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

void randomShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]) {
    coordinates beginning;
    int direction;
    for(int i = 0; i < NUM_OF_SHIPS; i++) {
        for(int j = 0; j < ship[i].ships; j++) {
            do {
                beginning.x = rand() % 10;
                beginning.y = rand() % 10;
                direction = rand() % 2;
            } while(checkShipPlacement(board, beginning, ship[i].length, direction));
            putShipOnBoard(board, beginning, direction, ship[i]);
        }
    }
}

void manualShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]) {
	coordinates beginning;
	int direction;
	for(int i = 0; i < NUM_OF_SHIPS; i++) {
		for(int j = 0; j < ship[i].ships; j++) {
			system(CLEAR);
			printBoard(board, true);
			do {
				beginning = inputCoordinate();
				printf("> Enter direction:\n");
				printf("> [1] Horizontal\n");
				printf("> [2] Vertical\n");
				printf("> ");
				scanf("%d", &direction);
			} while(checkShipPlacement(board, beginning, ship[i].length, --direction));
			putShipOnBoard(board, beginning, direction, ship[i]);
		}
	}
}