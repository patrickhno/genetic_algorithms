// neuron.h  - copyright (C) 2001-2011 by Patrick Hanevold

#include <math.h>
#ifndef M_PI
# define M_PI               3.14159265358979323846
#endif

class Neuron{
public:   Neuron(){}
          Neuron(Neuron **inp, int inputs, int type, double a, double b);
          ~Neuron();

  void    construct(Neuron **inp, int inputs, int type, double a, double b);
  void    init(int type, double a, double b);

  // genetic manipulators
  void    mix(Neuron *n);
  void    mutate(double level);
  void    breed(double w, Neuron *a, Neuron *b);

  Neuron  &operator=(Neuron &);

  // ********* inline optimized functions ************

  inline double scalar_mult(float *w){
    double val=0;
    for(int n=0; n<inputs; n++) val += input[n]->val*w[n];
    return val/inputs;
  }

  // fire neuron
  inline void run(){
    // scalar multiply
#ifndef HEAVY
    val = 0;
    for(int n=0; n<inputs; n++) val += input[n]->val*weight[n];
    switch(function){
    case 0: // atan transfer function
      val = float(M_PI*atan(val+base)/1.6);
      break;
    case 1: // hardlim transfer function
      val = float((val+base)>0);
      break;
    default: // linear transfer function
      val+=base;
    }
#else
    double a1 = M_PI*atan( scalar_mult(&weight[0*inputs]) + base[0] )/1.6;  /* atan transfer function */
    double a2 = M_PI*atan( scalar_mult(&weight[1*inputs]) + base[1] )/1.6;  /* atan transfer function */
    int    a3 =     ( scalar_mult(&weight[2*inputs]) + base[2] ) > 0;          /* hardlim transfer function */
    int    a4 =     ( scalar_mult(&weight[3*inputs]) + base[3] ) > 0;          /* hardlim transfer function */
    double a5 =       scalar_mult(&weight[4*inputs]) + base[4] ;                 /* linear transfer function */
    double a6 =       scalar_mult(&weight[5*inputs]) + base[5] ;                 /* linear transfer function */
    val =
      a1*weight[6*inputs+0] +
      a2*weight[6*inputs+1] +
      a3*weight[6*inputs+2] +
      a4*weight[6*inputs+3] +
      a5*weight[6*inputs+4] +
      a6*weight[6*inputs+5] + base[6];         /* hardlim transfer function */
#endif
  }


private:
friend class Net;

  unsigned short inputs;
  Neuron  **input;
  float   *weight;
#ifdef HEAVY
  float   base[7];
#else
  unsigned short function;
  float   base;
#endif
  float   val;
};

