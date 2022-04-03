#include "Graph.h"

Graph::Graph() {

}

Graph::~Graph() {
    for (unsigned int i = 0; i < this->nodes.size(); i++) {
        delete this->nodes.at(i);
    }
}
