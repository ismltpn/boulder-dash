#include "../sdl/include/SDL.h"
#include "textures.h"
void load_textures(SDL_Renderer * renderer){
  SDL_Surface * sSave = NULL;
  SDL_Surface * sEmpty = NULL;
  SDL_Surface * sBorder = NULL;
  SDL_Surface * sDiamond = NULL;
  SDL_Surface * sDirt = NULL;
  SDL_Surface * sMonster = NULL;
  SDL_Surface * sPlayer = NULL;
  SDL_Surface * sPlayer2 = NULL;
  SDL_Surface * sRock = NULL;
  SDL_Surface * sRock2 = NULL;
  SDL_Surface * sSpider = NULL;
  SDL_Surface * sWater = NULL;
  SDL_Surface * sDoor = NULL;
  SDL_Surface * sDigits = NULL;
  SDL_Surface * sScore = NULL;
  SDL_Surface * sGameover = NULL;
  SDL_Surface * sStart = NULL;
  SDL_Surface * sHeart = NULL;
  SDL_Surface * sPaused = NULL;
  SDL_Surface * sLevel = NULL;
  SDL_Surface * sClock = NULL;
  SDL_Surface * sArrow = NULL;
  SDL_Surface * sIntro = NULL;
  SDL_Surface * sBack = NULL;
  SDL_Surface * sWin = NULL;

  switch (theme) {
    case 1:
      sSave = SDL_LoadBMP("assets/1_save.bmp");
      sEmpty = SDL_LoadBMP("assets/1_empty.bmp");
      sBorder = SDL_LoadBMP("assets/1_border.bmp");
      sDiamond = SDL_LoadBMP("assets/1_diamond.bmp");
      sDirt = SDL_LoadBMP("assets/1_dirt.bmp");
      sMonster = SDL_LoadBMP("assets/1_monster.bmp");
      sPlayer = SDL_LoadBMP("assets/1_player.bmp");
      sPlayer2 = SDL_LoadBMP("assets/1_player2.bmp");
      sRock = SDL_LoadBMP("assets/1_rock.bmp");
      sRock2 = SDL_LoadBMP("assets/1_rock2.bmp");
      sSpider = SDL_LoadBMP("assets/1_spider.bmp");
      sWater = SDL_LoadBMP("assets/1_water.bmp");
      sDoor = SDL_LoadBMP("assets/1_door.bmp");
      sDigits = SDL_LoadBMP("assets/1_digits.bmp");
      sScore = SDL_LoadBMP("assets/1_score.bmp");
      sGameover = SDL_LoadBMP("assets/1_gameover.bmp");
      sStart = SDL_LoadBMP("assets/1_start.bmp");
      sHeart = SDL_LoadBMP("assets/1_heart.bmp");
      sPaused = SDL_LoadBMP("assets/1_pause.bmp");
      sLevel = SDL_LoadBMP("assets/1_level.bmp");
      sClock = SDL_LoadBMP("assets/1_clock.bmp");
      sArrow = SDL_LoadBMP("assets/1_cursor.bmp");
      sIntro = SDL_LoadBMP("assets/1_intro.bmp");
      sBack = SDL_LoadBMP("assets/1_back.bmp");
      sWin = SDL_LoadBMP("assets/1_win.bmp");
      break;
    case 2:
      sSave = SDL_LoadBMP("assets/3_save.bmp");
      sEmpty = SDL_LoadBMP("assets/3_empty.bmp");
      sBorder = SDL_LoadBMP("assets/3_border.bmp");
      sDiamond = SDL_LoadBMP("assets/3_diamond.bmp");
      sDirt = SDL_LoadBMP("assets/3_dirt.bmp");
      sMonster = SDL_LoadBMP("assets/3_monster.bmp");
      sPlayer2 = SDL_LoadBMP("assets/3_player2.bmp");
      sPlayer = SDL_LoadBMP("assets/3_player.bmp");
      sRock = SDL_LoadBMP("assets/3_rock.bmp");
      sRock2 = SDL_LoadBMP("assets/3_rock2.bmp");
      sSpider = SDL_LoadBMP("assets/3_spider.bmp");
      sWater = SDL_LoadBMP("assets/3_water.bmp");
      sDoor = SDL_LoadBMP("assets/3_door.bmp");
      sDigits = SDL_LoadBMP("assets/3_digits.bmp");
      sScore = SDL_LoadBMP("assets/3_score.bmp");
      sGameover = SDL_LoadBMP("assets/3_gameover.bmp");
      sStart = SDL_LoadBMP("assets/3_start.bmp");
      sHeart = SDL_LoadBMP("assets/3_heart.bmp");
      sPaused = SDL_LoadBMP("assets/3_pause.bmp");
      sLevel = SDL_LoadBMP("assets/3_level.bmp");
      sClock = SDL_LoadBMP("assets/3_clock.bmp");
      sArrow = SDL_LoadBMP("assets/3_cursor.bmp");
      sIntro = SDL_LoadBMP("assets/3_intro.bmp");
      sBack = SDL_LoadBMP("assets/3_back.bmp");
      sWin = SDL_LoadBMP("assets/3_win.bmp");
      break;
  }
  tSave = SDL_CreateTextureFromSurface(renderer,sSave);
  tEmpty = SDL_CreateTextureFromSurface(renderer,sEmpty);
  tBorder = SDL_CreateTextureFromSurface(renderer,sBorder);
  tDiamond = SDL_CreateTextureFromSurface(renderer,sDiamond);
  tDirt = SDL_CreateTextureFromSurface(renderer,sDirt);
  tMonster = SDL_CreateTextureFromSurface(renderer,sMonster);
  tPlayer = SDL_CreateTextureFromSurface(renderer,sPlayer);
  tPlayer2 = SDL_CreateTextureFromSurface(renderer,sPlayer2);
  tRock = SDL_CreateTextureFromSurface(renderer,sRock);
  tRock2 = SDL_CreateTextureFromSurface(renderer,sRock2);
  tSpider = SDL_CreateTextureFromSurface(renderer,sSpider);
  tWater = SDL_CreateTextureFromSurface(renderer,sWater);
  tDoor = SDL_CreateTextureFromSurface(renderer,sDoor);
  tDigits = SDL_CreateTextureFromSurface(renderer,sDigits);
  tScore = SDL_CreateTextureFromSurface(renderer,sScore);
  tGameover = SDL_CreateTextureFromSurface(renderer,sGameover);
  tStart = SDL_CreateTextureFromSurface(renderer,sStart);
  tHeart = SDL_CreateTextureFromSurface(renderer,sHeart);
  tPaused = SDL_CreateTextureFromSurface(renderer,sPaused);
  tLevel = SDL_CreateTextureFromSurface(renderer,sLevel);
  tClock = SDL_CreateTextureFromSurface(renderer,sClock);
  tArrow = SDL_CreateTextureFromSurface(renderer,sArrow);
  tIntro = SDL_CreateTextureFromSurface(renderer,sIntro);
  tBack = SDL_CreateTextureFromSurface(renderer,sBack);
  tWin = SDL_CreateTextureFromSurface(renderer,sWin);

  SDL_FreeSurface(sSave);
  SDL_FreeSurface(sEmpty);
  SDL_FreeSurface(sBorder);
  SDL_FreeSurface(sDiamond);
  SDL_FreeSurface(sDirt);
  SDL_FreeSurface(sMonster);
  SDL_FreeSurface(sPlayer);
  SDL_FreeSurface(sPlayer2);
  SDL_FreeSurface(sRock);
  SDL_FreeSurface(sRock2);
  SDL_FreeSurface(sSpider);
  SDL_FreeSurface(sWater);
  SDL_FreeSurface(sDoor);
  SDL_FreeSurface(sDigits);
  SDL_FreeSurface(sScore);
  SDL_FreeSurface(sGameover);
  SDL_FreeSurface(sStart);
  SDL_FreeSurface(sHeart);
  SDL_FreeSurface(sPaused);
  SDL_FreeSurface(sLevel);
  SDL_FreeSurface(sClock);
  SDL_FreeSurface(sArrow);
  SDL_FreeSurface(sIntro);
  SDL_FreeSurface(sBack);
  SDL_FreeSurface(sWin);
}
void free_textures(){
  SDL_DestroyTexture(tSave);
  SDL_DestroyTexture(tEmpty);
  SDL_DestroyTexture(tBorder);
  SDL_DestroyTexture(tDiamond);
  SDL_DestroyTexture(tDirt);
  SDL_DestroyTexture(tMonster);
  SDL_DestroyTexture(tPlayer);
  SDL_DestroyTexture(tPlayer2);
  SDL_DestroyTexture(tRock);
  SDL_DestroyTexture(tRock2);
  SDL_DestroyTexture(tSpider);
  SDL_DestroyTexture(tWater);
  SDL_DestroyTexture(tDoor);
  SDL_DestroyTexture(tDigits);
  SDL_DestroyTexture(tScore);
  SDL_DestroyTexture(tGameover);
  SDL_DestroyTexture(tStart);
  SDL_DestroyTexture(tHeart);
  SDL_DestroyTexture(tPaused);
  SDL_DestroyTexture(tLevel);
  SDL_DestroyTexture(tClock);
  SDL_DestroyTexture(tArrow);
  SDL_DestroyTexture(tIntro);
  SDL_DestroyTexture(tBack);
  SDL_DestroyTexture(tWin);
}
