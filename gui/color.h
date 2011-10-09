// color.h  -  copyright (C) 2001-2011 by Patrick Hanevold

#ifndef _COLOR_H_
#define _COLOR_H_

class Color{
public:   Color();
          Color(double r, double g, double b);
  Color   &operator=(const Color &c);
  double  red,green,blue;
};

#endif
