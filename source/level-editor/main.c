#include "../../sdl/include/SDL.h"
#include <stdio.h>
#include "../fundamentals.h"
#include "../textures.h"
#define BLOCK_SIZE 15
#define ROI_CHANGE_SIZE 5
#define MAX_WIDTH 50
#define MAX_HEIGHT 30
#define BOTTOM_BLOCK_SIZE 50
#define PLAYER_START_X 3
#define PLAYER_START_Y 3
#define DOOR_X 1
#define DOOR_Y 1

void str_add(char * s1, char * s2);

Level load_from_file(){
  int i;
  FILE * f;
  char file_name[64];
  Level level;
  do{
    printf("File name:");
    scanf("%s", file_name);
    str_add(file_name,".bin");
    f = fopen(file_name,"r");
    if(f==NULL) printf("Cannot open %s\n", file_name);
  }while(f==NULL);
  fread(&level.width,sizeof(int),1,f);
  fread(&level.height,sizeof(int),1,f);
  fread(&level.diamondsRequired,sizeof(int),1,f);
  fread(&level.time,sizeof(int),1,f);
  fread(&level.waterRate,sizeof(double),1,f);
  fread(&level.playerStartPos,sizeof(Point),1,f);
  fread(&level.doorPos,sizeof(Point),1,f);

  level.blocks=ALLOC(Block*,level.height);
  for(i=0;i<level.height;i++){
    level.blocks[i]=ALLOC(Block,level.width);
  }
  for(i=0;i<level.height;i++){
    fread(level.blocks[i], sizeof(Block),level.width,f);
  }
  fclose(f);
  return level;
}
void render_number(SDL_Renderer * renderer, int num, Point c, int size, int len){
  int i,w,h;
  SDL_Rect source,dest;
  char text[100];
  SDL_QueryTexture(tDigits,NULL,NULL,&w,&h);
  sprintf(text,"%0*d",len,num);
  for(i=0;i<len;i++){
    dest.h=size;
    dest.w=size;
    dest.x=(c.x+i)*size;
    dest.y=(c.y+1)*size;
    source.y=0;
    source.w=w/10;
    source.h=h;
    switch (text[i]) {
      case '1': source.x=source.w; break;
      case '2': source.x=source.w*2; break;
      case '3': source.x=source.w*3; break;
      case '4': source.x=source.w*4; break;
      case '5': source.x=source.w*5; break;
      case '6': source.x=source.w*6; break;
      case '7': source.x=source.w*7; break;
      case '8': source.x=source.w*8; break;
      case '9': source.x=source.w*9; break;
      case '0': source.x=0; break;
    }
    SDL_RenderCopy(renderer,tDigits,&source,&dest);
  }
}
void str_add(char * s1, char * s2){
  int i,j;
  for(i=0;s1[i]!='\0';i++);
  for(j=0;s2[j]!='\0';j++){
    s1[i+j]=s2[j];
  }
  s1[i+j]='\0';
}

void free_roi(Block ** roi,int h){
  int i;
  for(i=0;i<h;i++){
    free(roi[i]);
  }
  free(roi);
}

void save(Level * level){
  int i,j;
  FILE * f;
  char name[64];
  printf("Diamonds Required:(%d)",level->diamondsRequired);
  scanf("%d", &level->diamondsRequired);
  printf("Max time:(%d)",level->time);
  scanf("%d", &level->time);
  printf("Water Rate:(%.2lf)",level->waterRate);
  scanf("%lf", &level->waterRate);
  printf("Enter File Name:");
  scanf("%s", name);
  str_add(name,".bin");
  f = fopen(name,"w");
  for(i=0;i<level->height;i++){
    for(j=0;j<level->width;j++){
      level->blocks[i][j].active=0;
    }
  }
  if(f==NULL) printf("Cannot open %s\n", name);
  else{
    printf("Exporting level specs..\n");
    fwrite(&level->width,sizeof(int),1,f);
    fwrite(&level->height,sizeof(int),1,f);
    fwrite(&level->diamondsRequired,sizeof(int),1,f);
    fwrite(&level->time,sizeof(int),1,f);
    fwrite(&level->waterRate,sizeof(double),1,f);
    fwrite(&level->playerStartPos,sizeof(Point),1,f);
    fwrite(&level->doorPos,sizeof(Point),1,f);
    printf("Exporting map..\n");
    for(i=0;i<level->height;i++){
      fwrite(level->blocks[i], sizeof(Block),level->width,f);
      printf("Row %d exported.\n", i);
    }
  }
  fclose(f);
  free_roi(level->blocks,level->height);
}
int max_limit(int a, int max){
  if(a>max) return max;
  return a;
}
int min_limit(int a, int min){
  if(a<min) return min;
  return a;
}

