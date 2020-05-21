#include "battleship.h"
#include "battleship.c"

int main() {
    srand(time(NULL));

    ShipType ship[NUM_OF_SHIPS] = {
        {'N', 4, 1},
        {'K', 3, 2},
        {'R', 2, 3},
        {'P', 1, 4},
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


    //Choosing first player
    int player = rand() % 2;

    //Starting game
    while(true) {
        system(CLEAR);

        if(player == PLAYER1) {
            do {
                system(CLEAR);
                printf("Player 1's turn:\n");
                printBoard(boardTwo, false);
                target = inputCoordinate();
                shot_checker = checkShot(boardTwo, target);
            } while(shot_checker == -1);
            updateBoard(boardTwo, target);
        }

        else if(player == PLAYER2) {
            if(game_mode == PLAYER_V_PLAYER) {
                do {
                    system(CLEAR);
                    printf("Player 2's turn:\n");
                    printBoard(boardOne, false);
                    target = inputCoordinate();
                    shot_checker = checkShot(boardOne, target);
                } while(shot_checker == -1);
                updateBoard(boardOne, target);
            }

            else if(game_mode == PLAYER_VS_COOP) {

                system(CLEAR);
                printf("Computers trurn:\n");

                if (last_target.x == -1){ //if last shot was a miss do a random shot
                    do {
                		target.x = rand() % 10;
                		target.y = rand() % 10;
                		shot_checker = checkShot(boardOne, target);
                	} while(shot_checker == -1);

                    if (shot_checker != 0){ //boat hit
                        last_target = target;
                    }

                    updateBoard(boardOne, target);
                }

                else{
                    //try every possible direction

                    target = last_target;
                    shot_checker = tryEveryDirection(boardOne,&target,&number_of_tested_shots);
                    updateBoard(boardOne, target);

                    if (shot_checker != 0){  //if boat is hit remeber new coordinates
                        last_target = target;
                        number_of_tested_shots = 0;
                    }

                    else{
                        last_target.x = -1;
                        last_target.y = -1;
                    }
                }
            }
        }
        // If player hit a boat, he will have one more chance to shoot
        if(!shot_checker) {
            system(CLEAR);
            printf("Player %d's board:\n", player + 1);
            fflush(stdin);
            getchar();      //because of some magical reason, without this program deletes table before user input character for PLAYER1 (butit requests two characters for PLAYER2 - as expected)
            if(player == PLAYER1) printBoard(boardOne, true);
            else if(player == PLAYER2 && game_mode != PLAYER_VS_COOP) printBoard(boardTwo, true);
            player = !player;
            fflush(stdin);
            getchar();
        }
    }
}
