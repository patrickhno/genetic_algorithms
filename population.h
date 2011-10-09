// population.h - copyright (C) 2001-2011 by Patrick Hanevold

class Net;

class Population{
public:   Population(int individuals, int inputs, int outputs, double a, double b);
  void    init(int induvidual, double a, double b);
  void    mix(int i, int j);
  void    mutate(int induvidual, double level);
  void    copy(int individual1, int individual2);
  void    copy(int individual1, Population *population, int individual2);
  void    swap(int individual1, int individual2);
  Net     *getIndividual(int i);
  void    sort(int safearea, class Genetic *gen);
private:
  int     individuals;
  Net     **individual;
};

