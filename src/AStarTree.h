#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "AStarNode.h"

/**
 * a class to represent the tree that a star uses to find an optimal path; each
 * node in the tree represents a state of the 8 puzzle board, and transisitons
 * from a parent node to a child node represents making a move(applying one of
 * the operators, such as moving the empty tile up, down, left, or right)
 */
class AStarTree {
    private:
        // the root node of the tree
        AStarNode *root;

    public:
        AStarTree();
        ~AStarTree();
};

#endif
