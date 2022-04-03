#include "Operators.h"

bool canMoveEmptyTileUp(State *currState) {
    return currState->getEmptyTileRow() > 0;
}

bool canMoveEmptyTileDown(State *currState) {
    return currState->getEmptyTileRow() < BOARD_SIZE - 1;
}

bool canMoveEmptyTileLeft(State *currState) {
    return currState->getEmptyTileCol() > 0;
}

bool canMoveEmptyTileRight(State *currState) {
    return currState->getEmptyTileCol() < BOARD_SIZE - 1;
}

State moveEmptyTileUp(State *currState) {
    int row = currState->getEmptyTileRow();
    int col = currState->getEmptyTileCol();

    // create a new state with the empty tile and the tile above swapped
    return State(currState, row - 1, col);
}

State moveEmptyTileDown(State *currState) {
    int row = currState->getEmptyTileRow();
    int col = currState->getEmptyTileCol();

    // create a new state with the empty tile and the tile below swapped
    return State(currState, row + 1, col);
}

State moveEmptyTileLeft(State *currState) {
    int row = currState->getEmptyTileRow();
    int col = currState->getEmptyTileCol();

    // create a new state with the empty tile and the tile left swapped
    return State(currState, row, col - 1);
}

State moveEmptyTileRight(State *currState) {
    int row = currState->getEmptyTileRow();
    int col = currState->getEmptyTileCol();

    // create a new state with the empty tile and the tile right swapped
    return State(currState, row, col + 1);
}
