// population.cpp  -  copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "net.h"
#include "genetic.h"

using namespace std;

inline int irand( int range ){
  return( rand() % range );
}

// Create a neural network
// input: inputs  = number of input
//        outputs = number of outputs
//        layers  = the number of layers of neurons to have in the neural net
//        a & b   = normalization values for the neurons (min & max)

Net::Net(int inputs, int outputs, int layers, double a, double b){
  this->layers = layers;
  this->outputs = outputs;
  typedef Layer* layerptr;
  layer = new layerptr[layers];
  output = new double[outputs];
  int ip = inputs;
  int op = inputs/2;
  for(int n=0; n<layers; n++){
    layer[n] = new Layer(ip,op>outputs?op:outputs,a,b);
    ip/=2;
    op/=2;
  }
  for(int n=0; n<layer[0]->inputs; n++) layer[0]->input[n] = new Neuron((Neuron**)0,0,0,a,b);
  for(int n=1; n<layers; n++) layer[n]->setInputs(layer[n-1]);
  neurons = 0;
  for(int n=0; n<layers; n++) neurons+=layer[n]->outputs;
  typedef Neuron* nptr;
  neuron = new nptr[neurons];
  int ni=0;
  for(int n=0; n<layers; n++){
    for(int i=0; i<layer[n]->outputs; i++) neuron[ni++] = &layer[n]->neuron[i];
  }
  if(ni!=neurons){ cout << "!!!!!!!!!!!!!!" << endl; exit(0); }
  age = 30;//irand(10);
  score=0;
  max=1;
  min=0;
  calibrated = false;

  name = 0x12345678;
}

// initialize the net with random weights
// input: a & b = normalization values (min & max)

void Net::init(double a, double b){
  for(int n=0; n<layers; n++) layer[n]->init(a,b);
  age = 0;//irand(10);
  score=0;
  max=1;
  min=0;
  calibrated = false;
}

// mutate a single neuron with another by randomized blending

void Net::mix(){
  neuron[irand(neurons)]->mix(neuron[irand(neurons)]);
}

// fire all neurons in the net (basic propagation algorithm)

void Net::run(){
  for(int n=0; n<layers; n++) layer[n]->run();
  for(int n=0; n<outputs; n++) output[n] = (layer[layers-1]->neuron[n].val-min)/(max-min);
}

// mutate a single neuron with another from other net (in population) by randomized blending
// input: other neural network

void Net::mix(Net *net){
  neuron[irand(neurons)]->mix(net->neuron[irand(net->neurons)]);
}

// mutate neural net by radiation (noise blending)
// input: dev = radiation factor

void Net::mutate(double dev){
  int cnt=rand()%neurons;
  for(int n=0; n<cnt; n++) neuron[rand()%neurons]->mutate(dev/double(cnt));
  age=0;
  score=0;
  min=0;
  max=1;
  calibrated=false;
}

// 

double Net::getScore(){
  return score/double(age);
}

Net &Net::operator=(Net &s){
  if(neurons!=s.neurons||layers!=s.layers){
    cerr << "bad!" << endl;
    exit(EXIT_FAILURE);
  }
  for(int n=0; n<layers; n++) (*layer[n])=(*s.layer[n]);
  age=0;
  score=0;
  min=0;
  max=1;
  calibrated=false;
  return *this;
}

inline double drand(){
  return double((rand()%10000)-5000)/10000.0;
}

// let this neural net be the result of breeding. (blending and light mutation)
// input: a & b = neural networs to have intercource

void Net::breed(Net *a, Net *b){
  double w = drand()+.5;
  for(int n=0; n<neurons; n++){
    neuron[n]->breed(w,a->neuron[n],b->neuron[n]);
  }
  //neuron[rand()%neurons]->mutate(.001);
  mutate(drand()+.5);
  age=0;
  score=0;
  min=0;
  max=1;
  calibrated=false;
}

void Net::setCalibration(double min, double max){
  this->min = min-(min-max)*.5;
  this->max = max-(min-max)*.5;
  calibrated = true;
}

