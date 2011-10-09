
## Simple demonstration of Evolution of Neural Networks using Genetic Algorithms
                      (C) 2001-2011 Patrick Hanevold

=============================================================================

This is something I played with back in 2001 that someone may find amusing.

Besides a simple SDL based Widget-GUI framework this demonstration includes
the following files.

This demonstration contains a test application utilizing the genetic
algorithms API by simply trying to predict a sinus function - which it does
well.

This GA framework is also tested on predicting sunspot activity and
stock market activity and does so as well as can be expected from statistical
computations.

## Brief description of Genetic Algorithms

Essentially, Genetic Algorithms (GA) are a method of "breeding" computer
programs and solutions to optimization or search problems by means of
simulated evolution. Processes loosely based on natural selection,
crossover, and mutation are repeatedly applied to a population of neural
networks which represent potential solutions. Over time, the number of
above-average individuals increases, and better fit individuals are created,
until a good solution to the problem at hand is found.

Our genetic algorithm works with not one but multiple populations, all of
which in a large degree evolve separately except for minor interbreeding
where we allow different populations to mix with each other.

## Files of interest

genetic    - the top API for the algorithm. Containing populations of neural networks.
population - the population container containing a population of neural nets
net        - the neural net containing multiple layers of neurons
layer      - the layer container containing a layer neurons
neuron     - neural networks consists of neurons, this is the neuron

sinTest    - the test application.

## License

(The MIT License)

Copyright (c) 2011 Patrick Hanevold

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ‘Software’), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED ‘AS IS’, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
