#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H

#include <vector>

#include "State.h"
#include "Operators.h"

/**
 * a class to represent a node in the tree a star uses to find the optimal
 * path; each node contains the state of the 8 puzzle board at that point in
 * the game, and transitions between nodes represent making a move
 */
class AStarNode {
    private:
        // the operator that got us from the parent's state to this node's
        // state
        Operator op;

        // the state of the board at this node in the tree
        State state;

        // the parent node, which contains the state that came before this one,
        // until we made a move and got here
        AStarNode *parent;

        // the child nodes, which contain the states that come after this one,
        // after we make another move
        std::vector<AStarNode *> children;

        // save the value of the computed path length so we don't recompute it
        // each call (we know it will never change)
        int cachedPathLength;

    public:
        AStarNode(Operator op, State *state, AStarNode *parent);

        // getters
        Operator getOp();
        State *getState();
        AStarNode *getParent();
        std::vector<AStarNode *> *getChildren();

        /**
         * add the specified child node as a child of this node
         * 
         * @param child the child node to add
         */
        void addChild(AStarNode *child);

        /**
         * return the path length of this node in the a star tree
         * 
         * we define the path length of a node in the a star tree as the number
         * of moves needed to get from the initial state (the root node) to
         * that state; equivalently, this is the number of edges between the
         * root node and that node we are considering (so, the root node has
         * path length of zero)
         * 
         * @return the path length of this node in the a star tree
         */
        int getPathLength();

        ~AStarNode();
};

#endif
