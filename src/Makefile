CFLAGS = -Wall
ROOT_DIR = ..

all: evaluate

evaluate: evaluate.o Simulator.o Grid.o Cuboid.o Ship.o
	@echo Building $@ ...
	g++ $(CFLAGS) evaluate.o Simulator.o Grid.o Cuboid.o Ship.o -o $(ROOT_DIR)/evaluate

evaluate.o: evaluate.cpp Simulator.o
	g++ -c $(CFLAGS) evaluate.cpp

Simulator.o: Simulator.cpp Grid.o Cuboid.o Ship.o
	g++ -c $(CFLAGS) Simulator.cpp

Ship.o: Ship.cpp Cuboid.o
	g++ -c $(CFLAGS) Ship.cpp

Grid.o: Grid.cpp
	g++ -c $(CFLAGS) Grid.cpp

Cuboid.o: Cuboid.cpp
	g++ -c $(CFLAGS) Cuboid.cpp

clean:
	rm *o ../evaluate