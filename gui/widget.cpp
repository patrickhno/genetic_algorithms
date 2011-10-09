// copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include "widget.h"

using namespace std;

#ifdef HAVE_SDL_TTF
TTF_Font *Widget::font;
#endif
void (*Widget::fillRect)(Rect, Color)           = 0;
void (*Widget::drawLine)(int,int,int,int,Color) = 0;
void (*Widget::drawCircle)(int,int,int,Color)   = 0;

Widget::Widget(){
  parent = 0;
}
Widget::Widget(Widget *p){
  p->attach(this);
//  parent=p;
}
Widget::~Widget(){
  if(parent) parent->detach(this);
}

Widget *Widget::getParent() const{ return parent; }
const Array<Widget*> *Widget::getChildren() const{ return &children;  }

void Widget::render(Rect r){
  view = r;
  dorender = true;
  if(parent) render(r);
  if(dorender){
    for(int n=0; n<children.getCount(); n++){
      Widget *w = children[n];
      w->Widget::render(r);
    }
  }
}

void Widget::attach(Widget *child){
  children.add(child);
//  child->view = view;
  child->parent = this;
}
void Widget::detach(Widget *child){
  for(int n=0; n<children.getCount(); n++) if(children[n]==child){
    children.remove(n);
    return;
  }
}

void Widget::drawClippedLine(int x, int y, int x1, int y1, Color c){

  Rect r = view;

  if(x>=r.x+r.w&&x1>=r.x+r.w) return;
  if(y<r.y&&y1<r.y) return;

  if(x1>=r.x+r.w){
    int lx = x;
    int ly = y;
    while(x1!=r.x+r.w-1){
      int x=(lx+x1)>>1;
      if(x>=r.x+r.w-1){
        x1=x;
        y1=(ly+y1)>>1;
      }else{
        lx=x;
        ly=(ly+y1)>>1;
      }
    }
  }
  if(y1<r.y){
    int lx = x;
    int ly = y;
cout << x << ',' << y << endl;      
cout << x1 << ',' << y1 << endl;      
    while(y1!=r.y){
      int y=(ly+y1)>>1;
      if(y<=r.y){
        y1=y;
        x1=(lx+x1)>>1;
      }else{
        ly=y;
        lx=(lx+x1)>>1;
      }
    }
  }

  if(y<r.y||y1<r.y) return;
  if(x<r.x||x1<r.x) return;
  if(y>=r.y+r.h||y1>=r.y+r.h) return;
  if(x>=r.x+r.w||x1>=r.x+r.w) return;

  drawLine(x,y,x1,y1,c);
}
