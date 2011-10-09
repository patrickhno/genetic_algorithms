// copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include "widget.h"

using namespace std;

class Screen : public Widget{
public:         Screen(int w, int h);
                ~Screen();
          void  render(Rect r);
private:
  static  void  fillRect(Rect, Color);
  static  void  drawLine(int,int,int,int, Color);
  static  void  drawCircle(int,int,int, Color);
  static  SDL_Surface *scr;
};

