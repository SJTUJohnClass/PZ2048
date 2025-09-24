#include "game_logic.h"

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Or... can you?
// Just don't modify the signatures of existing functions.

// Don't try to use extern variables from user_logic.cpp. You're not supposed to communicate through this way.
// After all, the game logic on the online judger won't contain extern variables same as yours.
// You are free to add helper functions.

void Start(int row_num, int col_num, int target, uint game_seed) {
    /** implement here. **/
}

std::pair<int, int> EndGame() {
    /** implementation here **/
    return {0, 0};
}

int GetRows() {
    /** implementation here **/
    return 0;
}

int GetCols() { 
    /** implementation here **/
    return 0;
}

bool TryRun(char dir) {
    /** implementation here **/
    return false;
}

bool Undo() {
    /** implement here. **/
    /**in the process you need to undo the operation and both the score**/
    /**for example we have 0 0 0 4 4pts from 2 0 0 2 0pts, after we undo, we get 2 0 0 2 0pts**/
    return false;
}

void SetTile(int row_index, int col_index, int value) {
    /** implement here. **/
}

int GetTile(int row_index, int col_index) {
    /** implement here. **/
    return 0;
}

int Score() { 
    /** implement here. **/
    return 0;
}

int Steps() { 
    /** implement here. **/
    return 0;
}

int GetTarget() { 
    /** implement here. **/
    return 0;
}

bool HasReachedTarget() {
    /** implement here. **/
    return false;
}

bool Stuck() {
    /** implement here. **/
    return false;
}

void PrintBoard() {
    /** implement here. **/
    /** Hint: You MUST USE std:cout **/
    /** Hint: When you print the board, you have to use 1 space to split the number**/
    /** Hint: More Specifically, you have to open *.ans to check whether your output format is correct**/
}

}
