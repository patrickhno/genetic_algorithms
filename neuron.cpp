// neuron.cpp  - copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "neuron.h"

using namespace std;

inline int irand( int range ){
  return( rand() % range );
}

inline double drand(){
  return double((rand()%10000)-5000)/10000.0;
}

// Create a single neuron and connect it to input neurons
// input: input  = input neurons
//        inputs = number of input neurons
//        type   = unused
//        a & b  = normalization (min & max)

Neuron::Neuron(Neuron **input, int inputs, int type, double a, double b){
  if(inputs>5){
    // clamp if we have more then 5 inputs, and use 5 random'ish of them
    this->input = input+rand()%(inputs-5);
    inputs = 5;
  }else{
    this->input = input;
  }
  this->inputs = inputs;
#ifdef HEAVY
  weight = new float[7*inputs];
  for(int n=0; n<inputs*7; n++) weight[n] = 1;
  for(int n=0; n<7; n++) base[n] = 0;
#else
  weight = new float[inputs];
  for(int n=0; n<inputs; n++) weight[n] = irand((b-a)*1000.0f)/1000.0f-(b-a)/2.0f;
  base = irand((b-a)*1000.0f)/1000.0f-(b-a)/2.0f;
  function = 0;
#endif
}

Neuron::~Neuron(){
}

// initialize a neuron with new input's and randomize weights
// input: input  = input neurons
//        inputs = number of input neurons
//        type   = unused
//        a & b  = normalization (min & max)

void Neuron::construct(Neuron **input, int inputs, int type, double a, double b){
  if(inputs>4){
    // clamp if we have more then 4 inputs, and use 4 random'ish of them
    this->input = input+rand()%(inputs-4);
    inputs = 4;
  }else{
    this->input = input;
  }
  this->inputs = inputs;
#ifdef HEAVY
  weight = new float[7*inputs];
  for(int n=0; n<inputs*7; n++) weight[n] = drand()*100.0;
  for(int n=0; n<7; n++) base[n] = drand()*100.0;
#else
  weight = new float[inputs];
  for(int n=0; n<inputs; n++) weight[n] = irand((b-a)*1000.0f)/1000.0f-(b-a)/2.0f;
  base = irand((b-a)*1000.0f)/1000.0f-(b-a)/2.0f;
#endif
}

// initialize with random weights
// input: type   = unused
//        a & b  = normalization (min & max)

void Neuron::init(int type, double a, double b){
#ifdef HEAVY
  for(int n=0; n<inputs*7; n++) weight[n] = drand();
  for(int n=0; n<7; n++) base[n] = drand();
#else
  for(int n=0; n<inputs; n++) weight[n] = irand((b-a)*1000.0f)/1000.0f-(b-a)/2.0f;
  base = irand((b-a)*1000.0f)/1000.0f-(b-a)/2.0f;
#endif
}

// Make this neuron a mix of self and other
// input: n = other neuron

void Neuron::mix(Neuron *n){
#ifdef HEAVY
  if(inputs==n->inputs){
    for(int i=0; i<inputs*7; i++) weight[i] = (weight[i]+n->weight[i])*.5+drand()*.01;
    for(int i=0; i<7; i++) base[i] = (base[i]+n->base[i])*.5+drand()*.01;
  }
#else
  if((inputs==n->inputs)&&function==n->function){
    for(int i=0; i<inputs; i++) weight[i] = (weight[i]+n->weight[i])/2.0;
    base = (base+n->base)/2.0;
  }
#endif
}

Neuron &Neuron::operator=(Neuron &s){
  if(inputs!=s.inputs){
    cerr << "bad!" << endl;
    exit(EXIT_FAILURE);
  }
#ifdef HEAVY
  for(int n=0; n<inputs*7; n++) weight[n]=s.weight[n];
  for(int n=0; n<7; n++) base[n]=s.base[n];
  val=s.val;
#else
  for(int n=0; n<inputs; n++) weight[n]=s.weight[n];
  base     = s.base;
  function = s.function;
#endif
  return *this;
}

// Make this neuron the child of neuron a and b
// input: a & b = neurons to sex up
//        w     = weight (0 -> 1)

void Neuron::breed(double w, Neuron *a, Neuron *b){
  if(a->inputs!=b->inputs&&inputs!=a->inputs){
    cerr << "!!!!!!!!!!" << endl;
  }
  for(int n=0; n<inputs*7; n++) weight[n]=a->weight[n]*w+b->weight[n]*(1.0-w);
  for(int n=0; n<7; n++) base[n]=a->base[n]*w+b->base[n]*(1.0-w);
  val=a->val*w+b->val*(1.0-w);
}

#define MAX 1.0

// Apply a litte radiation to this neuron and mutate weights a bit
// input: v = radiation

void Neuron::mutate(double v){
  int i = irand(inputs*8);
  if(i<inputs*7){
    weight[i]+=drand()*v;
    if(weight[i]>MAX) weight[i]=MAX;
    else if(weight[i]<-MAX) weight[i]=-MAX;
  }else{
    i-=inputs*7;
    base[i]+=drand()*v;
    if(base[i]>MAX) base[i]=MAX;
    else if(base[i]<-MAX) base[i]=-MAX;
  }
}

