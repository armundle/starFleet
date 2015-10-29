#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "constants.h"
#include "Simulator.h"

void printNewLine()
{
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Please specify 'field' and 'script' files.\nExiting!" << std::endl;
        exit(EXIT_FAILURE);
    }

    Simulator sim(argv[1], argv[2]);

    unsigned int step = 1;

    while(!sim.isComplete())
    {
        std::cout << "Step " << step << std::endl;;

        printNewLine();

        sim.showGrid();

        printNewLine();

        sim.run();

        printNewLine();

        sim.showGrid();

        printNewLine();

        step++;
    }

    //point evaluation
    if(sim.minesRemaining() == 0 && sim.endOfScript())
    {
        const unsigned int initMines = sim.initMines();

        const unsigned int firePenaltyCeil = initMines * FIRE_PENATLY_MULT;
        const unsigned int firePenalty     = sim.numFires() * FIRE_PENATLY_MULT;

        const unsigned int movePenaltyCeil = initMines * MOVE_PENALTY_CEIL;
        const unsigned int movePenalty     = sim.numMoves() * MOVE_PENALTY_MULT;

        unsigned int points = (initMines * INIT_MULT)
                              - std::min(firePenalty, firePenaltyCeil)
                              - std::min(movePenalty, movePenaltyCeil);
        std::cout << "pass (" << points << ")" << std::endl;
    }
    else if(sim.minesRemaining() == 0 && !sim.endOfScript())
    {
        std::cout << "pass (1)" << std::endl;
    }
    else //missed mine or mines remaining
    {
        std::cout << "fail (0)" << std::endl;
    }
}
