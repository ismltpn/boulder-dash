#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "textures.h"
#include "intro.h"
#include "fundamentals.h"
#include "map.h"
#include "prestage.h"
#include "stage.h"
#include "ends.h"
int main(int argc, char * argv[]){
  int window_w = 600, window_h = 600;
  SDL_Window *window;
  SDL_Renderer * renderer;
  int currentLevel = 1;
  int health=5;
  int score = 0;
  Level level;
  /* init */
  if (SDL_Init( SDL_INIT_EVERYTHING ) < 0){
    printf("SDL init edilemedi! Hata: %s\n",SDL_GetError( ) );
  }
  window = SDL_CreateWindow( "Boulder Dash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_RESIZABLE );
  renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
  if ( NULL == window ){
    printf("Pencere oluşturulamadı! Hata: %s\n",SDL_GetError( ) );
    return EXIT_FAILURE;
  }
  theme = 1;
  load_textures(renderer);
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  intro(window,renderer);
  while(health>=0 && currentLevel<11){
    prestage(window,renderer,score,currentLevel,health);
    level = level_picker(currentLevel);
    if(game(&level,&window_w,&window_h,health,&score,window,renderer) == -1) health --;
    else currentLevel ++;
  }

  if(health<0){
    gameover(window,renderer,score,-1);
  }
  else{
    gameover(window,renderer,score,1);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow( window );
  SDL_Quit( );
  return EXIT_SUCCESS;
}