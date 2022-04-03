#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "Node.h"

class Graph {
    private:
        std::vector<Node *> nodes;

    public:
        Graph();
        ~Graph();
};

#endif