void try_to_change(Level * level, Point mouse, block_t t,Point startPos,Point startIndex){
  if(mouse.x>startPos.x&&mouse.x<startPos.x+BLOCK_SIZE*max_limit(level->width,MAX_WIDTH)){
    if(mouse.y>startPos.y&&mouse.y<startPos.y+BLOCK_SIZE*max_limit(level->height,MAX_HEIGHT)){
      mouse.x-=startPos.x;
      mouse.y-=startPos.y;
      mouse.x=mouse.x/BLOCK_SIZE;
      mouse.y=mouse.y/BLOCK_SIZE;
      mouse.x+=startIndex.x;
      mouse.y+=startIndex.y;
      if(mouse.x!=0&&mouse.y!=0&&mouse.x!=level->width-1&&level->height-1){
        switch (t) {
          case player:
            level->blocks[level->playerStartPos.y][level->playerStartPos.x].type=empty;
            level->playerStartPos=mouse;
            level->blocks[mouse.y][mouse.x].type=t;
            break;
          case door:
            level->blocks[level->doorPos.y][level->doorPos.x].type=empty;
            level->doorPos=mouse;
            level->blocks[mouse.y][mouse.x].type=t;
            break;
          default: level->blocks[mouse.y][mouse.x].type=t; break;
        }

      }
    }
  }
}

SDL_Rect point_to_rect(Point p, int size){
  SDL_Rect rect;
  rect.x=p.x*size;
  rect.y=p.y*size;
  rect.w=size;
  rect.h=size;
  return rect;
}

