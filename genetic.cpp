// population.cpp  -  copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "genetic.h"
#include "population.h"
#include "net.h"

using namespace std;

inline int irand( int range ){
  return( rand() % range );
}

// Create a genetic pool. A pool of many populations of neural networks that will evolve through evolution.
// input: pupulations = the number of populations
//        individuals = the number of neural networks in each population
//        inputs      = the number of inputs for each neural network
//        outputs     = the number of outputs for each neural network

Genetic::Genetic(int populations, int individuals, int inputs, int outputs){
  generation = 0;
  this->populations = populations;
  this->individuals = individuals;
  this->inputs      = inputs;
  double a=1;
  double b=2;
  startscore = 20000;
  start = 0;
  stop = 0;
  typedef Population* popptr;
  population = new popptr[populations];
  for(int n=0; n<populations; n++) population[n] = new Population(individuals,inputs,outputs,a,b);
  val = 0;
  lastage = 0;
}

// evolve: iterate evolution to the next generation

void Genetic::nextGeneration(){

  initGeneration();

  newgen = true;

  int keep = 6;
  int swap = 6;
  int init = 70;
  int muts = 10;
//  int cros = 100-(keep+swap+init+muts);
  int mixgen = 10;

  // parameters to divide population into defied classes
  int bestpop = keep*individuals/100;                    // all above, strong criteria elite club
  int selpop  = (keep+swap)*individuals/100;             // all above, select parents to breed
  int newpop  = (keep+swap+init)*individuals/100;        // all above are untouched, pool is mutated
  int mut1    = (keep+swap+init+muts)*individuals/100;   // all below, kill, and breed new

  // increase age of population and sort populations according to fitness
  for(int p=0 ; p<populations; p++){
    for(int i=0; i<individuals; i++) population[p]->getIndividual(i)->age++;
    population[p]->sort(50,this);
  }

  // mutate and interbreed populations
  for(int p=0 ; p<populations; p++){
    for(int i=individuals-50; i<individuals; i++){
    //if(populations>1&&(generation%mixgen)==0){
    //  population[p]->copy(i, population[irand(populations)], newpop?irand(newpop):0);
    //  population[p]->mix(i,newpop?irand(newpop):0);
    //}else{
      switch(irand(4)){
      case 0:
        // clone and mutate
        population[p]->copy(i,irand(newpop));
        switch(irand(7)){
        case 0: population[p]->getIndividual(i)->mutate(double(irand(1000000))/100000000.0); break;
        case 1: population[p]->getIndividual(i)->mutate(double(irand(1000000))/10000000.0); break;
        case 2: population[p]->getIndividual(i)->mutate(double(irand(1000000))/1000000.0); break;
        case 3: population[p]->getIndividual(i)->mutate(double(irand(1000000))/100000.0); break;
        case 4: population[p]->getIndividual(i)->mutate(double(irand(1000000))/10000.0); break;
        case 5: population[p]->getIndividual(i)->mutate(double(irand(1000000))/1000.0); break;
        case 6: population[p]->getIndividual(i)->mutate(double(irand(1000000))/100.0); break;
        }
        break;
      case 1:
        // mix populations
        population[p]->copy(i, population[irand(populations)], newpop?irand(newpop):0);
        population[p]->mix(i,newpop?irand(newpop):0);
        break;
      case 2:
        // randomize weights
        population[p]->getIndividual(i)->init(0,0);
        break;
      default:
        // breed
        int a=irand(selpop);
        int b=irand(selpop);
        while(b==a) b=irand(selpop);
        population[p]->getIndividual(i)->breed(population[p]->getIndividual(a),population[p]->getIndividual(b));
      }
    //}
    }
  }

  // sumarize how the poluation is doing (evolving)
  generation++;
  board_score=0;
  board_age=0;
  for(int p=0 ; p<populations; p++){
    for(int n=0; n<bestpop; n++){
      board_score+=population[p]->getIndividual(n)->getScore();
      board_age+=population[p]->getIndividual(n)->getAge();
    }
  }
  board_score/=bestpop*populations;
  board_age/=bestpop*populations;
}

// award neural net with score
// inputs: net   = neural network to award
//         score = the score given to the network during evaluation

void Genetic::stimulate(Net *net, double score){
  if(!net->calibrated) calibrate(net);
  if(newgen){ max=min=score; newgen=false; }
  else{
    if(score<min) min=score;
    if(score>max) max=score;
  }
  net->score += score;
}

void Genetic::setTrainingPeriod(int start, int stop){
  this->start = start;
  this->stop  = stop;
  if(val) delete val;
  val = new double[stop-start];
}

/*
void Genetic::setEval(int t, double v){
  val[t-start] = v;
}

double Genetic::getEval(int t){
  return val[t-start];
}
*/
