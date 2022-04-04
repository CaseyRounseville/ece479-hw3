#ifndef STATE_H
#define STATE_H

#define BOARD_SIZE 3
#define EMPTY_TILE -1

#include <string>

/**
 * a class to represent a state in the 8 puzzle game; this consists of keeping
 * track of where all the tiles are on the board, including the empty tile
 */
class State {
    private:
        // represent the board as a 2d array of integers
        int board[BOARD_SIZE][BOARD_SIZE];

        // the position of the empty tile, for easy access
        int emptyTileRow;
        int emptyTileCol;

        /**
         * a private helper function to copy a 2d array into this state's board
         * instance variable
         * 
         * @param board the 2d array representing the board
         */
        void loadBoard(int board[BOARD_SIZE][BOARD_SIZE]);

    public:
        /**
         * initialize a state with a default board
         */
        State();

        /**
         * initialize a state with the given board
         * 
         * @param board the 2d array representing the board
         */
        State(int board[BOARD_SIZE][BOARD_SIZE]);

        /**
         * initialize a state based on a base state, with the empty tile moved
         * to the new specified location
         * 
         * @param base the base state to base the new one off of
         * @param newEmptyTileRow the new row of the empty tile
         * @param newEmptyTileCol the new column of the empty tile
         */
        State(State *base, int newEmptyTileRow, int newEmptyTileCol);

        // getters
        int getEmptyTileRow() const;
        int getEmptyTileCol() const;
        int getTile(int row, int col) const;

        // operator overloads for equals and not equals
        bool operator==(const State &other) const;
        bool operator!=(const State &other) const;

        ~State();
};

class UnorderedSetStateHasher {
    public:
        const size_t operator()(const State &state) const;
};

std::string stringifyTile(int tile);

#endif
