// population.cpp  -  copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "layer.h"
#include "neuron.h"

using namespace std;

inline int irand( int range ){
  return( rand() % range );
}

// Create a layer of neurons
// input: inputs  = number of inputs
//        outputs = number of outputs
//        a & b   = normalization value for the neurons (min & max)

Layer::Layer(int inputs, int outputs, double a, double b){
  this->inputs = inputs;
  this->outputs = outputs;
  typedef Neuron* nptr;
  input = new nptr[inputs];
  neuron = new Neuron[outputs];
  for(int n=0; n<outputs; n++) neuron[n].construct(input,inputs,rand()%3,a,b);
}

Layer::~Layer(){
  delete neuron;
}

// initialize all neurons in the layer with random weights
// input: a & b = normalization values (min & max)

void Layer::init(double a, double b){
  for(int n=0; n<outputs; n++) neuron[n].init(rand()%3,a,b);
}

// set other layers output neurons as inputs to self
// intput: l = other layer with output neurons

void Layer::setInputs(Layer *l){
  for(int i=0; i<l->outputs; i++){
    input[i] = &l->neuron[i];
  }
}

Layer &Layer::operator=(Layer &s){
  if(outputs!=s.outputs){
    cerr << "Layer::operator = cannot copy layer!" << endl;
    exit(EXIT_FAILURE);
  }
  for(int n=0; n<outputs; n++) neuron[n]=s.neuron[n];
  return *this;
}

// fire all neurons

void Layer::run(){
  for(int n=0; n<outputs; n++) neuron[n].run();
}

