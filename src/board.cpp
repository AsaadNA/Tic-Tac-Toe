#include "board.h"

//@NOTE: gm -> 1 for pvp && 2 for ai
Board::Board(int gm , SDL_Renderer* renderer) {

   //@NOTE: Initialzing the board and magic_square shit..

   mouse_point = new SDL_Point();

   const int x_val = 210;

   int xx = x_val;
   int yy = 100;
   int padding = 120;

   for(int i = 0; i <= 2; i++) {
      for(int j = 0; j <= 2; j++) {
         board[i][j] = new Placeholder(xx,yy,renderer);
         board[i][j]->set_magic_number(magic_squares[i][j]);
         xx += padding;
      }

      xx = x_val;
      yy += padding;
   }

   game_mode = gm;
   switch(gm) {
      case 0: {
         create_pvp();
      } break;

      case 1: {
         create_ai();
      } break;
   }
}

//@NOTE: Check if the magic_collection has 3 numbers with the sum of 15 in an array
bool Board::check_if_won(std::vector<int> array) {
   if(array.size() >= 3) {
      for(int i = 0; i <= array.size() - 1; i++) {
         for(int j = 0; j <= array.size() - 1; j++) {
            for(int k = 0; k <= array.size() - 1; k++) {
               if(i != j && i != k && j != k) {
                  if(array[i] + array[k] + array[j] == 15) {
                     return true;
                  }
               }
            }
         }
      }
   } return false;
}

void Board::create_pvp() {

   std::cout << "(LOG) CREATED PVP GAME MODE\n";

   player_one = new player();
   player_two = new player();

   //@TODO: We are assigning symbols .. but we will have a system

   player_one->symbol = 'x';
   player_two->symbol = 'o';

   //@TODO: Here we are giving the first turn to p1 .. but we will have toss system
   
   player_one->turn = true;
}


/* 
   @NOTE: This simply uses (turn) flag to determin the turn .. reject already taken places
          and checks to see who got the sum of 15
*/

void Board::update_pvp(SDL_Event& event) {
   if(event.type == SDL_MOUSEBUTTONDOWN && !pvp_game_over) {
      if(event.button.button == SDL_BUTTON_LEFT) {
         SDL_GetMouseState(&mouse_point->x , &mouse_point->y); //get mouse position
         for(int i = 0; i <= 2; i++) {
            for(int j = 0; j <= 2; j++) {
               if(board[i][j]->is_clicked(mouse_point)) {
                  if(board[i][j]->get_filled_status() == false) { //check if filled or not
                     
                     //@NOTE: This is player one
                     if(player_one->turn) {
                        player_one->turn = false;
                        player_two->turn = true;
                        board[i][j]->set_symbol(player_one->symbol);

                        //Push the magic number to the vector magic_collection of player_one
                        //Check if the player has won
                        //If the player has one then pvp_game_over = true;

                        player_one->magic_collection.push_back(board[i][j]->get_magic_number());
                        if(check_if_won(player_one->magic_collection)) {
                           pvp_game_over = true;
                           std::cout << "(GAME PVP LOG) Player One Has Won !!!!!!!\n";
                        }

                     //@NOTE: This is player two
                     } else {
                        player_two->turn = false;
                        player_one->turn = true;
                        board[i][j]->set_symbol(player_two->symbol);
                        player_two->magic_collection.push_back(board[i][j]->get_magic_number());
                        if(check_if_won(player_two->magic_collection)) {
                           pvp_game_over = true;
                           std::cout << "(GAME PVP LOG) Player Two Has Won !!!!!!!\n";
                        }
                     }

                     board[i][j]->set_filled_status(true);
                     filled_places += 1;

                     //@NOTE: Draw condition
                     if(filled_places == 3*3 && !pvp_game_over) {
                        pvp_game_over = true;
                        std::cout << "(GAME PVP LOG) Game Over with a draw !!\n";
                     }

                  } else {
                     std::cout << "(GAME PVP LOG) Already Taken Dipshit \n";
                  }
               }
            }
         }
      }
   }
}

bool Board::is_moves_left() {
   for(int i = 0; i <= 2; i++) {
      for(int j = 0; j <= 2; j++) {
         if(!board[i][j]->get_filled_status())
            return true;
      }
   }

   return false;
}

int Board::minimax_evaluator() {
   for(int row = 0; row <= 2; row++) {
      if(board[row][0]->gpv() == board[row][1]->gpv() && board[row][1]->gpv() == board[row][2]->gpv()) {
         if(board[row][0]->gpv() == _opponent->symbol)
            return +10;
         else if(board[row][0]->gpv() == _player->symbol)
            return -10;
      }
   }

   for(int col = 0; col <= 2; col++) {
      if(board[0][col]->gpv() == board[1][col]->gpv() && board[1][col]->gpv() == board[2][col]->gpv()) {
         if(board[0][col]->gpv() == _opponent->symbol)
            return +10;
         else if(board[0][col]->gpv() == _player->symbol)
            return -10;
      }
   }

   if(board[0][0]->gpv() == board[1][1]->gpv() && board[1][1]->gpv() == board[2][2]->gpv()) {
      if(board[0][0]->gpv() == _opponent->symbol)
         return +10;
      else if(board[0][0]->gpv() == _player->symbol)
         return -10;
   }

   if(board[0][2]->gpv() == board[1][1]->gpv() && board[1][1]->gpv() == board[2][0]->gpv()) { 
        if(board[0][2]->gpv() == _opponent->symbol) 
            return +10; 
        else if(board[0][2]->gpv() == _player->symbol) 
            return -10; 
    } 

    return 0;
}