void move_roi(Level * level, Point * p, Direction d){
  int s = ROI_CHANGE_SIZE;
  switch (d) {
    case _left:  p->x=min_limit(p->x-s,0); return;
    case _up:    p->y=min_limit(p->y-s,0); return;
    case _right: p->x=max_limit(p->x+s,level->width-MAX_WIDTH); return;
    case _down:  p->y=max_limit(p->y+s,level->height-MAX_HEIGHT); return;
    default: return;
  }
}
void render_block(Block *block, SDL_Renderer * renderer,int size,Point startPos, Point startIndex){
  SDL_Texture * current;
  SDL_Rect source,dest;
  int w,h;
  Direction p = _none;
  int anim = 1;
  switch (block->type) {
    case border:
     current = tBorder; break;
    case empty:
     current = tEmpty; break;
    case player:
     current = tPlayer; break;
    case spider:
     current = tSpider; break;
    case diamond:
     current = tDiamond; break;
    case monster:
     current = tMonster; break;
    case rock:
     current = tRock; break;
    case dirt:
     current = tDirt; break;
    case water:
     current = tWater; break;
    case door:
     current = tDoor; break;
    default: current = tDirt; break;
  }
  dest=point_to_rect(block->pos,size);
  dest.x+=startPos.x-startIndex.x*BLOCK_SIZE;
  dest.y+=startPos.y-startIndex.y*BLOCK_SIZE;
  if(block->type==rock && block->active==0) current=tRock2;
  if(block->type==door || block->type==monster || block->type==rock || block->type==spider || block->type==water || block->type==diamond){
    SDL_QueryTexture(current,NULL,NULL,&w,&h);
    source.w=w/4;
    source.h=h;
    source.y=0;
    switch (anim) {
      case 0: source.x=0; break;
      case 1: source.x=source.w; break;
      case 2: source.x=source.w*2; break;
      case 3: source.x=source.w*3; break;
      default: break;
    }
    SDL_RenderCopy(renderer,current,&source,&dest);
  }
  else if(block->type==player){
    SDL_QueryTexture(current,NULL,NULL,&w,&h);
    source.w=w/4;
    source.h=h/4;
    switch (anim) {
      case 0: source.x=0; break;
      case 1: source.x=source.w; break;
      case 2: source.x=source.w*2; break;
      case 3: source.x=source.w*3; break;
      default: break;
    }
    switch (p) {
      case _left: source.y=0; break;
      case _right: source.y=source.h; break;
      case _down: source.y=source.h*2; break;
      case _up: source.y=source.h*3; break;
      case _none:
        current=tPlayer2;
        SDL_RenderCopy(renderer,current,NULL,&dest);
        return;
    }
    SDL_RenderCopy(renderer,current,&source,&dest);
  }
  else SDL_RenderCopy(renderer,current,NULL,&dest);
}
void draw_map(Level * map,SDL_Renderer * renderer,Point startPos, Point startIndex){
  Block ** roi = map->blocks;
  int i,j;
  for(i=0;i<max_limit(map->height,MAX_HEIGHT);i++){
    for(j=0;j<max_limit(map->width,MAX_WIDTH);j++){
      render_block(&roi[i+startIndex.y][j+startIndex.x],renderer,BLOCK_SIZE,startPos,startIndex);
    }
  }
}
void draw_grid(Level * level, SDL_Renderer * renderer, Point startPos){
  int i;
  SDL_SetRenderDrawColor(renderer,0,255,0,30);
  for(i=0;i<max_limit(level->height,MAX_HEIGHT);i++){
    SDL_RenderDrawLine(renderer,startPos.x,i*BLOCK_SIZE+startPos.y,max_limit(level->width,MAX_WIDTH)*BLOCK_SIZE+startPos.x,i*BLOCK_SIZE+startPos.y);
  }
  for(i=0;i<max_limit(level->width,MAX_WIDTH);i++){
    SDL_RenderDrawLine(renderer,i*BLOCK_SIZE+startPos.x,startPos.y,i*BLOCK_SIZE+startPos.x,max_limit(level->height,MAX_HEIGHT)*BLOCK_SIZE+startPos.y);
  }
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
}
void empty_map(Level * level){
  int i,j;
  level->blocks=ALLOC(Block*,level->height);
  for(i=0;i<level->height;i++){
    level->blocks[i]=ALLOC(Block,level->width);
  }
  for(i=0;i<level->height;i++){
    for(j=0;j<level->width;j++){
      level->blocks[i][j].active=0;
      level->blocks[i][j].type=dirt;
      level->blocks[i][j].pos.x=j;
      level->blocks[i][j].pos.y=i;
      if(i==0||j==0||i==level->height-1||j==level->width-1){
        level->blocks[i][j].type=border;
      }
    }
  }
  level->diamondsRequired=0;
  level->playerStartPos.x=PLAYER_START_X;
  level->playerStartPos.y=PLAYER_START_Y;
  level->doorPos.x=DOOR_X;
  level->doorPos.y=DOOR_Y;
  level->blocks[PLAYER_START_Y][PLAYER_START_X].type=player;
  level->blocks[DOOR_Y][DOOR_X].type=door;
}

