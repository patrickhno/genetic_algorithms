// copyright (C) 2001-2011 by Patrick Hanevold

#ifndef _GENETIC_H
#define _GENETIC_H

class Population;
class Net;

class Genetic{
public:       Genetic(int populations, int induviduals, int inputs, int outputs);
  virtual     ~Genetic(){}

          Population  *getPopulation(int n){ return population[n]; }
          void        nextGeneration();
          void        stimulate(Net *net, double score);
          void        setTrainingPeriod(int start, int end);
  virtual void        initGeneration(){}
  virtual double      getInput(int t){ return 0; }
  virtual void        evaluate(Net *) = 0;
  virtual void        calibrate(Net *net){}
  virtual bool        criteria(Net *net){ return true; }
          double      getEval(int t);
          void        setEval(int t, double v);
          double      getBoardScore(){ return board_score; }
          int         getBoardAge(){ return board_age; }
private:
          int         inputs;
          int         startscore;
          int         start;
          int         stop;
          int         generation;
          int         individuals;
          int         populations;
          Population  **population;
          bool        newgen;
          double      min,max;
          double      *val;
          int         lastage;
          double      board_score;
          int         board_age;
};

#endif
