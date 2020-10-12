#include "placeholder.h"

Placeholder::Placeholder(int x , int y , SDL_Renderer* renderer) {
   rect = new SDL_Rect{x,y,size,size};
   
   int texture_w, texture_h;
   x_texture = IMG_LoadTexture(renderer,"res/x.png");
   assert(x_texture != nullptr && "(Assert) Failed Loading X Texture");
   o_texture = IMG_LoadTexture(renderer,"res/o.png");
   assert(o_texture != nullptr && "(Assert) Failed Loading O Texture");
   SDL_QueryTexture(x_texture,NULL,NULL,&texture_w,&texture_h);
   SDL_QueryTexture(o_texture,NULL,NULL,&texture_w,&texture_h);
   
   texture_rect.x = x + 35;  texture_rect.y = y + 35;
   texture_rect.w = texture_w;  texture_rect.h = texture_h;

}

bool Placeholder::is_clicked(SDL_Point* mouse_point) {
   return SDL_PointInRect(mouse_point,rect);
}

void Placeholder::render(SDL_Renderer *renderer) {
   SDL_SetRenderDrawColor(renderer,255,255,255,0);
   SDL_RenderDrawRect(renderer,rect);
   if(symbol == 'o') { 
      SDL_RenderCopy(renderer,o_texture,NULL,&texture_rect);
   } else if(symbol == 'x') {
      SDL_RenderCopy(renderer,x_texture,NULL,&texture_rect);
   }
}
