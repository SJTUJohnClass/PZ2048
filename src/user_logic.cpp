#include "user_logic.h"
#include "game_logic.h"

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Just don't modify the signatures of existing functions.

// You are free to add helper functions.

// Don't try to use extern variables from game_logic.cpp. You're not supposed to communicate through this way.
// After all, the game logic on the online judger won't contain extern variables same as yours.

static int row_num = 0, col_num = 0;
static std::vector<std::vector<int>> board;

void ClientPrepare(int r, int c) {
    // Just an example. You can make your own implementation.
    row_num = r;
    col_num = c;
    board.assign(row_num, std::vector<int>(col_num, 0));
    // for random seed set
    tsrand();
}

void ReadBoard() {
    // Just an example. You can make your own implementation.
    for (int i = 0; i < row_num; ++i) {
        for (int j = 0; j < col_num; ++j) {
            std::cin >> board[i][j];
        }
    }
}

char Decide() {
    // Please find a strategy to return a char for the direction you want to move
    // Here's an example for random move for four directions with equal probability
    // Notice: the program could not run in reality, please find a reasonable algorithm on your own :)
    static const char dir_map[4] = {'w', 's', 'a', 'd'};
    return dir_map[rand() % 4];
}

}

