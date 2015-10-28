#include "Simulator.h"
#include "constants.h"
#include <iostream>
#include "PatternHelper.h"
#include <fstream>
#include <sstream>

Simulator::Simulator(const char* fieldFile, const char *scriptFile) :
                    _grid(_g),
                    _cuboid(_g),
                    _ship(_cuboid),
                    _initMines(0),
                    _minesRemaining(0),
                    _maxPoints(0),
                    _points(0),
                    _nFires(0),
                    _nMoves(0),
                    _endOfScript(false),
                    _mineMissed(false)
{
    _readFieldFile(fieldFile);
    _readScriptFile(scriptFile);

    _initMines = _grid.countMines();
    _minesRemaining = _initMines;
    _maxPoints = INIT_MULT * _initMines;
    _points = _maxPoints;
}

Simulator::~Simulator()
{
}

void Simulator::_readFieldFile(const char* f)
{
    std::ifstream fieldFile(f);
    std::string row;

    while(fieldFile >> row)
    {
        GridElement element(row.begin(), row.end());
        _g.push_back(element);
    }
}

void Simulator::_readScriptFile(const char* s)
{
    std::ifstream scriptFile(s);
    
    std::string command;
    std::string row;

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
        
        //new line
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

    std::string command;

    while(!_commands.empty())
    {
        command = _commands.front();
        
        //end of line
        if(command == "")
        {
            _commands.pop_front();
            _drop();
            break;
        }
        
        //print out current command
        std::cout << command << " ";
        
        _runOnce(command);
        
        //on to next command
        _commands.pop_front();
    }

    //new line for output formatting
    std::cout << std::endl;

    if(_commands.empty())
    {
        _endOfScript = true;
    }
}

void Simulator::_runOnce(const std::string& command)
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
        _grid.trim();
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
    
    if(_grid.mineMissed())
    {
        _mineMissed = true;    
    }
}

bool Simulator::isComplete()
{
    //terminating condition for the simulation
    if( _mineMissed || _endOfScript || !_minesRemaining)
    {
        return true;
    }

    return false;
}

int Simulator::numFires()
{
    return _nFires;
}

int Simulator::numMoves()
{
    return _nMoves;
}

int Simulator::minesRemaining()
{
    return _minesRemaining;
}

bool Simulator::endOfScript()
{
    return _endOfScript;
}