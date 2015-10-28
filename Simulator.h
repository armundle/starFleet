#pragma once

#include <string>
#include <deque>
#include "types.h"
#include "Ship.h"

class Simulator
{
    public:
        Simulator(std::string fieldFile, std::string scriptFile);
        ~Simulator();

        void showGrid();
        void run();
        void missedMine();

        bool isComplete();

        int numFires();
        int numMoves();

    private:
        GridType _g;
        Grid     _grid;
        Cuboid   _cuboid;
        Ship     _ship;

        unsigned int _initMines;
        unsigned int _minesRemaining;
        unsigned int _maxPoints;
        unsigned int _points;
        unsigned int _nFires;
        unsigned int _nMoves;

        bool _endOfScript;

        std::deque<std::string> _commands;

        void _readFieldFile(std::string fieldFile);
        void _readScriptFile(std::string scriptFile);

        void _runLine(std::string command);
};

//Implementation

Simulator::Simulator(std::string fieldFile, std::string scriptFile) :
                    _grid(_g),
                    _cuboid(_g),
                    _ship(_cuboid),
                    _initMines(0),
                    _minesRemaining(0),
                    _maxPoints(0),
                    _points(0),
                    _nFires(0),
                    _nMoves(0),
                    _endOfScript(false)
{
    _readFieldFile(fieldFile);
    _readScriptFile(scriptFile;

    _initMines = _countMines();
    _minesRemaining = _initMines;
    _maxPoints = INIT_MULT * _initMines;
    _points = _maxPoints;
}

~Simulator::Simulator()
{
}

void Simulator::_readFieldFile(std::string f)
{
    std::ifstream f(fieldFile);

    Row row;

    while(fieldFile >> row)
    {
        GridElement element(row.begin(), row.end());
        grid.push_back(element);
    }
}

void Simulator::_readScriptFile(std::string s)
{
    //reading the script file
    std::ifstream scriptFile(s);
    std::string command;

    while(scriptFile.good() && !scriptFile.eof())
    {
        std::getline(scriptFile, row);
        std::istringstream iss(row);

        //end of file
        if(row.empty())
        {
            break;
        }

        while(iss >> command)
        {
            _commands.push_back(command);
        }
        _commands.push_back("");
    }
}

void Simulator::showGrid()
{
    _grid.print();
}

void Simulator::run()
{
    if(isComplete())
    {
        return;
    }

    if(_commands.empty())
    {
        _endOfScript = true;
    }

    std::string command = _commands.front();

    while(command != "")
    {
        _runLine(command);

        _commands.pop_front();
        command = _commands.front();
    }

    if(!_commands.empty())
    {
        _drop();
    }
}

void Simulator::_runLine(std::string command)
{
    if(isFireCommand(command))
    {
        _minesRemaining -= _ship.fire(command);
        _updateFirePenalty();

        _grid.trim();
    }
    else if(isMoveCommand(command))
    {
        _ship.move(command);
        _updateMovePenalty();

        _grid.resize(command);
    }
    //error
}

void Simulator::_updateFirePenalty()
{
    _nFires++;

    /*
    if(_nFires < FIRE_PENATLY_MULT * _initMines)
    {
        _nFires += FIRE_PENALTY_INCR;
    }
    */
}

void Simulator::_updateMovePenalty()
{
    _nMoves++;
    /*
    if(_nMoves < MOVE_PENALTY_MULT * _initMines)
    {
        _nMoves += MOVE_PENALTY_INCR;
    }
    */
}

void Simulator::_drop()
{
    _grid.drop();
}

bool Simulator::missedMine()
{
    return _grid.mineMissed();
}

bool isComplete()
{
    //todo: fill this in.
    if(mineMissed() || _endOfScript || !_minesRemaining)
    {
        return true;
    }

    return false;
}

int numFires()
{
    return numFires;
}

int numMoves()
{
    return numMoves;
}
