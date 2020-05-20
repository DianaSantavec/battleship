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

    coordinates target, last_hit = {-1,-1}, new_hit; //last hit & new_hit is for computer player
    int shot_checker;

    int game_mode,  // Stores mode of the game (0 or 1)
        temp;       // Stores temporary values

    // Set both boards to WATER

    initializeBoard(boardOne);
    initializeBoard(boardTwo);

    // PICK GAME MODE BETWEEN PLAYER VS COMPUTER AND PLAYER VS PLAYER

    system("cls");
    printf("> [1] Player vs CO-OP\n");
    printf("> [2] Player vs Player\n");
    do {
        printf("> ");
        scanf("%d", &game_mode);
        game_mode--;
    } while(!game_mode && game_mode);

    //Placing ships
    system("cls");
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
        system("cls");
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
        system("cls");

        if(player == PLAYER1) {
            do {
                system("cls");
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
                    system("cls");
                    printf("Player 2's turn:\n");
                    printBoard(boardOne, FALSE);
                    target = inputCoordinate();
                    shot_checker = checkShot(boardOne, target);
                } while(shot_checker == -1);
                updateBoard(boardOne, target);
            }
            
            else if(game_mode == PLAYER_VS_COOP) {

                system("clear");
                printf("Computers trurn:\n");
                
                if (last_hit.row == -1){ //if last shot was a miss do a random shot
                    target = randomShot(boardOne);
                    shot_checker = checkShot(boardOne, target);
                    
                    if (shot_checker != 0){ //boat hitted
                        last_hit = target;
                    }
                    
                    updateBoard(boardOne, target);

                    printf("\nif\n");
                }

                else{
                    printf("\nelse\n");
                    new_hit = last_hit;
                    new_hit.column ++;
                    shot_checker= checkShot(boardOne, new_hit);
                    
                    if (shot_checker == -1){
                        new_hit.column -= 2;
                    }
                    shot_checker= checkShot(boardOne, new_hit);

                    if (shot_checker == -1){
                        new_hit.column += 1;
                        new_hit.row += 1;
                    }
                    shot_checker= checkShot(boardOne, new_hit);

                    if (shot_checker == -1){
                        new_hit.row -= 2;
                    }

                    shot_checker= checkShot(boardOne, new_hit);

                    if(shot_checker == -1){
                        new_hit = randomShot(boardOne);
                        shot_checker= checkShot(boardOne, new_hit);
                    }

                    if (shot_checker != -1){
                        updateBoard(boardOne, new_hit);
                        
                        if (shot_checker != 0){
                            last_hit = new_hit;
                        }

                        else{
                            last_hit.row = -1;
                            last_hit.column = -1;
                        }
                    }            

                }

                fflush(stdin);
                //getchar();
            }
        }

        // If player hited a boat, he will have one more chance to shoot
        if(!shot_checker) {
            system("cls");
            printf("Player %d's board:\n", player + 1);
            if(player == PLAYER1) printBoard(boardOne, TRUE);
            else if(player == PLAYER2) printBoard(boardTwo, TRUE);
            player = !player;
            fflush(stdin);
            getchar();
        }
    }
}
