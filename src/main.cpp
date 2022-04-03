#include "State.h"
#include "Operators.h"

#include <iostream>

void printState(State *state);

int main(int arc, char **argv) {
    std::cout << "8 puzzle" << std::endl;

    // initial and final boards
    int initialBoard[BOARD_SIZE][BOARD_SIZE] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, -1 }
    };
    int goalBoard[BOARD_SIZE][BOARD_SIZE] = {
        { -1, 1, 2 },
        { 3, 4, 5 },
        { 6, 7, 8 }
    };

    // create initial state and goal state
    State initialState(initialBoard);
    State goalState(goalBoard);

    std::cout << "initial state:" << std::endl;
    printState(&initialState);
    std::cout << "--------------------" << std::endl;
    std::cout << "goal state:" << std::endl;
    printState(&goalState);

    return 0;
}

void printState(State *state) {
    for (unsigned int row = 0; row < BOARD_SIZE; row++) {
        for (unsigned int col = 0; col < BOARD_SIZE; col++) {
            int tile = state->getTile(row, col);
            if (tile == EMPTY_TILE) {
                std::cout << "-" << " ";
            } else {
                std::cout << tile << " ";
            }
        }
        std::cout << std::endl;
    }
}
