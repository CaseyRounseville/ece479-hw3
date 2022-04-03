#ifndef ASTAR_H
#define ASTAR_H

#include "Graph.h"
#include "State.h"

void astar(Graph *graph, State *goalState);
int heuristic1(State *currState, State *goalState);
int heuristic2(State *currState, State *goalState);

#endif
