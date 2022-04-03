#ifndef OPERATORS_H
#define OPERATORS_H

#include "State.h"

/**
 * enumeration of the valid operations for moving the blank tile
 */
enum Operator {
    OP_NONE,
    OP_MOVE_UP,
    OP_MOVE_DOWN,
    OP_MOVE_LEFT,
    OP_MOVE_RIGHT
};

/**
 * functions to check whether a move is valid in a current state
 */
bool canMoveEmptyTileUp(State *currState);
bool canMoveEmptyTileDown(State *currState);
bool canMoveEmptyTileLeft(State *currState);
bool canMoveEmptyTileRight(State *currState);

/**
 * functions to perform the moves from a current state, and return the new
 * state that results from performing that move
 */
State moveEmptyTileUp(State *currState);
State moveEmptyTileDown(State *currState);
State moveEmptyTileLeft(State *currState);
State moveEmptyTileRight(State *currState);

#endif
