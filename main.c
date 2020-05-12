#include "battleship.h"
//#include "battleship.c"

int main() {
    int izbor;
    
    cell board1[ROWS][COLS], board2[ROWS][COLS];
    
    initializeBoard(board1);
    initializeBoard(board2);
    
    mainMenu();

    do{
        if (!scanf("%d",&izbor)){
            fflush();
            printf("Niste uneli cifru!");
        }
        if (izbor !=2 && izbor != 1){
            printf("Niste uneli validnu opciju!");
        }
    }while (izbor!=2 || izbor!=1);

    switch (izbor){
        case 1:
            //potreban unos imena igraca

            //koji prvi igra
            srand(time(NULL));
            int player = rand() % 2; 

            
            break;

        case 2:
            randomizeShips(board, ship);
            break;
    }

    
    ShipType ship[NUM_OF_SHIPS] = {
        {NOSAC_AVIONA, 4, 1},
        {KRSTARICA, 3, 2},
        {RAZARAC, 2, 3},
        {PODMORNICA, 1, 4},
    };

    return 0;
}
