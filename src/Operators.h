#ifndef OPERATORS_H
#define OPERATORS_H

#include "State.h"

bool canMoveEmptyTileUp(State *currState);
bool canMoveEmptyTileDown(State *currState);
bool canMoveEmptyTileLeft(State *currState);
bool canMoveEmptyTileRight(State *currState);

State moveEmptyTileUp(State *currState);
State moveEmptyTileDown(State *currState);
State moveEmptyTileLeft(State *currState);
State moveEmptyTileRight(State *currState);

#endif