int Board::minimax(int depth , bool is_max) {
   int score = minimax_evaluator();

   if(score == 10) {
      return score;
   }

   if(score == -10) {
      return score;
   }

   if(!is_moves_left()) {
      return 0;
   }

   if(is_max) {
      int best = -1000;
      for(int i = 0; i <= 2; i++) {
         for(int j = 0; j <= 2; j++) {
            if(board[i][j]->get_filled_status() == false) {
               board[i][j]->set_symbol(_opponent->symbol);
               board[i][j]->set_filled_status(true);
               best = std::max(best,minimax(depth+1,!is_max));
               board[i][j]->set_symbol(' ');
               board[i][j]->set_filled_status(false);
            }
         }
      }
      return best;
   }

   else {
      int best = 1000;
      for(int i = 0; i <= 2; i++) {
         for(int j = 0; j <= 2; j++) {
            if(board[i][j]->get_filled_status() == false) {
               board[i][j]->set_symbol(_player->symbol);
               board[i][j]->set_filled_status(true);
               best = std::min(best,minimax(depth+1,!is_max));
               board[i][j]->set_symbol(' ');
               board[i][j]->set_filled_status(false);
            }
         }
      }
      return best;
   }  
}

Board::move Board::find_best_move() {
   move best_move;
   best_move.row = -1;
   best_move.col = -1;
   int best_value = -1000;

   for(int i = 0; i <= 2; i++) {
      for(int j = 0; j <= 2; j++) {
         if(board[i][j]->get_filled_status() == false) {
            board[i][j]->set_symbol(_opponent->symbol);
            board[i][j]->set_filled_status(true);
            int move_value = minimax(0,false);
            board[i][j]->set_symbol(' ');
            board[i][j]->set_filled_status(false);

            if(move_value > best_value) {
               best_move.row = i;
               best_move.col = j;
               best_value = move_value;
            }
         }
      }
   }

   std::cout << "THE VALUE OF BEST MOVE IS: " << best_value << std::endl;
   std::cout << "BEST MOVE [" << best_move.row << "] [" << best_move.col << "]\n";
   return best_move; 
}

void Board::create_ai() {
   _player = new player();
   _opponent = new player();

   _player->turn = true;

   _player->symbol = 'x';
   _opponent->symbol = 'o';
}

void Board::update_ai(SDL_Event& event) {
   if(event.type == SDL_MOUSEBUTTONDOWN && !ai_game_over) {
      if(event.button.button == SDL_BUTTON_LEFT) {
         SDL_GetMouseState(&mouse_point->x,&mouse_point->y);
            for(int i = 0; i <= 2; i++) {
               for(int j = 0; j <= 2; j++) {
                  if(board[i][j]->is_clicked(mouse_point)) {
                     if(board[i][j]->get_filled_status() == false) {

                        if(_player->turn) {

                           _player->turn = false;
                           _opponent->turn = true;
                           board[i][j]->set_symbol(_player->symbol);
                           board[i][j]->set_filled_status(true);

                           filled_places++;

                           _player->magic_collection.push_back(board[i][j]->get_magic_number());
                           if(check_if_won(_player->magic_collection)) {
                              ai_game_over = true;
                              std::cout << "(GAME AI LOG) Player Has Won !!!!!!!\n";
                           }

                           std::cout << "(PLAYER)FILLED PLACES: " << filled_places << std::endl;
                        }

                        if(_opponent->turn && filled_places != 9) {
                           move best_move = find_best_move();
                           board[best_move.row][best_move.col]->set_symbol(_opponent->symbol);
                           board[best_move.row][best_move.col]->set_filled_status(true);

                           filled_places++;

                           _opponent->turn = false;
                           _player->turn = true;  
                           
                           std::cout << "(AI)FILLED PLACES: " << filled_places << std::endl;
                           
                           _opponent->magic_collection.push_back(board[best_move.row][best_move.col]->get_magic_number());
                           if(check_if_won(_opponent->magic_collection)) {
                              ai_game_over = true;
                              std::cout << "(GAME AI LOG) AI Has Won YOU LOSER !!!!!!!\n";
                           }
                        }

                        if(filled_places == 3*3 && !ai_game_over) {
                           ai_game_over = true;
                           std::cout << "(GAME AI LOG) Game Over with a draw !!\n";
                        }

                     } else {
                        std::cout << "MF it's taken";
                     }
                  }
               }
            }
         }
      }
   }

void Board::reset_game_flags() {
   switch(game_mode) {
      case 0: {
         pvp_game_over = false;
      } break;

      case 1: {
         ai_game_over = false;
      } break;
   }
}

bool Board::check_game_finished() {
   switch(game_mode) {
      case 0: {
         return pvp_game_over;
      } break;

      case 1: {
         return ai_game_over;
      } break;
   }
}

void Board::update(SDL_Event& event) {
   switch(game_mode) {
      case 0: {
         update_pvp(event);
      } break;

      case 1: {
         update_ai(event);
      } break;
   }
}

void Board::render(SDL_Renderer *renderer) {
   for(int i = 0; i <= 2; i++) {
      for(int j = 0; j <= 2; j++) {
         board[i][j]->render(renderer);
      }
   }
}

Board::~Board() {
   delete mouse_point;
   delete player_one;
   delete player_two;
   delete _player;
   delete _opponent;
}