int main(){
  int window_w = MAX_WIDTH*BLOCK_SIZE, window_h = MAX_HEIGHT*BLOCK_SIZE+100;
  SDL_Window * window;
  SDL_Event e;
  SDL_Renderer * renderer;
  Level level;
  Point zeroPoint = {0,0};
  Point mapStartPos = {0,0};
  Point roiStartIndex = {0,0};
  SDL_Rect saveRect;
  Block bottomBlocks[10];
  int running = 1;
  int biggerH = 0;
  int biggerV = 0;
  int i;
  int mouseDown = 0;
  Point mousePos;
  block_t cursor = empty;
  Block selected;
  Point selectedPos;
  char isEdit;
  theme = 1;
  printf("Do you want to edit an existing level?");
  do{
    printf("(y/n)");
    scanf("%c", &isEdit);
  }while(isEdit!='y'&&isEdit!='n');
  if(isEdit=='y'){
    level = load_from_file();
  }
  else{
    printf("Enter Width:");
    scanf("%d", &level.width);
    printf("Enter Height:");
    scanf("%d", &level.height);
    empty_map(&level);
  }

  if (SDL_Init( SDL_INIT_EVERYTHING ) < 0){
    printf("SDL init edilemedi! Hata: %s\n",SDL_GetError( ) );
    exit(-1);
  }
  window = SDL_CreateWindow( "Boulder Dash - Level Creator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_ALLOW_HIGHDPI);
  renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  load_textures(renderer);

  if(level.width<=MAX_WIDTH){
    mapStartPos.x=(MAX_WIDTH-level.width)*BLOCK_SIZE/2;
  }
  else{
    biggerH=1;
  }
  if(level.height<=MAX_HEIGHT){
    mapStartPos.y=(MAX_HEIGHT-level.height)*BLOCK_SIZE/2;
  }
  else{
    biggerV=1;
  }

  bottomBlocks[0].type=empty;
  bottomBlocks[1].type=border;
  bottomBlocks[2].type=diamond;
  bottomBlocks[3].type=dirt;
  bottomBlocks[4].type=monster;
  bottomBlocks[5].type=player;
  bottomBlocks[6].type=rock;
  bottomBlocks[7].type=spider;
  bottomBlocks[8].type=water;
  bottomBlocks[9].type=door;
  for(i=0;i<10;i++){
    bottomBlocks[i].pos.x=i;
    bottomBlocks[i].pos.y=(window_h-70)/BOTTOM_BLOCK_SIZE;
  }

  saveRect.x=window_w-225;
  saveRect.y=window_h-100;
  saveRect.w=200;
  saveRect.h=100;

  selected.pos.x=0;
  selected.pos.y=0;
  selectedPos.x=BOTTOM_BLOCK_SIZE/4;
  selectedPos.y=window_h-100-BOTTOM_BLOCK_SIZE/2;

  while(running){
    if ( SDL_PollEvent( &e )){
      SDL_GetMouseState(&mousePos.x, &mousePos.y);
      switch (e.type){
        case SDL_QUIT: exit(0); break;
        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){
            case SDLK_LEFT: if(biggerH) move_roi(&level,&roiStartIndex,_left);break;
            case SDLK_RIGHT: if(biggerH) move_roi(&level,&roiStartIndex,_right);break;
            case SDLK_UP: if(biggerV) move_roi(&level,&roiStartIndex,_up);break;
            case SDLK_DOWN: if(biggerV) move_roi(&level,&roiStartIndex,_down);break;
            case SDLK_0: cursor=door; break;
            case SDLK_1: cursor=empty; break;
            case SDLK_2: cursor=border; break;
            case SDLK_3: cursor=diamond; break;
            case SDLK_4: cursor=dirt; break;
            case SDLK_5: cursor=monster; break;
            case SDLK_6: cursor=player; break;
            case SDLK_7: cursor=rock; break;
            case SDLK_8: cursor=spider; break;
            case SDLK_9: cursor=water; break;
          }
        case SDL_MOUSEBUTTONDOWN:
          if(e.button.button==SDL_BUTTON_LEFT){
            mouseDown=1;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          if(e.button.button==SDL_BUTTON_LEFT){
            mouseDown=0;
          }
          break;
      }
    }
    if(mouseDown){
      if(mousePos.y>MAX_HEIGHT*BLOCK_SIZE){
        if(mousePos.x<BOTTOM_BLOCK_SIZE*1) cursor = empty;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*2) cursor = border;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*3) cursor = diamond;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*4) cursor = dirt;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*5) cursor = monster;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*6) cursor = player;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*7) cursor = rock;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*8) cursor = spider;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*9) cursor = water;
        else if(mousePos.x<BOTTOM_BLOCK_SIZE*10) cursor = door;
        else {
          running=0;
        }
      }
      else{
        try_to_change(&level,mousePos,cursor,mapStartPos,roiStartIndex);
      }
    }
    SDL_RenderClear(renderer);
    draw_map(&level,renderer,mapStartPos,roiStartIndex);
    draw_grid(&level,renderer,mapStartPos);
    for(i=0;i<10;i++){
      if(i==0)
        render_number(renderer,i,bottomBlocks[9].pos,BOTTOM_BLOCK_SIZE,1);
      else render_number(renderer,i,bottomBlocks[i-1].pos,BOTTOM_BLOCK_SIZE,1);
      render_block(&bottomBlocks[i],renderer,BOTTOM_BLOCK_SIZE,zeroPoint,zeroPoint);
    }

    SDL_RenderCopy(renderer,tSave,NULL,&saveRect);
    selected.type=cursor;
    render_block(&selected,renderer,BOTTOM_BLOCK_SIZE/2,selectedPos,zeroPoint);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow( window );
  SDL_Quit( );
  save(&level);
  free_textures();
  return 0;
}

/*
typedef struct{
  block_t type;
  Point pos;
  int active;
}Block;

typedef struct{
  Block ** blocks;
  int width;
  int height;
  int totalDiamonds;
  Point playerStartPos;
  Point doorPos;
}Level;
*/
