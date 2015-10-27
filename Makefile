all: starFleet

starFleet: main.o Cuboid.o Ship.o
	g++ main.o Cuboid.o Ship.o -o starFleet

main.o: main.cpp
	g++ -c main.cpp
	
Cuboid.o: Cuboid.cpp
	g++ -c Cuboid.cpp

Ship.o: Ship.cpp
	g++ -c Ship.cpp

clean:
	rm *o