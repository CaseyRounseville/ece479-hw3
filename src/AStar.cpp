#include "AStar.h"

#include <algorithm>

void astar(
    State *initialState,
    State *goalState,
    int (*heuristicFunction)(State *initialState, State *goalState),
    std::vector<Operator> *outWinningMoves
) {
    // create the astar tree
    AStarTree tree(initialState);

    // step 1
    // form a one-element queue consisting of a zero-length path that contains
    // only the root node
    std::vector<AStarNode *> queue;
    AStarNode *root = tree.getRoot();
    queue.push_back(root);

    // step 2
    // until the first path in the queue terminates at the goal node, or until
    // the queue is empty, run in a loop
    while (
        queue.size() > 0 &&
        *queue.at(0)->getState() != *goalState
    ) {
        // step 2.1
        // remove the first path from the queue
        AStarNode *firstNode = queue.at(0);
        queue.erase(queue.begin());

        // create new paths by extending the first path to all neighbors of the
        // terminal node;
        createNewPaths(&queue, firstNode);

        // step 2.2
        // reject all new paths with loops
        removeNewPathsWithLoops(&queue);

        // step 2.3
        // if two or more paths reach a common node, delete all those paths
        // except the one that reaches the common node with the minimum cost
        removeCostlierDuplicatesFromQueue(&queue);

        // step 2.4
        // sort the entire queue by the sum of the path length and a
        // lower-bound estimate of the cost remaining, with least-cost paths in
        // front
        sortQueue(&queue, goalState, heuristicFunction);
    }

    // step 3
    // if the goal node is found, announce success; otherwise, announce failure
    if (queue.size() > 0) {
        // success
        // write the winning moves to the output vector
        AStarNode *terminal = queue.at(0);
        AStarNode *currNode = terminal;
        while (currNode != root) {
            // add the move that got us to this node to the output vector
            Operator move = currNode->getOp();
            outWinningMoves->push_back(move);

            // move up one move in the tree
            currNode = currNode->getParent();
        }

        // reverse the output vector
        std::reverse(outWinningMoves->begin(), outWinningMoves->end());
    } else {
        // failure
        // don't write any winning moves to the output vector, since there are
        // none
    }
}

int heuristic1(State *currState, State *goalState) {
    // count the number of tiles out of place between the current state and the
    // goal state, not including the blank tile
    int numTilesMisplaced = 0;
    for (unsigned int row = 0; row < BOARD_SIZE; row++) {
        for (unsigned int col = 0; col < BOARD_SIZE; col++) {
            int currStateTile = currState->getTile(row, col);
            int goalStateTile = goalState->getTile(row, col);

            // make sure to not count the empty tile
            if (
                currStateTile != EMPTY_TILE &&
                currStateTile != goalStateTile
            ) {
                numTilesMisplaced++;
            }
        }
    }
    return numTilesMisplaced;
}

int heuristic2(State *currState, State *goalState) {
    return 0;
}

void createNewPaths(std::vector<AStarNode *> *queue, AStarNode *terminal) {
    // we will add children for moving the empty tile in all four directions,
    // except if we cannot currently move the empty tile in a certain direction
    State *terminalState = terminal->getState();

    // try moving up
    if (canMoveEmptyTileUp(terminalState)) {
        State upState = moveEmptyTileUp(terminalState);
        AStarNode *upNode = new AStarNode(OP_MOVE_UP, &upState);
        terminal->addChild(upNode);
        queue->push_back(upNode);
    }

    // try moving down
    if (canMoveEmptyTileDown(terminalState)) {
        State downState = moveEmptyTileDown(terminalState);
        AStarNode *downNode = new AStarNode(OP_MOVE_DOWN, &downState);
        terminal->addChild(downNode);
        queue->push_back(downNode);
    }

    // try moving left
    if (canMoveEmptyTileLeft(terminalState)) {
        State leftState = moveEmptyTileLeft(terminalState);
        AStarNode *leftNode = new AStarNode(OP_MOVE_LEFT, &leftState);
        terminal->addChild(leftNode);
        queue->push_back(leftNode);
    }

    // try moving right
    if (canMoveEmptyTileRight(terminalState)) {
        State rightState = moveEmptyTileRight(terminalState);
        AStarNode *rightNode = new AStarNode(OP_MOVE_RIGHT, &rightState);
        terminal->addChild(rightNode);
        queue->push_back(rightNode);
    }
}

