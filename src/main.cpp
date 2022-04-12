#include "AStar.h"
#include "State.h"
#include "Operators.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

/**
 * print the usage statement to explain how to run the program
 */
void printUsage();

/**
 * print a state to the standard output
 * 
 * @param state the state to print out
 */
void printState(State *state);

// human player
void humanPlayerGame(State *initialState, State *goalState);
Operator readMoveFromUser();

// astar player
void astarPlayerGame(State *initialState, State *goalState, int (*heuristicFunction)(State *initialState, State *goalState));
void astarDisplay(State *initialstate, std::vector<Operator> *moves);

int main(int argc, char **argv) {
    // handle command line arguments
    if (argc < 2) {
        printUsage();
        return 1;
    }

    bool humanPlayer = false;
    int (*heuristicFunction)(State *initialState, State *goalState);
    if (std::string(argv[1]) == "human") {
        humanPlayer = true;
        heuristicFunction = nullptr;
    } else if (std::string(argv[1]) == "astar") {
        if (argc != 3) {
            printUsage();
            return 1;
        }
        humanPlayer = false;
        std::string heuristicStr = std::string(argv[2]);
        if (heuristicStr == "1") {
            heuristicFunction = heuristic1;
        } else if (heuristicStr == "2") {
            heuristicFunction = heuristic2;
        } else if (heuristicStr == "3") {
            heuristicFunction = heuristic3;
        } else {
            printUsage();
            return 1;
        }
    } else {
        printUsage();
        return 1;
    }

    std::cout << "8 puzzle" << std::endl;

    // initial and final boards
    int initialBoard[BOARD_SIZE][BOARD_SIZE] = {
        { 2, 8, 3 },
        { 1, 6, 4 },
        { 7, -1, 5 }
    };
    int goalBoard[BOARD_SIZE][BOARD_SIZE] = {
        { 1, 2, 3 },
        { 8, -1, 4 },
        { 7, 6, 5 }
    };

    // create initial state and goal state
    State initialState(initialBoard);
    State goalState(goalBoard);

    if (humanPlayer) {
        humanPlayerGame(&initialState, &goalState);
    } else {
        astarPlayerGame(&initialState, &goalState, heuristicFunction);
    }

    return 0;
}

void printUsage() {
    std::cout << "USAGE:" << std::endl;
    std::cout << "For human player:" << std::endl;
    std::cout << "\t./bin/hw3 human" << std::endl;
    std::cout << "For A* algorithm:" << std::endl;
    std::cout << "\t./bin/hw3 astar 1" << std::endl;
    std::cout << "\t./bin/hw3 astar 2" << std::endl;
    std::cout << "\t./bin/hw3 astar 3" << std::endl;
}

void printState(State *state) {
    for (unsigned int row = 0; row < BOARD_SIZE; row++) {
        for (unsigned int col = 0; col < BOARD_SIZE; col++) {
            int tile = state->getTile(row, col);
            std::cout << stringifyTile(tile) << " ";
        }
        std::cout << std::endl;
    }
}

