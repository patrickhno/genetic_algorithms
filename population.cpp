// population.cpp - copyright (C) 2001-2011 by Patrick Hanevold

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "population.h"
#include "net.h"
#include "genetic.h"

using namespace std;

//#define MAXPOP  60    /* Size of population */
//#define BESTPOP 4     /* Number of individuals taken from the best */
//#define SELPOP  8     /* SELPOP-BESTPOP = Number of people selected randomly on each gen. */
//#define NEWPOP  18    /* NEWPOP-SELPOP = Number of new people, created randomly on each gen. */
//#define MUT1    25    /* MUT1-NEWPOP = Number of mutations in the first mutation group */
//#define MIXGEN  10    /* Number of generations between population mixing */

inline int irand( int range ){
  return( rand() % range );
}

// Create a population of individual neural networks
// input: individuals = the number of neural networks to create in the population
//        inputs      = the number of inputs in every neural network
//        outputs     = the number of outputs in every neural network
//        a & b       = neuron normalization values (min & max)

Population::Population(int individuals, int inputs, int outputs, double a, double b){
  this->individuals = individuals;
  int layers = 0;
  for(int n=inputs; n>outputs; n/=2) layers++;
  typedef Net* netptr;
  individual = new netptr[individuals];
  for(int n=0; n<individuals; n++){
    individual[n] = new Net(inputs,outputs,layers,a,b);
  }
}

// initialize a neural network with random weights
// input: i     = which neural network in the population to initialize
//        a & b = neuron normalization values (min & max)

void Population::init(int i, double a, double b){
  individual[i]->init(a,b);
}

// mutate a single neuron with another by randomized blending
// input: i = the neural network to mix a random neuron in
//        j = the other neural network to mix a random neuron with (random source neuron)

void Population::mix(int i, int j){
  individual[i]->mix(individual[j]);
}

// mutate a random neuron in a neural network by radiation (noise blending)
// input: i     = whch neural network to radiate a random neuron
//        level = radiation level

void Population::mutate(int i, double level){
  individual[i]->mutate(level);
}

void Population::copy(int i1, int i2){
  (*individual[i1]) = (*individual[i2]);
}

void Population::copy(int i1, Population *pop, int i2){
  *individual[i1] = *pop->getIndividual(i2);
}

void Population::swap(int i1, int i2){
  Net *t = individual[i1];
  individual[i1] = individual[i2];
  individual[i2] = t;
}

Net *Population::getIndividual(int i){
  return individual[i];
}

// inperfectly sort the population according to fitness
// input: cnt = the number of iterations in the sort algorithm (simple bouble sorting)
//        gen = the gene pool the population belong to

void Population::sort(int cnt, Genetic *gen){
  // first evaluate all individuals in population
  double *scores = new double[individuals];
  for(int n=0; n<individuals; n++){
    gen->evaluate(individual[n]);
    scores[n]=individual[n]->getScore();
    if(isinf(scores[n])) scores[n]=-10000000;
  }

  // then sort the entire population according to score (lame sort)
  for(int n=0; n<cnt; n++){    
    for(int i=0 ; i<(individuals-1); i++){
      if(scores[i+1]>scores[i]){
        swap(i,i+1);
        double a=scores[i];
        scores[i]=scores[i+1];
        scores[i+1]=a;
      }
    }
  }
  delete []scores;
}

