all: evaluate

evaluate: evaluate.o Simulator.o Grid.o Cuboid.o Ship.o
	g++ -Wall evaluate.o Simulator.o Grid.o Cuboid.o Ship.o -o evaluate

evaluate.o: evaluate.cpp Simulator.o
	g++ -c -Wall evaluate.cpp

Simulator.o: Simulator.cpp Grid.o Cuboid.o Ship.o
	g++ -c -Wall Simulator.cpp

Ship.o: Ship.cpp Cuboid.o
	g++ -c -Wall Ship.cpp

Grid.o: Grid.cpp
	g++ -c -Wall Grid.cpp

Cuboid.o: Cuboid.cpp
	g++ -c -Wall Cuboid.cpp

clean:
	rm *o evaluate
