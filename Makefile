all: starFleet

starFleet: main.o Simulator.o Grid.o Cuboid.o Ship.o
	g++ -Wall main.o Simulator.o Grid.o Cuboid.o Ship.o -o starFleet

main.o: main.cpp
	g++ -c -Wall main.cpp

Simulator.o: Simulator.cpp
	g++ -c -Wall Simulator.cpp
	
Grid.o: Grid.cpp
	g++ -c -Wall Grid.cpp
	
Cuboid.o: Cuboid.cpp
	g++ -c -Wall Cuboid.cpp

Ship.o: Ship.cpp
	g++ -c -Wall Ship.cpp

clean:
	rm *o starFleet
