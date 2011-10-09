// copyright (C) 2001-2011 by Patrick Hanevold

#include "widget.h"
#include <math.h>

class Grid : public Widget{
public:   Grid(Widget *p);
  void    render(Rect r);
};

Grid::Grid(Widget *p) : Widget(p){
}

void Grid::render(Rect r){

  if(!getChildren()->getCount()) return;

  int hb = int(sqrt(double(getChildren()->getCount()))+.5); //log2(getChildren()->getCount());
  if(hb==0) hb=1;
  int vb = getChildren()->getCount()/hb;
  if(vb*hb<getChildren()->getCount()) vb++;

  int bw = r.w/hb;
  int bh = r.h/vb;
  int n=0;
  for(int yb=0; yb<vb; yb++){
    for(int xb=0; xb<hb; xb++){
      if(n!=getChildren()->getCount()){
        Widget *w = (*getChildren())[n++];
        w->Widget::render(Rect(r.x+xb*bw,r.y+yb*bh,r.w/hb,r.h/vb));
      }else fillRect(Rect(r.x+xb*bw,r.y+yb*bh,r.w/hb,r.h/vb),Color(0,0,0));
    }
  }
//  for(int n=0; n<getChildren()->getCount(); n++){
//    Widget *w = (*getChildren())[n];
//    w->Widget::render(Rect(r.x,r.y,r.w/hb,r.h/vb));
//  }
  noRender();
}
