#pragma once

#include "board.h"
#include "menu.h"

class TicTacToe {

public:

   ~TicTacToe();

   void run();

private:

   bool init_sdl();

   void create();
   void render();
   void update();

private:

   const int window_width = 800;
   const int window_height = 600;

   SDL_Window *window = nullptr;
   SDL_Renderer *renderer = nullptr;

   SDL_Event event;

   bool running = false;

private:

   Board *board = nullptr;
   Menu  *menu  = nullptr;

   enum game_states { PLAYING , MENU };
   game_states current_game_state = MENU;
};