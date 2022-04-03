#include "State.h"

#include <sstream>

void State::loadBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (unsigned int row = 0; row < BOARD_SIZE; row++) {
        for (unsigned int col = 0; col < BOARD_SIZE; col++) {
            int tile = board[row][col];
            this->board[row][col] = tile;

            if (tile == EMPTY_TILE) {
                this->emptyTileRow = row;
                this->emptyTileCol = col;
            }
        }
    }
}

State::State() {
    // 1 2 3
    // 4 5 6
    // 7 8 -
    for (unsigned int row = 0; row < BOARD_SIZE; row++) {
        for (unsigned int col = 0; col < BOARD_SIZE; col++) {
            int tile = row * BOARD_SIZE + col + 1;
            if (tile == BOARD_SIZE * BOARD_SIZE) {
                tile = EMPTY_TILE;
            }
            this->board[row][col] = tile;
        }
    }
}

State::State(int board[BOARD_SIZE][BOARD_SIZE]) {
    this->loadBoard(board);
}

State::State(State *base, int newEmptyTileRow, int newEmptyTileCol) {
    // copy the base state into this state
    this->loadBoard(base->board);
    
    // swap the empty tile with another tile
    int tempTile = this->board[newEmptyTileRow][newEmptyTileCol];
    this->board[newEmptyTileRow][newEmptyTileCol] = EMPTY_TILE;
    this->board[this->emptyTileRow][this->emptyTileCol] = tempTile;

    // update the stored location of the empty tile
    this->emptyTileRow = newEmptyTileRow;
    this->emptyTileCol = newEmptyTileCol;
}

int State::getEmptyTileRow() const {
    return this->emptyTileRow;
}

int State::getEmptyTileCol() const {
    return this->emptyTileCol;
}

int State::getTile(int row, int col) const {
    return this->board[row][col];
}

bool State::operator==(const State &other) const {
    for (unsigned int row = 0; row < BOARD_SIZE; row++) {
        for (unsigned int col = 0; col < BOARD_SIZE; col++) {
            if (this->getTile(row, col) != other.getTile(row, col)) {
                // found a difference in the board
                return false;
            }
        }
    }

    // no differences in the board
    return true;
}

bool State::operator!=(const State &other) const {
    return !(*this == other);
}

State::~State() {
    // nothing
}

std::string stringifyTile(int tile) {
    if (tile == EMPTY_TILE) {
        return "-";
    } else {
        std::stringstream ss;
        ss << tile;
        return ss.str();
    }
}
