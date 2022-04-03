#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H

#include <vector>

#include "State.h"

/**
 * a class to represent a node in the tree a star uses to find the optimal
 * path; each node contains the state of the 8 puzzle board at that point in
 * the game, and transitions between nodes represent making a move
 */
class AStarNode {
    private:
        // the state of the board at this node in the tree
        State state;

        // the parent node, which contains the state that came before this one,
        // until we made a move and got here
        AStarNode *parent;

        // the child nodes, which contain the states that come after this one,
        // after we make another move
        std::vector<AStarNode *> children;

    public:
        AStarNode();

        // getters
        AStarNode *getParent();
        std::vector<AStarNode *> *getChildren();

        ~AStarNode();
};

#endif
