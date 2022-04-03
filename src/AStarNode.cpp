#include "AStarNode.h"

AStarNode::AStarNode() {
    // nothing
}

AStarNode *AStarNode::getParent() {
    return this->parent;
}

std::vector<AStarNode *> *AStarNode::getChildren() {
    return &this->children;
}

AStarNode::~AStarNode() {
    // nothing
}
