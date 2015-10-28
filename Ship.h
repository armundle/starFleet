#pragma once
//Cuboid class to store the grid, perform operations on the grid

#include "types.h"
#include "Cuboid.h"

class Ship
{
    struct Position
    {
        int x;
        int y;
    
        Position(int xIn = 0, int yIn = 0) : x(xIn), y(yIn)
        {
        }
    };

    typedef struct Position Position;
    
    public:
    //todo:what about rest of the constructors?
    Ship(Cuboid& c);
    ~Ship() {};

    int fire(const FirePatternStringType& pattern);
    void move(const MoveType& move);

    private:

    Cuboid& _grid;
    Position _center;

    void _recalCenter();
    bool _outOfBounds(int x, int y);
    
    int _destroyMine(std::vector<Position> p);
    void _updateShipCenter(const Position& p);
    
    //helper methods
    typedef std::vector<Position> FirePatternNumType;

    Position _createPosition(int x, int y);
    std::vector<Position> _convertPatternToNumVector(const FirePatternStringType& s);
    Position _convertMoveToNum(const MoveType& move);
};