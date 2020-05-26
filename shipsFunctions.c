#include "battleship.h"

/*
 * This function sets symbols of the board to the proper ship symbols
 *
 * Parameters:
 *     board     - matrix of cells
 *     beginning - coordinates of the first cell of the ship
 *     direction - direction in which the ship is being placed
 *     ship      - type of the ship that's being placed
 *
 * Return(void):
 *     Nothing
 */

void putShipOnBoard(cell board[][COLS], coordinates beginning, int direction, ShipType ship) {
    // Iterate for the length of the ship
    for(int i = 0; i < ship.length; i++) {
        if(direction == HORIZONTAL)
            // If placed horizontally, move by Y axis
            board[beginning.x][beginning.y + i].symbol = ship.symbol;
        else
            // If placed vertically, move by X axis
            board[beginning.x + i][beginning.y].symbol = ship.symbol;
    }
}

/*
 * This function checks if it's possible to place a ship based
 * on it's first cell and direction
 *
 * Parameters:
 *     board     - matrix of cells
 *     beginning - coordinates of the first cell of the ship
 *     length    - length of the ship that's being placed
 *     direction - direction in which the ship is being placed
 *
 * Return(bool):
 *     true  - if it isn't possible to place a ship
 *     false - if it is possible to place a ship
 */

bool checkShipPlacement(cell board[][COLS], coordinates beginning, int length, int direction) {
    // We don't have to iterate through it's length if the end of the ship goes out of the board
    if(direction == HORIZONTAL && beginning.y + length > COLS) return true;
    else if(direction == VERTICAL && beginning.x + length > ROWS) return true;
    // Iterate through the length to check if the ship is colliding with another ship
    for(int i = 0; i < length; i++) {
        if(direction == HORIZONTAL) {
            if(board[beginning.x][beginning.y + i].symbol != WATER) return true;
        } else {
            if(board[beginning.x + i][beginning.y].symbol != WATER) return true;
		}
    }
    return false;
}

/*
 * This function places ships on board randomly
 *
 * Parameters:
 *     board        - matrix of cells
 *     ship         - all the ships that are being placed
 *     ship_details - details about ships
 *
 * Return(void):
 *     Nothing
 */

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

/*
 * This function places ships on board manually
 * The way it works is that user inputs beginning coordinates
 * and the direction. That's enough for the ship to be placed.
 *
 * Parameters:
 *     board        - matrix of cells
 *     ship         - all the ships that are being placed
 *     ship_details - details about ships
 *
 * Return(void):
 *     Nothing
 */

void manualShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS], shipDetails ship_details[]) {
	coordinates beginning; // Stores beginning coordinates
	int direction;         // Stores direction
    int k = 0,z = 0;       // Counters
    // Iterate through all types of ships
	for(int i = 0; i < NUM_OF_SHIPS; i++) {
        // Iterate through all ships of same type
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

/*
 * This function checks for sunk ships
 *
 * Parameters:
 *     target       - targeted cell
 *     ship_details - details about ships
 *     player       - player that's being targeted
 *
 * Return(int):
 *     1 - if sank
 *     0 - if nothing happened
 */

int isShipSunken(coordinates target, shipDetails ships_details[][COLS],int player){
    int i,j;
    //checks every coordinate that contains a ship and decreases number of fields that ship contains
    for (i=0;i<NUMBER_OF_SHIPS_IN_TOTAL;i++){
        for (j=0;j<LONGEST_SHIP;j++){  //actually, it could go to lengt of hitted ship, but tbh, this is easier for implementation and execution time is not so much longer
            if (ships_details[player][i].all_coordinates[j].x == target.x && ships_details[player][i].all_coordinates[j].y == target.y){
                ships_details[player][i].number_of_remaining_fields -=1;
                if (ships_details[player][i].number_of_remaining_fields <= 0){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
    }
}
