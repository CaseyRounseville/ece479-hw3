#ifndef STATE_H
#define STATE_H

#define BOARD_SIZE 3
#define EMPTY_TILE -1

class State {
    private:
        // represent the board as a 2d array of integers
        int board[BOARD_SIZE][BOARD_SIZE];

        // the position of the empty tile, for easy access
        int emptyTileRow;
        int emptyTileCol;

        void loadBoard(int board[BOARD_SIZE][BOARD_SIZE]);

    public:
        State();
        State(int board[BOARD_SIZE][BOARD_SIZE]);
        State(State *base, int newEmptyTileRow, int newEmptyTileCol);

        int getEmptyTileRow();
        int getEmptyTileCol();
        int getTile(int row, int col);

        bool operator==(State &other);
        bool operator!=(State &other);

        ~State();
};

#endif
