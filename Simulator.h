#pragma once

#include <string>
#include <deque>
#include "types.h"
#include "Ship.h"
#include "Grid.h"
#include "Cuboid.h"

class Simulator
{
    public:
        Simulator(const char* fieldFile, const char* scriptFile);
        ~Simulator();

        void showGrid() const;
        void run();

        bool isComplete() const;

        int numFires() const;
        int numMoves() const;
        
        int initMines() const;
        int minesRemaining() const;
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

        std::deque<std::string> _commands;

        void _readFieldFile(const char* fieldFile);
        void _readScriptFile(const char* scriptFile);

        void _runOnce(const std::string& command);
        void _updateFirePenalty();
        void _updateMovePenalty();
        void _drop();
        
        bool _isFireCommand(const FirePatternStringType& s);
        bool _isMoveCommand(const MoveType& s);
};