// copyright (C) 2001-2011 by Patrick Hanevold

#include "sinTest.h"
#include "net.h"
#include "gui/screen.h"
#include "gui/graph.h"
#include "gui/grid.h"
#include "population.h"

SinTest::SinTest() : Genetic(2,400,8,1){
}

// set calibration factors of a neural net
// input: net = a neural net from the population

void SinTest::calibrate(Net *net){
  net->setCalibration(-1,1);
}

// evaluate and stimulate a neural net. Todo?: Futuristic punishment/reward
// inputs: net = neural net to evaluate

void SinTest::evaluate(Net *net){
  int i=rand()%1000;
  for(int n=0; n<8; n++) net->setInput(n,double(i)/1000.0);
  net->run();
  stimulate(net,-fabs(sin(double(i*3)/1000.0)-*net->getOutput()));
}

bool SinTest::criteria(Net *net){
  if(net->getAge()<60) return false;  // keep youngsters out of the score board
  return true;
}


// start evolution of neural networks!

void SinTest::go(){
  Screen scr(640,512);
  Graph<double> score;
  Graph<int> age;
  Graph<double> sample;
  Graph<double> sample2;
  Grid grid(&scr);
  grid.attach(&score);
  grid.attach(&sample);
  grid.attach(&age);
  grid.attach(&sample2);
  while(true){
    for(int n=0; n<10; n++) nextGeneration();
    sample.clear();
    sample2.clear();
    Net *net = getPopulation(0)->getIndividual(0);
    for(int i=0; i<100; i++){
      for(int n=0; n<8; n++) net->setInput(n,double(i)/100.0);
      net->run();
      sample.add(*net->getOutput());
      sample2.add(sin(double(i*3)/100.0));
    }
    score.add(getBoardScore());
    age.add(getBoardAge());
    scr.render(Rect(0,0,640,512));
  }
}
