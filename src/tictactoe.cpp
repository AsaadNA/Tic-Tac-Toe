#include "tictactoe.h"

bool TicTacToe::init_sdl() {
   if(SDL_Init(SDL_INIT_VIDEO) == 0 && TTF_Init() == 0) {
      window = SDL_CreateWindow("TicTacToe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,window_width,window_height,SDL_WINDOW_SHOWN);
      if(window) {
         renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
         if(renderer) {
            std::cout << "(MAIN LOG) Successful Initializing SDL\n";
            return true;
         }
      } else {
         std::cout << "Error Creating Window\n";
         return false;
      }
   } else {
      std::cout << "Error Initializing SDL\n";
      return false;
   }
}

void TicTacToe::create() {
   running = true;
   menu  = new Menu(renderer);
}

//@NOTE: The Update method is called only when events are on window
//       this basically updates and checks the game states
void TicTacToe::update() {

   //Check if the menu is still running or not -> then create our board according to the gamemode selected in menu
   if(menu->get_menu_running_status() == false && current_game_state != PLAYING) {
      board = new Board(menu->get_game_mode_selected(),renderer);
      current_game_state = PLAYING;
   }

   //If the game is finished reset all the flags .. so that it will restart 
   if(board != nullptr && board->check_game_finished()) {
      menu->reset_menu_flags();
      board->reset_game_flags();
      current_game_state = MENU;
      std::cout << "(LOG) Restarting the game in 4.2 seconds..\n";
      SDL_Delay(4200); //Delay by n seconds then it automagically goes to menu
   }
   
   if(event.type == SDL_QUIT) running = false;
   if(current_game_state == PLAYING) board->update(event);
   if(current_game_state == MENU) menu->update(event);
}

void TicTacToe::render() {
   
   SDL_RenderClear(renderer);
   
   if(current_game_state == MENU) menu->render();
   if(current_game_state == PLAYING) {
     board->render(renderer);   
     SDL_SetRenderDrawColor(renderer,0,0,0,0);
   }

   SDL_RenderPresent(renderer);
}

void TicTacToe::run() { 
   if(init_sdl()) {
      create();
      while(running) {
         if(SDL_PollEvent(&event)) update();         
         render();
      }
   }
}

TicTacToe::~TicTacToe() {
   delete board;
   delete menu;
}

/////////////////////////////////////////////

int main(int argc , char** argv) {
   TicTacToe *game = new TicTacToe();
   game->run();
}