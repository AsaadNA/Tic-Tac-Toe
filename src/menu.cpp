#include "menu.h"

Menu::Menu(SDL_Renderer* renderer) {

   global_renderer = renderer;

   font = TTF_OpenFont("res/font.ttf",20);
   assert(font != nullptr && "(ASSERT) Failed to load font !");
   
   game_title = create_menu_item(145,20,450,150,"Tic Tac Toe",-1);
   items[0]   = create_menu_item(145,220,450,150,"Player Vs Player",0);
   items[1]   = create_menu_item(145,380,450,150,"Player Vs AI",1);
}

Menu::menu_item* Menu::create_menu_item(int x , int y , int w , int h , const char* message,int itemnumber) {
   menu_item *item = new menu_item;
   item = new menu_item(); 
   item->message = message;
   item->surface = TTF_RenderText_Solid(font,message,normal_font_color);
   item->texture = SDL_CreateTextureFromSurface(global_renderer,item->surface);
   item->rect.x = x;
   item->rect.y = y;
   item->rect.w = w; 
   item->rect.h = h;
   item->itemnumber = itemnumber;
   SDL_FreeSurface(item->surface);
   return item;
}

void Menu::reset_menu_flags() {
   game_mode_selected = 0;
   menu_still_running = true;
}

void Menu::update(SDL_Event& event) {
   if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch(event.key.keysym.sym) {

         //Scrolling up the menu
         case SDLK_UP: {
            if(current_index == 0) current_index = 0;
            else current_index--;
            std::cout << "Current index: " << current_index << std::endl;

         } break;

         //Scrolling down the menu
         case SDLK_DOWN: {
                  
            if(current_index == 1) current_index = 1; //This should be set to the array size
            else current_index++;
            std::cout << "Current index: " << current_index << std::endl;

         } break;

         //Enter key in sense selects a menu item and changes the flag
         case SDLK_RETURN: {
            game_mode_selected = current_index;
            menu_still_running = false;
         } break; 

         //Let's say space is used for pvp
         case SDLK_SPACE: {
            menu_still_running = false;
            game_mode_selected = 1;
         } break;

         //And A is used for AI
         case SDLK_a: {
            menu_still_running = false;
            game_mode_selected = 2;
         } break;
      }
   }
}

void Menu::render() {
   SDL_SetRenderDrawColor(global_renderer,0,0,0,0);
   SDL_RenderCopy(global_renderer,game_title->texture,NULL,&game_title->rect);
   for(int i = 0; i <= 1; i++) {
      if(current_index == items[i]->itemnumber) {
         items[i]->surface = TTF_RenderText_Solid(font,items[i]->message,selected_font_color);
         items[i]->texture = SDL_CreateTextureFromSurface(global_renderer,items[i]->surface);
      } else {
         items[i]->surface = TTF_RenderText_Solid(font,items[i]->message,normal_font_color);
         items[i]->texture = SDL_CreateTextureFromSurface(global_renderer,items[i]->surface);
      }
      
      SDL_RenderCopy(global_renderer,items[i]->texture,NULL,&items[i]->rect);
   }
}