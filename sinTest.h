// copyright (C) 2001-2011 by Patrick Hanevold

#ifndef _SINTEST_H_
#define _SINTEST_H_

#include "genetic.h"
#include "array.h"

class Net;

class SinTest : Genetic{
public:  SinTest();
  void   evaluate(Net *net);
  void   calibrate(Net *net);
  bool   criteria(Net *net);
  void   go();
  int    hist_i;
  Array<int> board;
};

#endif
