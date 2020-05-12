#include "battleship.h"

void initializeBoard(cell board[][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j].symbol          = WATER;
			board[i][j].position.row    = i;
			board[i][j].position.column = j;
		}
    }
}

void printBoard (cell gameBoard [][COLS], bool showPegs) {
	int i = 0, j = 0;

	printf ("  0 1 2 3 4 5 6 7 8 9\n");

	for (i = 0; i < ROWS; i++) {
		printf ("%d ", i);

		for (j = 0; j < COLS; j++) {
			if (showPegs == TRUE)
				printf ("%c ", gameBoard [i][j].symbol);
			else {
				switch (gameBoard [i][j].symbol) {
					case HIT:   printf ("%c ", HIT);   break;
					case MISS:  printf ("%c ", MISS);  break;
					case WATER:
					default:    printf ("%c ", WATER); break;
				}
			}
		}

		putchar ('\n');
	}
}

void putShipOnBoard(cell board[][COLS], coordinates beginning, int direction, ShipType ship) {
    for(int i = 0; i < ship.length; i++) {
        if(direction == HORIZONTAL)
            board[beginning.row][beginning.column + i].symbol = ship.symbol;
        else
            board[beginning.row + i][beginning.column].symbol = ship.symbol;
    }
}

void randomizeShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]) {
    coordinates beginning;
    int direction;
    for(int i = 0; i < NUM_OF_SHIPS; i++) {
        for(int j = 0; j < ship[i].ships; j++) {
            do {
                beginning.row = rand() % 10;
                beginning.column = rand() % 10;
                direction = rand() % 2;
            } while(checkShipPlacement(board, beginning, ship[i].length, direction));
            putShipOnBoard(board, beginning, direction, ship[i]);
            printBoard(board, TRUE);
        }
    }
}

void manualShips(cell board[][COLS], ShipType ship[NUM_OF_SHIPS]) {

}

bool checkShipPlacement(cell board[][COLS], coordinates beginning, int length, int direction) {
    if(direction == HORIZONTAL && beginning.column + length > COLS) return TRUE;
    else if(direction == VERTICAL && beginning.row + length > ROWS) return TRUE;

    for(int i = 0; i < length; i++) {
        if(direction == HORIZONTAL)
            if(board[beginning.row][beginning.column + i].symbol != WATER && beginning.column + i < COLS) return TRUE;
        else
            if(board[beginning.row + i][beginning.column].symbol != WATER && beginning.row + i < ROWS) return TRUE;
    }
    return FALSE;
}

/*void updateBoard (cell board[][COLS], coordinates target) {
	switch (board[target.row][target.column].symbol) {
		case WATER:
			board[target.row][target.column].symbol = MISS;
			break;
		case NOSAC_AVIONA:
		case KRSTARICA:
		case RAZARAC:
		case PODMORNICA:
			board[target.row][target.column].symbol = HIT;
			break;
		case HIT:
		case MISS:
		default:
			break;
	}
}

coordinates getTarget() {
    coordinates target;
	char temp[3];
    temp[0] = 0;
    do {
        if(temp[0]) printf("> Try again\n");
    	fflush (stdin);
    	printf ("> Enter target field(ex. A8):\n");
    	printf ("> ");
    	scanf ("%2s", temp);
        temp[0] = toupper(temp[0]) - 'A';
        if(temp[0] < 0 || temp[0] > 9)  {
            system("cls");
            continue;
        }
        target.row = temp[0];
        target.column = temp[1] - '0';
        break;
    } while(TRUE);
	return target;
}

short checkShot (cell gameBoard[][COLS], coordinates target) {
	int hit = -2;

	switch (gameBoard[target.row][target.column].symbol) {
		case WATER:
			hit = 0;
			break;
		case NOSAC_AVIONA:
		case KRSTARICA:
		case RAZARAC:
		case PODMORNICA:
			hit = 1;
			break;
		case HIT:
		case MISS:
		default:
			hit = -1;
			break;
	}

	return hit;
}*/
