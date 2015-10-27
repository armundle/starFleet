all: starFleet

starFleet: main.o Ship.o
	g++ main.o Ship.o -o starFleet

main.o: main.cpp
	g++ -c main.cpp

Ship.cpp.o: Ship.cpp
	g++ -c Ship.cpp

clean:
	rm *o