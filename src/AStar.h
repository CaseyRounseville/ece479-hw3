#ifndef ASTAR_H
#define ASTAR_H

#include "AStarTree.h"
#include "AStarNode.h"
#include "State.h"
#include "Operators.h"

#include <vector>

/**
 * find an optimal solution to the 8 puzzle using the a star algorithm
 * 
 * @param initialState the initial state of the board
 * @param goalState the state of the board that we are trying to reach
 * @param outWinningMoves the output vector where to put the sequence of
 * operators that forms an optimal solution to the 8 puzzle, getting from the
 * initial state to the goal state
 */
void astar(
    State *initialState,
    State *goalState,
    int (*heuristicFunction)(State *initialState, State *goalState),
    std::vector<Operator> *outWinningMoves
);

/**
 * compute number of tiles that are out of place between the current state and
 * the goal state, not including the blank tile (less is better, and zero means
 * we are at the goal state)
 * 
 * @param currState the state we are in now
 * @param goalState the state we want to be in
 * 
 * @return the number of tiles that are out of place between the current state
 * and the goal state, not including the blank tile
 */
int heuristic1(State *currState, State *goalState);

/**
 * (TODO) another heuristic
 */
int heuristic2(State *currState, State *goalState);

/**
 * create new paths by extending the first path to all neighbors of the
 * terminal node
 * 
 * @param queue the queue to create new paths in
 * @param terminal the node whose neighbors to create new paths with
 */
void createNewPaths(std::vector<AStarNode *> *queue, AStarNode *terminal);

/**
 * reject all new paths with loops
 */
void removeNewPathsWithLoops(std::vector<AStarNode *> *queue);

/**
 * if two or more paths reach a common node, delete all those paths except the
 * one that reaches the common node with the minimum cost
 * 
 * in this case, the cost is the path length
 */
void removeCostlierDuplicatesFromQueue(std::vector<AStarNode *> *queue);

class SortQueueComparator {
    private:
        // the state we are trying to reach; we need to know this when doing
        // comparisons for sorting since we need to compare how close to the
        // goal the two nodes are when we are deciding which one comes first
        // in the queue
        State *goalState;

        // a pointer to the heuristic function we are using (either heuristic1
        // or heuristic2)
        int (*heuristicFunction)(State *currState, State *goalState);

    public:
        SortQueueComparator(
            State *goalState,
            int (*heuristicFunction)(State *currState, State *goalState)
        );

        // return whether node1 < node2 in terms of f(n) = g(n) + h(n)
        bool operator()(AStarNode *node1, AStarNode *node2);

        ~SortQueueComparator();
};

/**
 * sort the queue by the sum of the path length and a lower bound estimate of
 * the cost remaining, with least-cost paths in front; this lower bound
 * estimate is the heuristic function we are using
 * 
 * we define the path length of a node in the a star tree as the number of
 * moves needed to get from the initial state (the root node) to that state;
 * equivalently, this is the number of edges between the root node and that
 * node we are considering (so, the root node has path length of zero)
 * 
 * @param queue the queue to sort
 * @param heuristicFunction a function pointer that points to the function we
 * are using as the heuristic (either heuristic1 or heuristic2)
 */
void sortQueue(
    std::vector<AStarNode *> *queue,
    State *goalState,
    int (*heuristicFunction)(State *currState, State *goalState)
);

#endif
