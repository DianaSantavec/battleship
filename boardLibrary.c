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


/* ---NEW----------------------NEW----------------------NEW------------------NEW--------NEW---- */
void printBoard (cell gameBoard [][COLS], bool showPegs) {
	/* -------------------------------------------------------------------------- */
	printf("     "); //instead of %7c
	printf(SYMBOL_UPPER_LEFT_EDGE);
    for(int i = 0; i < COLS * 2 - 1; i++) {
        if(i % 2) printf(UPPER_BORDER_T);
        else printf(HORIZONTAL_LINE);
    }
    printf(SYMBOL_UPPER_RIGHT_EDGE);
	printf("\n");
	printf("     ");
	printf(SINGLE_VERTICAL_LINE);
    for(int i = 0; i < COLS * 2 - 1; i++) {
        if(i % 2) printf(SINGLE_VERTICAL_LINE);
        else printf("%2d ", (i + 1) / 2);
    }
    printf(SINGLE_VERTICAL_LINE);
	printf("\n");

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

/* ---NEW----------------------NEW----------------------NEW------------------NEW--------NEW---- */
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
