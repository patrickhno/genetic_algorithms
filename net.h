// net.h  -  copyright (C) 2001-2011 by Patrick Hanevold

#include "layer.h"
#include "neuron.h"

class Net{
public:   Net(int inputs, int outputs, int layers, double a, double b);
  void    init(double a, double b);
  void    run();
  void    mix();
  void    mix(int n1, int n2);
  void    mix(Net *);
  void    mutate(double dev);
//  void    calcScore(class Genetic *);
  Net     &operator=(Net &);
  double  getScore();//{ return score; }
  void    setInput(int n, float val){
    //cout << n << "," << layer[0]->inputs << endl;
    //cout << layer[0]->input[n] << endl;
    layer[0]->input[n]->val = val;
  }
  double  *getOutput(){ return output; }
  void    breed(Net *a, Net *b);
  void    setCalibration(double min, double max);
  int     getAge(){ return age; }
private:
friend class Population;
friend class Genetic;
  int     neurons,layers;
  Neuron  **neuron;
  Layer   **layer;
  double  score;
  int     outputs;
  double  *output;
  int     age;
  double  max,min;
  bool    calibrated;
  int     name;
};
