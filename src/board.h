#pragma once

#include "placeholder.h"
#include <algorithm>    // std::max

class Board {

private:

   struct player {
      char symbol;
      bool turn;
      std::vector<int> magic_collection;
   };

public:

    Board(int gm , SDL_Renderer *renderer);
   ~Board();
   
   void update(SDL_Event& event);
   void render(SDL_Renderer *renderer);

   void reset_game_flags();
   bool check_game_finished();   //This will check if pvp or ai is finished or not
   
private:

   void create_pvp();
   void update_pvp(SDL_Event& event);

   void create_ai();
   void update_ai(SDL_Event& event);

   struct move {
      int row , col;
   };

   bool is_moves_left();
   int  minimax_evaluator();
   int  minimax(int depth , bool is_max);
   move find_best_move();

   bool check_if_won(std::vector<int> array);

private:

   bool stop_updating = false;
   bool pvp_game_over = false;
   bool ai_game_over  = false;

   player *player_one = nullptr;
   player *player_two = nullptr;

   player *_player = nullptr;
   player *_opponent = nullptr;

   Placeholder *board[3][3];
   int magic_squares[3][3] = {{2,7,6},{9,5,1},{4,3,8}};

   int game_mode = 0;
   int filled_places = 0; //tracks the places taken on grid to check for draw

   SDL_Point *mouse_point = nullptr;
};