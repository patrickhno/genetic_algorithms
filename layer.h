// layer.h  -  copyright (C) 2001-2011 by Patrick Hanevold

class Neuron;

class Layer{
public:   Layer(int inputs, int outputs, double a, double b);
          ~Layer();
  void    run();
  void    init(double a, double b);
  void    setInputs(Layer *l);
  Layer   &operator=(Layer &);
private:
friend class Net;
  int     inputs,outputs;
  Neuron  **input;
  Neuron  *neuron;
};

