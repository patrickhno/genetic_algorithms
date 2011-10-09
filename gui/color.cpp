// color.cpp  -  copyright (C) 2001-2011 by Patrick Hanevold

#include "color.h"

Color::Color(){
}

Color::Color(double r, double g, double b){
  red = r;
  green = g;
  blue = b;
}

Color &Color::operator=(const Color &c){
  red   = c.red;
  green = c.green;
  blue  = c.blue;
  return *this;
}
