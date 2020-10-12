#pragma once

#include <SDL2/sdl.h>
#include <SDL2/sdl_ttf.h>

#include <iostream>
#include <assert.h>

class Menu {

private:

   struct menu_item {
      SDL_Rect rect;
      SDL_Surface *surface;
      SDL_Texture *texture;
      const char* message;
      int itemnumber;
   };

public:

   Menu(SDL_Renderer* renderer);
   
   void update(SDL_Event& event);
   void render();

   void reset_menu_flags();
   void update_menu_item();

   menu_item* create_menu_item(int x , int y , int w , int h ,const char* message,int itemnumber);

   bool get_menu_running_status() { return menu_still_running; }
   int  get_game_mode_selected() { return game_mode_selected; }

private:

   SDL_Renderer *global_renderer = nullptr;

   TTF_Font* font = nullptr;

   SDL_Color normal_font_color = {255,255,255};
   SDL_Color selected_font_color = {0,0,255};

   menu_item* game_title; 
   menu_item *items[2]; //title and 2 game modes
   int current_index = 0;

   bool menu_still_running = true;
   int game_mode_selected = 0;

};