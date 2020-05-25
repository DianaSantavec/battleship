#ifdef __WIN32
#include "boardLibrary.c"
#include "computerLogic.c"
#include "coordinatesFunctions.c"
#include "shipsFunctions.c"

#endif

#include "battleship.h"

int main() {

#ifdef _WIN32
    window size = {5 + 4 * COLS + 1, 1 + 2 * (3 + 2 * ROWS + 1) + 3};
    setWindowSize(size.x, size.y);
#endif

    int i,j;    //counters

    srand(time(NULL));

    shipDetails ships_details[2][NUMBER_OF_SHIPS_IN_TOTAL]; //2 as in two players

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

    stackElement *stack = NULL, *element; //pointer to top of a stack for co-op

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
        if(temp == 1) manualShips(boardOne, ship, &ships_details[1]);
        else if(temp == 2) randomShips(boardOne, ship, &ships_details[1]);
    } while(temp != 1 && temp != 2);

    if(game_mode) {
        system(CLEAR);
        printf("> Player 2 places ships:\n");
        printf("> [1] Manually\n");
        printf("> [2] Randomly\n");
        do {
            printf("> ");
            scanf("%d", &temp);
            if(temp == 1) manualShips(boardTwo, ship, &ships_details[0]);
            else if(temp == 2) randomShips(boardTwo, ship, &ships_details[0]);
        } while(temp != 1 && temp != 2);
    }

    else randomShips(boardTwo, ship, &ships_details[0]);

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
                element = Top(stack);
                if (element == NULL) { //if last shot was a miss do a random shot
                    do {
                        printf("idem na random :/");
                		target.x = rand() % 10;
                		target.y = rand() % 10;
                		shot_checker = checkShot(boardOne, target);
                	} while(shot_checker == -1);

                    if (shot_checker != -1 && shot_checker != 0) { //boat hit
                        stack = Push(stack,target,number_of_tested_shots);
                        printf("URADIO SAM PUSH <3");


                    }

                    updateCell(boardOne, target);
                }

                else {
                    target = element->coordinate;
                    number_of_tested_shots = element->number_of_tested_shots;

                    //try every possible direction
                    //if (number_of_tested_shots == -1){

                        //target = tryEveryDirection(boardOne,&target,stack)
                        //shot_checker = tryEveryDirection(boardOne,&target,&number_of_tested_shots);
                        target = tryEveryDirection(boardOne,stack);
                        updateCell(boardOne, target);
                    //}
                    //else{

                    //}
                }

                printBoard(boardOne, true);
            }
        }

        if(shot_checker != -1 && shot_checker != 0) {
            printf("> %c%c is a hit!\n", target.x + 'A', target.y + '0');
            for (i=0;i<NUMBER_OF_SHIPS_IN_TOTAL;i++){
                for (j=0;j<LONGEST_SHIP;j++){  //actually, it could go to lengt of hitted ship, but tbh, this is easier for implementation and execution time is not so much longer
                    if (ships_details[player][i].all_coordinates[j].x == target.x && ships_details[player][i].all_coordinates[j].y == target.y){
                        ships_details[player][i].number_of_remaining_fields -=1;
                        if (ships_details[player][i].number_of_remaining_fields <= 0){
                            printf("> you sank the ");
                            switch (shot_checker){
                                case 1:
                                    printf("nosac aviona");  //I don't know translations
                                    break;
                                case 2:
                                    printf ("krstarica");
                                    break;
                                case 3:
                                    printf("razarac");
                                    break;
                                case 4:
                                    printf("submarine");
                                    break;
                            }
                            printf("!\n");
                        }
                    if (game_mode == PLAYER_VS_COOP){
                        Pop(stack);
                    }
                    break;
                    }
                }
                if (j<LONGEST_SHIP){
                    break;
                }
            }
            fflush(stdin);
            getchar();
            getchar();

        }

        else {
            printf("> %c%c is a miss!\n", target.x + 'A', target.y + '0');
            fflush(stdin);
            getchar();
            getchar();
            player = !player;
        }
    }
    Free(stack);
    return 0;
}


/*
1. Treba dodati promenjivu i funkciju za to da li je brod potopljen
2. Co-op je pogodio sredinu broda pa isao dva desno pa kad sam ja zavrsio, nije zavrsio brod nego gadjao gore levo kao random. Ispravi(prva slika)
3. Dodaj isto sto sam ja dodao za window size ili ti bash size kod tebe, ako hoces (druga slika)
*/
