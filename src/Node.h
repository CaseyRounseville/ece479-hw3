#ifndef NODE_H
#define NODE_H

#include <vector>

#include "State.h"

class Node {
    private:
        State state;
        std::vector<Node *> neighbors;

    public:
        Node();
        ~Node();
};

#endif
