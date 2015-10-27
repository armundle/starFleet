#include <iostream>
#include <string> //todo:Is this needed anymore?
#include <fstream> //todo:is there a subset of this?
#include <sstream>
#include <cstdlib>
#include "PatternHelper.h"
#include "common.h"
#include "Ship.h"

//todo:debugMode
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Please specify 'field' and 'script' files.\nExiting." << std::endl;
        exit(EXIT_FAILURE);
    }

    //todo: check for good file
    std::ifstream fieldFile(argv[1]);

    //todo:typedef this
    GridType grid;
    Row row;

    //todo: when does this terminate?
    //todo:wrap this in a helper class?
    while(fieldFile >> row)
    {
        //create a vector of char
        //todo: typedef this too
        GridElement element(row.begin(), row.end());
        grid.push_back(element);
    }

    Cuboid c(grid);
    Ship s(c);

    int numMines = countMines(grid);
    int initMines = numMines;

    //reading the script file
    std::ifstream scriptFile(argv[2]);
    std::string command;

    unsigned int step = 1;
    int maxScore = 10*numMines;
    bool missedMine = false;
    int points = maxScore;
    int nFired = 0;
    int nMoves = 0;
    std::string result("pass");

    while(scriptFile.good() && !scriptFile.eof())
    {
        std::getline(scriptFile, row);
        std::istringstream iss(row);

        //end of file
        if(row.empty())
        {
            break;
        }

        if(numMines == 0)
        {
            points = 1;
            std::cout << "\npass (1)" << std::endl;
            break;
        }

        //Step
        cout << "\nStep " << step << endl;
        cout << endl;

        //Current minefield.
        s.printGrid();
        cout << endl;

        while(iss >> command)
        {

            //Current command.
            //cout << "command" << endl;
            cout << command << " ";
            //cout << "this was the command" << endl;

            //testing for command type
            if(isFireCommand(command))//todo: use a set instead?
            {
                numMines -= s.fire(command);
                if(nFired < 5*initMines)
                {
                    nFired +=5;
                }
            }
            else if(isMoveCommand(command))//todo:use a set instead?
            {
                s.move(command);
                if(nMoves < 3*initMines)
                {
                    nMoves += 2;
                }
            }

            //Resulant field
        }

        //If it is not the last line in the script, drop down by 1km.
        if(!scriptFile.eof())
        {
            //std::cout << "\n....drop....\n" << endl;
            s.drop();
        }

        cout << endl;
        s.printGrid();

        if(s.missedMine())
        {
            missedMine = true;
            points = 0;
            result = "fail";
            break;
        }

        step++;
    }

    if((result == "pass") && (points > 1) && (numMines == 0))
    {
        points = points - nFired - nMoves;
        std::cout << "\npass (" << points << ")" << std::endl;
    }

    if(missedMine || numMines)
    {
        std::cout << "\nfail (0)" << std::endl;
    }

    //todo:check the command and perform action accordingly

    //manual testing
    //cout << "\n***Grid***\n" << endl;
    //s.printGrid();

    //cout << "Vessel Center: " << s.getCenter().x << ", " <<
    //s.getCenter().y << endl;

    //std::string str("alpha");
    //s.fire(str);
    //s.printGrid();

    //s.move("west");
    //s.printGrid();

    //std::cout << s.getCenter().x << ", " << s.getCenter().y << std::endl;
    //std::cout << s.getGridSizeX() << ", " << s.getGridSizeY() << std::endl;

    //cout << "\nMoving Down\n\n";
    //s.drop();
    //s.printGrid();

    //cout << "Done!" << endl;
}
