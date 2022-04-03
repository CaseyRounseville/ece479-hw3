#include "AStarNode.h"

AStarNode::AStarNode(Operator op, State *state, AStarNode *parent) {
    // set the operator that got us here in the a star tree
    this->op = op;

    // set the state of this node in the a star tree
    this->state = *state;

    // set the parent of this node
    this->parent = parent;

    // initialize the cached path length to -1 so we will know if it has been
    // computed yet or not (the minimum is zero if it was computed)
    this->cachedPathLength = -1;
}

Operator AStarNode::getOp() {
    return this->op;
}

State *AStarNode::getState() {
    return &this->state;
}

AStarNode *AStarNode::getParent() {
    return this->parent;
}

std::vector<AStarNode *> *AStarNode::getChildren() {
    return &this->children;
}

void AStarNode::addChild(AStarNode *child) {
    this->getChildren()->push_back(child);
}

int AStarNode::getPathLength() {
    // check if we have already computed the path length, otherwise we will
    // need to compute it, and then save the value for next time this function
    // is called
    if (this->cachedPathLength > -1) {
        return this->cachedPathLength;
    }

    if (this->getParent() == nullptr) {
        // root node has path length of zero
        this->cachedPathLength = 0;
        return this->cachedPathLength;
    }

    // this is not the root node, so we know that the path length of this node
    // is one more than its parent's
    this->cachedPathLength = this->getParent()->getPathLength() + 1;
    return this->cachedPathLength;
}

AStarNode::~AStarNode() {
    // nothing
}
