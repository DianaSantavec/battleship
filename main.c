#include "battleship.h"
#include "battleship.c"

int main() {

    srand(time(NULL));
    int player = rand() % 2;
    ShipType ship[NUM_OF_SHIPS] = {
        {NOSAC_AVIONA, 4, 1},
        {KRSTARICA, 3, 2},
        {RAZARAC, 2, 3},
        {PODMORNICA, 1, 4},
    };
    cell board[ROWS][COLS];
    initializeBoard(board);
    randomizeShips(board, ship);

    return 0;
}
