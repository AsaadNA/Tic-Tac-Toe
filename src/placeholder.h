#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

#include <SDL2/sdl.h>
#include <SDL2/sdl_image.h>

class Placeholder {

public:

   Placeholder(int x , int y,SDL_Renderer* renderer);
   
   void render(SDL_Renderer *renderer);
   bool is_clicked(SDL_Point* mouse_point);

   void set_magic_number(int n) { magic_number = n; }
   void set_filled_status(bool status) { filled = status; }
   void set_symbol(char sym) { symbol = sym; }

   int  get_magic_number() { return magic_number; }
   bool get_filled_status() { return filled; }
   char gpv() { return symbol; }

private:

   const int size = 120;
   int xx = 0, yy = 0;
   bool filled = false;
   int magic_number = 0;

   char symbol = ' ';

   SDL_Rect* rect = nullptr;

   SDL_Texture *x_texture = nullptr; 
   SDL_Texture *o_texture = nullptr;
   SDL_Rect texture_rect;

};