void humanPlayerGame(State *initialState, State *goalState) {
    State currState = *initialState;
    while (currState != *goalState) {
        std::cout << "current state:" << std::endl;
        printState(&currState);
        std::cout << "--------------------" << std::endl;
        std::cout << "goal state:" << std::endl;
        printState(goalState);

        std::cout << std::endl;

        std::cout << "Which direction to move the empty tile? [U/D/L/R]: ";
        Operator move = readMoveFromUser();

        switch (move) {
            case OP_NONE:
                // this will never happen
                std::cout << "OP_NONE happened" << std::endl;
                break;
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
}

Operator readMoveFromUser() {
    // read characters until a valid move
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
    return OP_NONE;
}

void astarPlayerGame(State *initialState, State *goalState, int (*heuristicFunction)(State *initialState, State *goalState)) {
    std::cout << "initial state:" << std::endl;
    printState(initialState);
    std::cout << "--------------------" << std::endl;
    std::cout << "goal state:" << std::endl;
    printState(goalState);

    std::cout << std::endl;

    std::cout << "winning moves:" << std::endl;
    std::vector<Operator> winningMoves;

    auto startTime = std::chrono::high_resolution_clock::now();
    astar(initialState, goalState, heuristic3, &winningMoves);
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    for (unsigned int i = 0; i < winningMoves.size(); i++) {
        std::cout << stringifyOperator(winningMoves.at(i)) << std::endl;
    }

    astarDisplay(initialState, &winningMoves);
    std::cout << std::endl;
    std::cout << "time elapsed: " << durationTime.count() << " microseconds" << std::endl;
}

void astarDisplay(State *initialstate, std::vector<Operator> *moves) {
    std::vector<State> states;

    State currState = *initialstate;
    states.push_back(currState);

    for (unsigned int i = 0; i < moves->size(); i++) {
        Operator currMove = moves->at(i);
        switch (currMove) {
            case OP_NONE:
                // this will never happen
                std::cout << "OP_NONE ocurred in move sequence" << std::endl;
                break;
            case OP_MOVE_UP:
                currState = moveEmptyTileUp(&currState);
                states.push_back(currState);
                break;
            case OP_MOVE_DOWN:
                currState = moveEmptyTileDown(&currState);
                states.push_back(currState);
                break;
            case OP_MOVE_LEFT:
                currState = moveEmptyTileLeft(&currState);
                states.push_back(currState);
                break;
            case OP_MOVE_RIGHT:
                currState = moveEmptyTileRight(&currState);
                states.push_back(currState);
                break;
        }
    }

    int numCols = 5;
    int numRows = 0;
    if (states.size() % numCols == 0) {
        numRows = states.size() / numCols;
    } else {
        numRows = (states.size() / numCols) + 1;
    }

    int numChars = (
        (numRows * BOARD_SIZE) *                                              // non empty lines
        (
            (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3)) + // 3 spaces between each col
            1                                                                 // newline at the end of each non empty row
        ) +
        (numRows - 1)                                                         // empty lines
    );

    // allocate one more char, needed for the null terminator
    char *display = new char[numChars + 1];

    // put in the null terminator
    display[numChars] = '\0';

    for (int i = 0; i < numChars; i++) {
        display[i] = ' ';
    }

    // put in the newlines
    for (int row = 0; row < numRows; row++) {
        for (int subRow = 0; subRow < BOARD_SIZE; subRow++) {
            display[
                (row * BOARD_SIZE + subRow) * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) + // non blank lines
                row +                                                                                               // blank line between rows
                (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3))                                     // go to the end of the current line
            ] = '\n';
        }
        if (row < numRows - 1) {
            display[
                (row * BOARD_SIZE + (BOARD_SIZE - 1)) * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) + // non blank lines
                row +                                                                                                         // blank line between rows
                (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3)) +                                             // go to the end of the current line
                1
            ] = '\n';
        }
    }

    // draw each state
    for (unsigned int stateIdx = 0; stateIdx < states.size(); stateIdx++) {
        State currState = states.at(stateIdx);

        // determine row and column in grid
        int row = stateIdx / numCols;
        int col = stateIdx % numCols;

        // determine char row and char col of top left corner where the state
        // should be drawn
        int charIdxUpperLeft = (
            (row * BOARD_SIZE) * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) + // non blank lines
            row +                                                                                      // blank line between rows
            col * ((BOARD_SIZE + BOARD_SIZE - 1) + 3)                                                  // plus 3 for 3 spaces in between each state
        );

        for (int subRow = 0; subRow < BOARD_SIZE; subRow++) {
            for (int subCol = 0; subCol < BOARD_SIZE; subCol++) {
                int tile = currState.getTile(subRow, subCol);
                char tileChar = stringifyTile(tile)[0];
                display[
                    charIdxUpperLeft +
                    subRow * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) +
                    subCol * 2
                ] = tileChar;

                // put a space after the tile, but only if this is not the end
                // of a row
                if (!(col == numCols - 1 && subCol == BOARD_SIZE - 1)) {
                    display[
                        charIdxUpperLeft +
                        subRow * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) +
                        subCol * 2 +
                        1
                    ] = ' ';
                }
            }

            // insert space within row, but don't overwrite the newline
            if (col < numCols - 1) {
                display[
                    charIdxUpperLeft +
                    subRow * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) +
                    (BOARD_SIZE + BOARD_SIZE - 1)
                ] = ' ';
                display[
                    charIdxUpperLeft +
                    subRow * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) +
                    (BOARD_SIZE + BOARD_SIZE - 1) +
                    1
                ] = ' ';
                display[
                    charIdxUpperLeft +
                    subRow * (numCols * (BOARD_SIZE + BOARD_SIZE - 1) + ((numCols - 1) * 3) + 1) +
                    (BOARD_SIZE + BOARD_SIZE - 1) +
                    2
                ] = ' ';
            }
        }
    }

    // print out the display
    std::cout << display;
}
