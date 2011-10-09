// copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include "screen.h"

using namespace std;

SDL_Surface *Screen::scr;

Screen::Screen(int w, int h) : Widget(){
  if(SDL_Init(SDL_INIT_VIDEO)<0){
    cerr << "Couldn't initialize SDL: " << SDL_GetError() << endl;
    exit(1);
  }

#ifdef HAVE_SDL_TTF
  if(TTF_Init()<0){
    fprintf(stderr, "Couldn't initialize TTF: %s\n",SDL_GetError());
    exit(2);
  }
  atexit(TTF_Quit);
#endif

  int videoflags = SDL_SWSURFACE/*|SDL_FULLSCREEN*/;
  scr = SDL_SetVideoMode(w,h, 24, videoflags);
  if(scr==NULL){
    cerr << "Couldn't set display mode: " << SDL_GetError() << endl;
    SDL_Quit();
    exit(5);
  }
#ifdef HAVE_SDL_TTF
  font = TTF_OpenFont("/usr/X11R6/lib/X11/fonts/truetype/verdana.ttf", 18);
  if(font==NULL){
    fprintf(stderr, "Couldn't load %d pt font: %s\n", 18, SDL_GetError());
    exit(2);
  }
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
#endif

  Widget::fillRect   = fillRect;
  Widget::drawLine   = drawLine;
  Widget::drawCircle = drawCircle;

//  view = Rect(0,0,w,h);
}
Screen::~Screen(){
}

void Screen::fillRect(Rect r, Color c){
  unsigned char *fb=(unsigned char*)scr->pixels;
  unsigned char R=char(c.red*255.0);
  unsigned char G=char(c.green*255.0);
  unsigned char B=char(c.blue*255.0);
  for(int y=0; y<r.h; y++){
    for(int x=0; x<r.w; x++){
      int n=(r.y+y)*scr->w+r.x+x;
      fb[n*3+0]=B;
      fb[n*3+1]=G;
      fb[n*3+2]=R;
    }
  }
}
void Screen::drawLine(int x, int y, int x1, int y1, Color c){

  unsigned char r = char(c.red*255);
  unsigned char g = char(c.green*255);
  unsigned char b = char(c.blue*255);

  unsigned char *fb=(unsigned char*)scr->pixels;
  int w=scr->w;
  int dx=x1-x;
  int dy=y1-y;
  if(abs(dx)>abs(dy)&&dx){
    y<<=16;
    dy<<=16;
    if(dx) dy/=abs(dx);
    else dy=0;
    if(dx>=0) dx=1;
    else dx=-1;
    do{ //for(;x<x1; x++){
      fb[((y>>16)*w+x)*3+0]=b;
      fb[((y>>16)*w+x)*3+1]=g;
      fb[((y>>16)*w+x)*3+2]=r;
      y+=dy;
      x+=dx;
    }while(x!=x1);
  }else if(dy){
    x<<=16;
    dx<<=16;
    if(dy) dx/=abs(dy);
    else dx=0;
    if(dy>0) dy=1;
    else dy=-1;
    do{ //for(;y<y1; y++){
      fb[(y*w+(x>>16))*3+0]=b;
      fb[(y*w+(x>>16))*3+1]=g;
      fb[(y*w+(x>>16))*3+2]=r;
      x+=dx;
      y+=dy;
    }while(y!=y1);
  }
}

void Screen::drawCircle(int x, int y, int d, Color c){
  double rad=d/2.0;
  for(int n=0; n<32; n++){
    double a=n*M_PI*4.0/32.0;
    double b=(n+1)*M_PI*4.0/32.0;
    drawLine(int(x+sin(a)*rad),int(y+cos(a)*rad),int(x+sin(b)*rad),int(y+cos(b)*rad),c);
  }
}

void Screen::render(Rect r){
  if(SDL_MUSTLOCK(scr)){
    if(SDL_LockSurface(scr)<0){
      fprintf(stderr, "Couldn't lock display surface: %s\n",SDL_GetError());
      return;
    }
  }

  Widget::render(r);

  if(SDL_MUSTLOCK(scr)) SDL_UnlockSurface(scr);
  SDL_UpdateRect(scr, 0, 0, 0, 0);
}
