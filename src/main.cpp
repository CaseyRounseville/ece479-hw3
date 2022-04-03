#include "State.h"
#include "Operators.h"

#include <iostream>

void printState(State *state);

// stuff for manual use
Operator readMoveFromUser();

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
        { 4, 5, 3 },
        { 7, 8, 6 }
    };

    // create initial state and goal state
    State currState(initialBoard);
    State goalState(goalBoard);

    while (currState != goalState) {
        std::cout << "current state:" << std::endl;
        printState(&currState);
        std::cout << "--------------------" << std::endl;
        std::cout << "goal state:" << std::endl;
        printState(&goalState);

        std::cout << std::endl;

        std::cout << "Which direction to move the empty tile? [U/D/L/R]: ";
        Operator move = readMoveFromUser();

        switch (move) {
            case OP_MOVE_UP:
                if (canMoveEmptyTileUp(&currState)) {
                    currState = moveEmptyTileUp(&currState);
                } else {
                    std::cout << "You cant do that right now" << std::endl;
                    std::cout << std::endl;
                }
                break;
            case OP_MOVE_DOWN:
                if (canMoveEmptyTileDown(&currState)) {
                    currState = moveEmptyTileDown(&currState);
                } else {
                    std::cout << "You cant do that right now" << std::endl;
                    std::cout << std::endl;
                }
                break;
            case OP_MOVE_LEFT:
                if (canMoveEmptyTileLeft(&currState)) {
                    currState = moveEmptyTileLeft(&currState);
                } else {
                    std::cout << "You cant do that right now" << std::endl;
                    std::cout << std::endl;
                }
                break;
            case OP_MOVE_RIGHT:
                if (canMoveEmptyTileRight(&currState)) {
                    currState = moveEmptyTileRight(&currState);
                } else {
                    std::cout << "You cant do that right now" << std::endl;
                    std::cout << std::endl;
                }
                break;
        }
    }

    std::cout << "you win" << std::endl;

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

Operator readMoveFromUser() {
    // read characters until either
    char c = '\0';
    while (
        c != 'u' && c != 'U' &&
        c != 'd' && c != 'D' &&
        c != 'l' && c != 'L' &&
        c != 'r' && c != 'R'
    ) {
        std::cin >> c;
    }

    // clear the rest of the line in the input buffer
    std::cin.ignore(INT_MAX, '\n');
    std::cin.clear();

    // determine operator
    switch (c) {
        case 'u':
        case 'U':
            return OP_MOVE_UP;
        case 'd':
        case 'D':
            return OP_MOVE_DOWN;
        case 'l':
        case 'L':
            return OP_MOVE_LEFT;
        case 'r':
        case 'R':
            return OP_MOVE_RIGHT;
    }

    // make the compiler happy
    return OP_MOVE_UP;
}
