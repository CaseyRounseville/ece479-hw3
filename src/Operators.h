#ifndef OPERATORS_H
#define OPERATORS_H

#include "State.h"

enum Operator {
    OP_MOVE_UP,
    OP_MOVE_DOWN,
    OP_MOVE_LEFT,
    OP_MOVE_RIGHT
};

bool canMoveEmptyTileUp(State *currState);
bool canMoveEmptyTileDown(State *currState);
bool canMoveEmptyTileLeft(State *currState);
bool canMoveEmptyTileRight(State *currState);

State moveEmptyTileUp(State *currState);
State moveEmptyTileDown(State *currState);
State moveEmptyTileLeft(State *currState);
State moveEmptyTileRight(State *currState);

#endif
