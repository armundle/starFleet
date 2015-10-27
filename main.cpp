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
    while(fieldFile >> row)
    {
        //create a vector of char
        //todo: typedef this too
        GridElement element(row.begin(), row.end());
        grid.push_back(element);
    }

    Ship s(grid);

    //reading the script file
    std::ifstream scriptFile(argv[2]);
    std::string command;

    unsigned int step = 1;

    while(scriptFile.good() && !scriptFile.eof())
    {
        std::getline(scriptFile, row);
        std::istringstream iss(row);

        //end of file
        if(row.empty())
        {
            break;
        }

        //Step
        cout << "Step " << step << endl;
        cout << endl;

        //Current minefield.
        s.printGrid();
        cout << endl;

        while(iss >> command)
        {

            //Current command.
            cout << command << " ";

            //testing for command type
            if(isFireCommand(command))//todo: use a set instead?
            {
                s.fire(command);
            }
            else if(isMoveCommand(command))//todo:use a set instead?
            {
                s.move(command);
            }

            //Resulant field
        }

        cout << endl;
        s.printGrid();
        cout << endl;

        step++;

        //If it is not the last line in the script, drop down by 1km.
        if(!scriptFile.eof())
        {
            s.drop();
        }
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
