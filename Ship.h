#pragma once
//Cuboid class to store the grid, perform operations on the grid

#include "types.h"
#include "Cuboid.h"

class Ship
{
    public:
    //todo:what about rest of the constructors?
    Ship(Cuboid& c);
    ~Ship() {};

    //todo:does this need to be exposed?
    //const GridType& getGrid();
    //const size_t getGridSizeX();
    //const size_t getGridSizeY();

    //void printGrid();

    int fire(const FirePatternStringType& pattern);
    void move(const MoveType& move);
    //void drop();
    //bool missedMine();

    //todo:make private
    const Position& getCenter();

    private:

    Cuboid& _grid;

    //todo:eh... does this belog here?
    Position _center;
    //bool _missedMine;
    
    void _recalCenter();
    int _destroyMine(std::vector<Position> p);
    void _updateShipCenter(const Position& p);
    //void _resizeGrid(const MoveType& move);

    bool _outOfBounds(int x, int y);

    //void _trim();
};
