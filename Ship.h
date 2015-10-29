#pragma once

#include "types.h"
#include "Cuboid.h"

/* Ship class:
 * A simulator can send fire or move commands to a ship.
 * The ship can destroy a mine at a specific location in the grid and return if
 * a mine was destroyed. It translates the fire pattern and move commands into
 * position coordinates.
 */

class Ship
{
    private:
    //ship's coordinate wrapper
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

    //fire with the specified pattern
    //returns the number of mines destroyed
    int fire(const FirePatternStringType& pattern);

    //move as specified by the Simulator
    void move(const MoveType& move);

    private:

    Cuboid& _grid;
    Position _center;

    /*helper functions*/

    //recalibrate the center according to the cuboid's dimensions
    void _recalCenter();
    //if the input coordinates are out of cuboid's bounds
    //return false
    bool _outOfBounds(int x, int y);

    //destroy mine using a vector of positions
    int _destroyMine(std::vector<Position> p);
    //update center of the ship according to the specified position
    void _updateShipCenter(const Position& p);

    //given x, y coordinates, return as a Position type
    Position _createPosition(int x, int y);

    typedef std::vector<Position> FirePatternNumType;

    //convert fire pattern as input from simulator to a vector of Positions
    std::vector<Position> _firePatternToPosition(const FirePatternStringType& s);

    //convert move as specified by the simulator to a Position type
    Position _moveToPosition(const MoveType& move);
};
