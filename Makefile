
# genetic algorithms - evolution of neural networks using genetic algorithms

OBJECTS = main.o genetic.o population.o net.o layer.o neuron.o sinTest.o gui/widget.o gui/rect.o string.o gui/color.o gui/screen.o

all: ga

clean:
	rm ga $(OBJECTS)

ga: $(OBJECTS)
	g++ -o ga $(OBJECTS) -framework SDL -framework Cocoa

%.o: %.cpp
	g++ -DHEAVY -DHISTORY=15 -DFUTURE=15 -I/Library/Frameworks/SDL.framework/Headers -c -O2 -o $@ $< # -framework SDL -framework Cocoa


