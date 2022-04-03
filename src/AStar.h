#ifndef ASTAR_H
#define ASTAR_H

#include "AStarTree.h"
#include "State.h"

void astar(AStarTree *tree, State *goalState);
int heuristic1(State *currState, State *goalState);
int heuristic2(State *currState, State *goalState);

#endif