void removeNewPathsWithLoops(std::vector<AStarNode *> *queue) {
    // a new path has a loop if the most recent state we added has been
    // encountered before
    for (
        unsigned int terminalIdx = 0;
        terminalIdx < queue->size();
        terminalIdx++
    ) {
        // the most recent state added in a path is the state contained in the
        // node for that path in the queue
        AStarNode *terminal = queue->at(terminalIdx);
        State *terminalState = terminal->getState();

        // check the state of the terminal node against the states of all nodes
        // that came before it to detect a loop
        AStarNode *currAncestor = terminal->getParent();
        while (currAncestor != nullptr) {
            if (*currAncestor->getState() == *terminalState) {
                // we have detected a loop, so remove the terminal from the
                // queue
                queue->erase(queue->begin() + terminalIdx);
                terminalIdx--;
                break;
            }

            // move up the tree by one move
            currAncestor = currAncestor->getParent();
        }
    }
}

void removeCostlierDuplicatesFromQueue(std::vector<AStarNode *> *queue) {
    for (
        unsigned int baseLineIdx = 0;
        baseLineIdx < queue->size() - 1;
        baseLineIdx++
    ) {
        // the base line node is the node that we will compare to all other
        // nodes after it in the queue, checking if those other nodes arrive at
        // the same state as the base line node at a lower cost;
        // if another node arrives at the same state as the base line node at a
        // lower cost, then we remove the base line node from the queue, and
        // treat that other less costly node as the new base line node, until
        // another even less costly one is found;
        // we run through treating every node except the last as a base line
        // node
        AStarNode *baseLineNode = queue->at(baseLineIdx);
        for (
            unsigned int compareIdx = baseLineIdx + 1;
            compareIdx < queue->size();
            compareIdx++
        ) {
            // the compare node is the node we are currently comparing against
            // the base line node, to see if it arrives at the same state as
            // the base line, at a lower cost
            AStarNode *compareNode = queue->at(compareIdx);

            if (
                compareNode->getState() == baseLineNode->getState() &&
                compareNode->getPathLength() < baseLineNode->getPathLength()
            ) {
                // we have found a node that arrives at the same state as the
                // base line node, at a lower cost;
                // we have to be careful about the indices here, remember that
                // removing an element from a list shifts the elements after it
                // to the left by one index
                queue->erase(queue->begin() + baseLineIdx);
                compareIdx--;
                baseLineIdx = compareIdx;
                baseLineNode = compareNode;
            }
        }
    }
}

SortQueueComparator::SortQueueComparator(
    State *goalState,
    int (*heuristicFunction)(State *currState, State *goalState)
) {
    this->goalState = goalState;
    this->heuristicFunction = heuristicFunction;
}

bool SortQueueComparator::operator()(AStarNode *node1, AStarNode *node2) {
    // compute f(n) = g(n) + h(n) for both nodes, where g(n) represents the
    // path length of the node, and h(n) represents the heuristic merit of the
    // node
    State *state1 = node1->getState();
    State *state2 = node2->getState();

    // compute estimated cost of node 1
    int node1PathLength = node1->getPathLength();
    int node1Heuristic = this->heuristicFunction(state1, this->goalState);
    int node1EstimatedCost = node1PathLength + node1Heuristic;

    // compute estimated cost of node 2
    int node2PathLength = node2->getPathLength();
    int node2Heuristic = this->heuristicFunction(state2, this->goalState);
    int node2EstimatedCost = node2PathLength + node2Heuristic;

    return node1EstimatedCost < node2EstimatedCost;
}

SortQueueComparator::~SortQueueComparator() {
    // nothing
}

void sortQueue(
    std::vector<AStarNode *> *queue,
    State *goalState,
    int (*heuristicFunction)(State *initialState, State *goalState)
) {
    // call the sorting function that comes with the standard library; this
    // requires us to supply our own comparison logic, in this case in the form
    // of a comparator object with the "()" operator overloaded so that the
    // object can be "called" like a function, and determine which of two nodes
    // should come first in the sorted queue
    SortQueueComparator comparator(goalState, heuristicFunction);
    std::sort(queue->begin(), queue->end(), comparator);
}
