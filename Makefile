all: starFleet

starFleet: main.o Simulator.o Grid.o Cuboid.o Ship.o
	g++ main.o Simulator.o Grid.o Cuboid.o Ship.o -o starFleet

main.o: main.cpp
	g++ -c main.cpp

Simulator.o: Simulator.cpp
	g++ -c Simulator.cpp
	
Grid.o: Grid.cpp
	g++ -c Grid.cpp
	
Cuboid.o: Cuboid.cpp
	g++ -c Cuboid.cpp

Ship.o: Ship.cpp
	g++ -c Ship.cpp

clean:
	rm *o starFleet
