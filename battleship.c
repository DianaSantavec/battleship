#include "battleship.h"

/*
 * Iterates through all board cells and initializes it's symbol and coordinates
 * Parameters:
 *     board - matrix of cells
 */

void initializeBoard(cell board[][COLS]) {
	// Loop through all rows
	for (int i = 0; i < ROWS; i++) {
		// Loop through all columns
		for (int j = 0; j < COLS; j++) {
			// Initialize cell
			board[i][j].symbol		= WATER;
			board[i][j].position.x	= i;
			board[i][j].position.y	= j;
		}
    }
}

void printBoard (cell gameBoard [][COLS], bool showPegs) {
	/* -------------------------------------------------------------------------- */
    printf("     ");
	printf(SYMBOL_UPPER_LEFT_EDGE);
    for(int i = 0; i < COLS * 2 - 1; i++) {
        if(i % 2) printf(UPPER_BORDER_T);
        else printf(HORIZONTAL_LINE);
    }
    printf(SYMBOL_UPPER_RIGHT_EDGE);
	printf("\n");

	//printf("%7c", 186);
	//printf("       ");
	printf("     ");
	printf(SINGLE_VERTICAL_LINE);
    for(int i = 0; i < COLS * 2 - 1; i++) {
        if(i % 2) printf(SINGLE_VERTICAL_LINE);
        else printf("%2d ", (i + 1) / 2);
    }
    printf(SINGLE_VERTICAL_LINE);
	printf("\n");

    //printf("%7c", 200);
	printf("     ");
	printf(SYMBOL_LOWER_LEFT_EDGE);

    for(int i = 0; i < COLS * 2 - 1; i++) {
        if(i % 2) printf(LOWER_BORDER_T);
        else printf(HORIZONTAL_LINE);
    }
    printf(SYMBOL_LOWER_RIGHT_EDGE);
	printf("\n");
    /* -------------------------------------------------------------------------- */

	printf(SYMBOL_UPPER_LEFT_EDGE);
	printf(HORIZONTAL_LINE);
	printf(SYMBOL_UPPER_RIGHT_EDGE);

    printf(SYMBOL_UPPER_LEFT_EDGE);
    for(int i = 0; i < COLS * 2 - 1; i++) {
        if(i % 2) printf(SYMBOL_T_SECOND_TYPE);
        else printf(HORIZONTAL_LINE);
    }
    printf(SYMBOL_UPPER_RIGHT_EDGE);
	printf("\n");

    for(int i = 0; i < ROWS * 2 - 1; i++) {
        if(i % 2) {
			printf(SYMBOL_T_ROTATED_RIGHT);
			printf(HORIZONTAL_LINE);
			printf(SYMBOL_T_ROTATED_LEFT);

            printf(SYMBOL_T_ROTATED_RIGHT_SECOND);
            for(int j = 0; j < COLS * 2 - 1; j++)
                if(j % 2) printf(SYMBOL_CROSS);
				else printf(HORIZONTAL_LINE_SINGLE);
            printf(SYMBOL_T_ROTATED_LEFT_SECOND);
			printf("\n");
        } else {
			printf(SYMBOL_VERTICAL_LINE);
			printf(" %c ", (i+1)/2 + 'A');
			printf(SYMBOL_VERTICAL_LINE);

            printf(SYMBOL_VERTICAL_LINE);
            for(int j = 0; j < COLS * 2 - 1; j++)
                if(j % 2) printf(SYMBOL_VERTICAL_LINE_SINGLE);
				else {
					switch(gameBoard[i][j].symbol) {
						case HIT:
						case MISS:
						case WATER:
							printf(" %c ", gameBoard[i][j].symbol);
							break;
						default:
							if(showPegs)
								printf(" %c ", gameBoard[i][j].symbol);
							else
								printf(" %c ", WATER);
							break;
					}
				}
            printf(SYMBOL_VERTICAL_LINE);
			printf("\n");
        }
    }
	printf(SYMBOL_LOWER_LEFT_EDGE);
	printf(HORIZONTAL_LINE);
	printf(SYMBOL_LOWER_RIGHT_EDGE);

    printf(SYMBOL_LOWER_LEFT_EDGE);
    for(int i = 0; i < COLS * 2 - 1; i++) {
        if(i % 2) printf(SYMBOL_T_ROTATED_SECOND);
        else printf(HORIZONTAL_LINE);
    }
    printf(SYMBOL_LOWER_RIGHT_EDGE);
	printf("\n");
}

void putShipOnBoard(cell board[][COLS], coordinates beginning, int direction, ShipType ship) {
    for(int i = 0; i < ship.length; i++) {
        if(direction == HORIZONTAL)
            board[beginning.x][beginning.y + i].symbol = ship.symbol;
        else
            board[beginning.x + i][beginning.y].symbol = ship.symbol;
    }
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

void updateBoard (cell board[][COLS], coordinates target) {
	switch (board[target.x][target.y].symbol) {
		case WATER:
			board[target.x][target.y].symbol = MISS;
			break;
		case NOSAC_AVIONA:
		case KRSTARICA:
		case RAZARAC:
		case PODMORNICA:
			board[target.x][target.y].symbol = HIT;
			break;
		case HIT:
		case MISS:
		default:
			break;
	}
}

coordinates inputCoordinate() {
    coordinates input;
	char temp[3];
    temp[0] = 0;
    do {
        if(temp[0]) printf("> Try again\n");
    	fflush (stdin);
    	printf ("> Enter field(ex. A8):\n");
    	printf ("> ");
    	scanf ("%2s", temp);
        temp[0] = toupper(temp[0]) - 'A';
        if(temp[0] < 0 || temp[0] > 9) continue;
        temp[1] = temp[1] - '0';
		if(temp[1] < 0 || temp[1] > 9) continue;
		input.x = temp[0];
		input.y = temp[1];
        break;
    } while(true);
	return input;
}

int checkShot (cell gameBoard[][COLS], coordinates target) {
	int hit = -2;
	switch (gameBoard[target.x][target.y].symbol) {
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
}

void mainMenu(){
	printf("\t\tBATTLESHIP\n\n1) Dva igraca\n2) Protiv racunara\n\nUnesite broj opcije: ");
}

int tryEveryDirection(cell playersBoard[][COLS], coordinates *target, int *number_of_tested_shots){
	int shot_checker;

	target->y +=1;
	shot_checker = checkShot(playersBoard, *target);

	if (shot_checker == -1 && *number_of_tested_shots == 0){
		target->y -=2;
		shot_checker = checkShot(playersBoard, *target);
		*number_of_tested_shots += 1;


		if (shot_checker == -1 && *number_of_tested_shots == 1){
			target->y +=1;
			target->x +=1;
			shot_checker = checkShot(playersBoard, *target);
			*number_of_tested_shots += 1;

			if (shot_checker == -1 && *number_of_tested_shots == 2){
				target->x -=2;
				shot_checker = checkShot(playersBoard, *target);
				*number_of_tested_shots += 1;

				if (shot_checker == -1 && *number_of_tested_shots == 3){
					do {
                		target->x = rand() % 10;
                		target->y = rand() % 10;
                		shot_checker = checkShot(playersBoard, *target);
                	} while(shot_checker == -1);
					*number_of_tested_shots = 0;
				}
			}
		}
	}

	return shot_checker;
}
