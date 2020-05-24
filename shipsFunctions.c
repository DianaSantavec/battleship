#include "battleship.h"

void putShipOnBoard(cell board[][COLS], coordinates beginning, int direction, ShipType ship) {
    for(int i = 0; i < ship.length; i++) {
        if(direction == HORIZONTAL)
            board[beginning.x][beginning.y + i].symbol = ship.symbol;
        else
            board[beginning.x + i][beginning.y].symbol = ship.symbol;
    }
}

bool checkShipPlacement(cell board[][COLS], coordinates beginning, int length, int direction) {
    if(direction == HORIZONTAL && beginning.y + length > COLS) return true;
    else if(direction == VERTICAL && beginning.x + length > ROWS) return true;

    for(int i = 0; i < length; i++) {
        if(direction == HORIZONTAL) {
            if(board[beginning.x][beginning.y + i].symbol != WATER) return true;
        } else {
            if(board[beginning.x + i][beginning.y].symbol != WATER) return true;
		}
    }
    return false;
}

void randomShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS], shipDetails ship_details[]) {
    coordinates beginning;
    int direction;
    int k = 0,z; // k- easier counting of element in array nedded for ship_details, z-just a counter
    for(int i = 0; i < NUM_OF_SHIPS; i++) {
        for(int j = 0; j < ship[i].ships; j++) {
            do {
                beginning.x = rand() % ROWS;
                beginning.y = rand() % COLS;
                direction = rand() % 2;
            } while(checkShipPlacement(board, beginning, ship[i].length, direction));
            putShipOnBoard(board, beginning, direction, ship[i]);
            
            for (z=0;z<ship[i].length;z++){
                if(direction == HORIZONTAL){
                    ship_details[k].all_coordinates[z].x = beginning.x;
                    ship_details[k].all_coordinates[z].y = beginning.y + z;
                }
                else{
                    ship_details[k].all_coordinates[z].x = beginning.x + z;
                    ship_details[k].all_coordinates[z].y = beginning.y;
                }
            }
            for (z;z<LONGEST_SHIP;z++){
                ship_details[k].all_coordinates[z].x = -1;
                ship_details[k].all_coordinates[z].y = -1;
            }

            ship_details[k].number_of_remaining_fields = ship[i].length;
            k++;
            
        }
    }
}

void manualShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS], shipDetails ship_details[]) {
	coordinates beginning;
	int direction;
    int k = 0,z = 0;  //counters
	for(int i = 0; i < NUM_OF_SHIPS; i++) {
		for(int j = 0; j < ship[i].ships; j++) {
			system(CLEAR);
			printBoard(board, true);
			beginning = inputCoordinate();
            printf("> Enter direction:\n");
            do {
            	printf("> [1] Horizontal\n");
            	printf("> [2] Vertical\n");
                printf("> ");
            	scanf("%d", &direction);
                if(direction != 1 && direction != 2) {
                    system(CLEAR);
                    continue;
                }
            } while(checkShipPlacement(board, beginning, ship[i].length, --direction));
			putShipOnBoard(board, beginning, direction, ship[i]);

            for (z=0;z<ship[i].length;z++){
                if(direction == HORIZONTAL){
                    ship_details[k].all_coordinates[z].x = beginning.x;
                    ship_details[k].all_coordinates[z].y = beginning.y + z;
                }
                else{
                    ship_details[k].all_coordinates[z].x = beginning.x + z;
                    ship_details[k].all_coordinates[z].y = beginning.y;
                }
            }
            for (z;z<LONGEST_SHIP;z++){
                ship_details[k].all_coordinates[z].x = -1;
                ship_details[k].all_coordinates[z].y = -1;
            }

            ship_details[k].number_of_remaining_fields = ship[i].length;
            k++;
		}
	}
}
