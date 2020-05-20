#include "battleship.h"
//#include "battleship.c"

int main() {
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

    CLEAR;
    printf("> [1] Player vs CO-OP\n");
    printf("> [2] Player vs Player\n");
    do {
        printf("> ");
        scanf("%d", &game_mode);
        game_mode--;
    } while(!game_mode && game_mode);

    //Placing ships
    //system("cls");
    CLEAR;
    printf("> Player 1 places ships:\n");
    printf("> [1] Manually\n");
    printf("> [2] Randomly\n");
    do {
        printf("> ");
        scanf("%d", &temp);
        if(temp == 1) manualShips(boardOne, ship);
        else if(temp == 2) randomizeShips(boardOne, ship);
    } while(temp != 1 && temp != 2);

    if(game_mode) {
        //system("cls");
        CLEAR;
        printf("> Player 2 places ships:\n");
        printf("> [1] Manually\n");
        printf("> [2] Randomly\n");
        do {
            printf("> ");
            scanf("%d", &temp);
            if(temp == 1) manualShips(boardTwo, ship);
            else if(temp == 2) randomizeShips(boardTwo, ship);
        } while(temp != 1 && temp != 2);
    } 
    
    else randomizeShips(boardTwo, ship);


    //Choosing first player
    int player = rand() % 2;

    //Starting game
    while(TRUE) {
        CLEAR;

        if(player == PLAYER1) {
            do {
                CLEAR;
                printf("Player 1's turn:\n");
                printBoard(boardTwo, FALSE);
                target = inputCoordinate();
                shot_checker = checkShot(boardTwo, target);
            } while(shot_checker == -1);
            updateBoard(boardTwo, target);
        }
        
        else if(player == PLAYER2) {
            if(game_mode == PLAYER_V_PLAYER) {
                do {
                    CLEAR;
                    printf("Player 2's turn:\n");
                    printBoard(boardOne, FALSE);
                    target = inputCoordinate();
                    shot_checker = checkShot(boardOne, target);
                } while(shot_checker == -1);
                updateBoard(boardOne, target);
            }
            
            else if(game_mode == PLAYER_VS_COOP) {

                CLEAR;
                printf("Computers trurn:\n");
                
                if (last_target.row == -1){ //if last shot was a miss do a random shot
                    target = randomShot(boardOne);
                    shot_checker = checkShot(boardOne, target);
                    
                    if (shot_checker != 0){ //boat hitted
                        last_target = target;
                    }
                    
                    updateBoard(boardOne, target);
                }

                else{
                    //try every possible direction

                    target = last_target;
                    shot_checker = tryEveryDirection(boardOne,&target,&number_of_tested_shots);
                    updateBoard(boardOne, target);
                    
                    if (shot_checker != 0){  //if boat is hitted remeber new coordinates
                        last_target = target;
                        number_of_tested_shots = 0;
                    }

                    else{
                        last_target.row = -1;
                        last_target.column = -1;
                    }
                }            
            }
        }
        // If player hited a boat, he will have one more chance to shoot
        if(!shot_checker) {
            //system("cls");
            CLEAR;
            printf("Player %d's board:\n", player + 1);
            fflush(stdin);
            getchar();      //because of some magical reason, without this program deletes table before user input character for PLAYER1 (butit requests two characters for PLAYER2 - as expected)
            if(player == PLAYER1) printBoard(boardOne, TRUE);
            else if(player == PLAYER2 && game_mode != PLAYER_VS_COOP) printBoard(boardTwo, TRUE);
            player = !player;
            fflush(stdin);
            getchar();
        }
    }
}
