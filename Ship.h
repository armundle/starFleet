#pragma once
//Cuboid class to store the grid, perform operations on the grid

#include "common.h"


class Ship
{
    public:
    //todo:what about rest of the constructors?
    Ship(GridType& g);
    ~Ship() {};

    //todo:does this need to be exposed?
    const GridType& getGrid();
    const size_t getGridSizeX();
    const size_t getGridSizeY();

    void printGrid();

    void fire(const FirePatternStringType& pattern);
    void move(const MoveType& move);
    void drop();
    bool missedMine();

    //todo:make private
    const Position& getCenter();

    private:

    GridType& _grid;

    //todo:eh... does this belog here?
    Position _center;
    bool _missedMine;
    
    void _destroyMine(std::vector<Position> p);
    void _updateShipCenter(const Position& p);
    void _resizeGrid(const MoveType& move);
    
    bool _outOfBounds(int x, int y);
    
    void _trim();
};
