// copyright (C) 2001-2011 by Patrick Hanevold

#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SDL/SDL.h>
#ifdef HAVE_SDL_TTF
#include <SDL/SDL_ttf.h>
#endif
#include "color.h"
#include "rect.h"
#include "../array.h"

class Widget{
public:                   Widget();
                          Widget(Widget *parent);
                          ~Widget();
          Widget          *getParent() const;
  const   Array<Widget*>  *getChildren() const;
          void            attach(Widget *child);
          void            detach(Widget *child);
  virtual void            render(Rect r);
//          Rect            getView();
//          void            setView(Rect r);
  static  void            (*fillRect)(Rect r, Color c);
  static  void            (*drawLine)(int x, int y, int x1, int y1, Color c);
  static  void            (*drawCircle)(int x, int y, int d, Color c);
          void            noRender(){ dorender = false; }
          void            drawClippedLine(int x, int y, int x1, int y1, Color c);
private:
  friend  class           Screen;
  friend  class           TickerWidget;
#ifdef HAVE_SDL_TTF
  static  TTF_Font        *font;
#endif
          Widget          *parent;
          Array<Widget*>  children;
          Rect            view;
          bool            dorender;
};

#endif
