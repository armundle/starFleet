#pragma once

#include <string>
#include <deque>
#include "types.h"
#include "Ship.h"
#include "Grid.h"
#include "Cuboid.h"

/* Simulator class:
 * Reads the field file and stores into a grid object.
 * Read the field file and stores the commands into a Queue.
 * Using the above two, it sends fire or move commands to the ship each time
 * it is run.
 * A user can query if the simulation is complete, if the end of script was
 * reached, number of fire commands received, number of move commands received,
 * number of initial mines in the field, and the number of mines remaining
 * at a given point in the simulation.
 */

class Simulator
{
    public:
        Simulator(const char* fieldFile, const char* scriptFile);
        ~Simulator();

        //prints the grid
        void showGrid() const;
        //runs one command line from the script
        void run();

        //returns true if the simulation is complete:
        //end of script; missed to destroy a mine;
        //all mines destroyed
        bool isComplete() const;

        //returns the number of fire commands received via the script
        int numFires() const;
        //returns the number of move commands received via the script
        int numMoves() const;

        //returns the initial number of mines found
        int initMines() const;
        //returns the number of mines remaining at a given point in the
        //simulation run
        int minesRemaining() const;
        //returns true if the script has reached the end
        bool endOfScript() const;

    private:
        GridType _g;//todo:better name for this
        Grid     _grid;//todo:better name for this
        Cuboid   _cuboid;//todo:better name for this
        Ship     _ship;

        unsigned int _initMines;
        unsigned int _minesRemaining;
        unsigned int _nFires;
        unsigned int _nMoves;

        bool _endOfScript;
        bool _mineMissed;

        /*helper functions*/

        //Queue to store the commands parsed from the script file
        std::deque<std::string> _commands;

        //parse the field file and store in the grid(_g)
        void _readFieldFile(const char* fieldFile);
        //parse the commands from script file and store in a queue
        void _readScriptFile(const char* scriptFile);
        //advance the simulation by a single command
        void _runOnce(const std::string& command);
        //increment count for a fire command
        void _updateFirePenalty();
        //increment count for a move command
        void _updateMovePenalty();
        //simulate dropping the ship through the cuboid
        void _drop();

        //return true if the command type is a fire pattern
        //else false
        //throw an error is neither
        bool _isFireCommand(const FirePatternStringType& s);
        //return true if the command type is a move
        //else false
        //throw an error is neither
        bool _isMoveCommand(const MoveType& s);
};
