#include "AStarTree.h"

void freeAStarNode(AStarNode *node);

AStarTree::AStarTree() {

}

AStarTree::~AStarTree() {
    // recursively free the entire tree
    freeAStarNode(root);
}

void freeAStarNode(AStarNode *node) {
    if (node == nullptr) {
        // should not happen, but just in case
        return;
    }

    // delete all the children first
    std::vector<AStarNode *> *children = node->getChildren();
    for (unsigned int i = 0; i < children->size(); i++) {
        freeAStarNode(children->at(i));
    }

    // then delete the node itself
    delete node;
}