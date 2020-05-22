#ifdef _WIN32
#include "boardLibrary.c"
#include "computerLogic.c"
#include "coordinatesFunctions.c"
#include "shipsFunctions.c"
#include <Windows.h>

typedef struct Window {
    SHORT x; // Number of characters displayed horizontally
    SHORT y; // Number of characters displayed vertically
} window;

/*
 * Sets window size on Windows to a given width and height
 *
 * Parameters:
 *     width  - number of characters displayed horizontally
 *     height - number of characters displayed vertically
 *
 * Return (void):
 *     Nothing
 */

void setWindowSize(int width, int height) {
    // Structure in WinConTypes.h (included in Windows.h) that holds buffer size
    COORD coord = {width, height};
    // Structure in WinConTypes.h (included in Windows.h) that holds all 4 corners of the window
    SMALL_RECT rect = {0, 0, width - 1, height - 1};
    // Security descriptor (included in Windows.h)
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Functions for setting buffer and window size
    SetConsoleScreenBufferSize(handle, coord);
    SetConsoleWindowInfo(handle, TRUE, &rect);
}
#endif

#include "battleship.h"

int main() {

#ifdef _WIN32
    window size = {5 + 4 * COLS + 1, 1 + 2 * (3 + 2 * ROWS + 1) + 3};
    setWindowSize(size.x, size.y);
#endif

    srand(time(NULL));

    ShipType ship[NUM_OF_SHIPS] = {
        {NOSAC_AVIONA, 4, 1},
        {KRSTARICA, 3, 2},
        {RAZARAC, 2, 3},
        {PODMORNICA, 1, 4},
    };
    cell boardOne[ROWS][COLS],  // Stores player 1 board
         boardTwo[ROWS][COLS];  // Stores player 2 board

    coordinates target, last_target = {-1,-1}; // Last_target is for co-op

    int shot_checker, number_of_tested_shots = -1; // number_of_tested_shots is for co-op, testing is every field around hit tested

    int game_mode,  // Stores mode of the game (0 or 1)
        temp;       // Stores temporary values

    // Set both boards to WATER

    initializeBoard(boardOne);
    initializeBoard(boardTwo);

    // PICK GAME MODE BETWEEN PLAYER VS COMPUTER AND PLAYER VS PLAYER

    system(CLEAR);
    printf("> [1] Player vs CO-OP\n");
    printf("> [2] Player vs Player\n");
    do {
        printf("> ");
        scanf("%d", &game_mode);
        game_mode--;
    } while(!game_mode && game_mode);

    //Placing ships
    system(CLEAR);
    printf("> Player 1 places ships:\n");
    printf("> [1] Manually\n");
    printf("> [2] Randomly\n");
    do {
        printf("> ");
        scanf("%d", &temp);
        if(temp == 1) manualShips(boardOne, ship);
        else if(temp == 2) randomShips(boardOne, ship);
    } while(temp != 1 && temp != 2);

    if(game_mode) {
        system(CLEAR);
        printf("> Player 2 places ships:\n");
        printf("> [1] Manually\n");
        printf("> [2] Randomly\n");
        do {
            printf("> ");
            scanf("%d", &temp);
            if(temp == 1) manualShips(boardTwo, ship);
            else if(temp == 2) randomShips(boardTwo, ship);
        } while(temp != 1 && temp != 2);
    }

    else randomShips(boardTwo, ship);


    //Choosing first player randomly
    int player = rand() % 2;

    //Starting game
    while(true) {
        system(CLEAR);

        if(player == PLAYER1) {
            do {
                system(CLEAR);
                printf("Player 1's turn:\n");
                printBoard(boardOne, true);
                printBoard(boardTwo, false);
                target = inputCoordinate();
                shot_checker = checkShot(boardTwo, target);
            } while(shot_checker == -1);
            updateCell(boardTwo, target);
            system(CLEAR);
            printf("Player 1's turn:\n");
            printBoard(boardOne, true);
            printBoard(boardTwo, false);
        }

        else if(player == PLAYER2) {
            if(game_mode == PLAYER_V_PLAYER) {
                do {
                    system(CLEAR);
                    printf("Player 2's turn:\n");
                    printBoard(boardTwo, true);
                    printBoard(boardOne, false);
                    target = inputCoordinate();
                    shot_checker = checkShot(boardOne, target);
                } while(shot_checker == -1);
                updateCell(boardOne, target);
                system(CLEAR);
                printf("Player 2's turn:\n");
                printBoard(boardTwo, true);
                printBoard(boardOne, false);
            }

            else if(game_mode == PLAYER_VS_COOP) {

                system(CLEAR);
                printf("Computers turn:\n");
                if (last_target.x == -1) { //if last shot was a miss do a random shot
                    do {
                		target.x = rand() % 10;
                		target.y = rand() % 10;
                		shot_checker = checkShot(boardOne, target);
                	} while(shot_checker == -1);

                    if (shot_checker == 1) { //boat hit
                        last_target = target;
                    }

                    updateCell(boardOne, target);
                }

                else {
                    //try every possible direction

                    target = last_target;
                    shot_checker = tryEveryDirection(boardOne,&target,&number_of_tested_shots);
                    updateCell(boardOne, target);

                    if (shot_checker == 1) {  //if boat is hit remeber new coordinates
                        last_target = target;
                        number_of_tested_shots = 0;
                    }

                    else {
                        last_target.x = -1;
                        last_target.y = -1;
                    }
                }

                printBoard(boardOne, true);
            }
        }

        if(shot_checker == 1) {
            printf("> %c%c is a hit!\n", target.x + 'A', target.y + '0');
            fflush(stdin);
            getchar();
        } else {
            printf("> %c%c is a miss!\n", target.x + 'A', target.y + '0');
            fflush(stdin);
            getchar();
            player = !player;
        }
    }
}
