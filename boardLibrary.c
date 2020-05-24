#include "battleship.h"

#ifdef __WIN32
/*
 * Sets window size on Windows to a given width and height
 *
 * Parameters:
 *     width  - number of characters displayed horizontally
 *     height - number of characters displayed vertically
 *
 * Return (void):
 *     Nothing
 */

void setWindowSize(int width, int height) {
	// Structure in WinConTypes.h (included in Windows.h) that holds buffer size
	COORD coord = {width, height};
	// Structure in WinConTypes.h (included in Windows.h) that holds all 4 corners of the window
	SMALL_RECT rect = {0, 0, width - 1, height - 1};
	// Security descriptor (included in Windows.h)
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// Functions for setting buffer and window size`
	SetConsoleScreenBufferSize(handle, coord);
	SetConsoleWindowInfo(handle, TRUE, &rect);
}
#endif
/*
 * Iterates through all board cells and initializes it's symbol and coordinates
 *
 * Parameters:
 *     board - matrix of cells
 *
 * Return (void):
 *     Nothing
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

/*
 * Prints out a given board
 *
 * Parameters:
 *     board - matrix of cells
 *     show  - determines whether to show placed ships or no (true/false)
 *
 * Notes: The whole function is divided in 2 section, X axis and Y axis + board.
 *       Each section is divided in 3 layers, top layer, middle layer and bottom layer.
 *       Each layer has 3 parts, left edge, middle and right edge.
 *
 * Return (void):
 *     Nothing
 */

void printBoard(cell board[][COLS], bool show) {
	// SECTION 1
		// Top layer
			// Left edge
				printf("     ");
				printf(SYMBOL_UPPER_LEFT_EDGE);
			// Middle
			    for(int i = 0; i < COLS * 2 - 1; i++) {
			        if(i % 2) printf(UPPER_BORDER_T);
			        else printf(HORIZONTAL_LINE);
			    }
			// Right edge
			    printf(SYMBOL_UPPER_RIGHT_EDGE);
				printf("\n");
		// Middle layer
			// Left edge
				printf("     ");
				printf(SINGLE_VERTICAL_LINE);
			// Middle
			    for(int i = 0; i < COLS * 2 - 1; i++) {
			        if(i % 2) printf(SINGLE_VERTICAL_LINE);
			        else printf("%2d ", (i + 1) / 2);
			    }
			// Right edge
			    printf(SINGLE_VERTICAL_LINE);
				printf("\n");
		// Bottom layer
			// Left edge
				printf("     ");
				printf(SYMBOL_LOWER_LEFT_EDGE);
			// Middle
			    for(int i = 0; i < COLS * 2 - 1; i++) {
			        if(i % 2) printf(LOWER_BORDER_T);
			        else printf(HORIZONTAL_LINE);
			    }
			// Right edge
			    printf(SYMBOL_LOWER_RIGHT_EDGE);
				printf("\n");
	// SECTION 2
		// Top layer
			// Y axis
				// Left edge
					printf(SYMBOL_UPPER_LEFT_EDGE);
				// Middle
					printf(HORIZONTAL_LINE);
				// Right edge
					printf(SYMBOL_UPPER_RIGHT_EDGE);

			// Board
				// Left edge
			    	printf(SYMBOL_UPPER_LEFT_EDGE);
				// Middle
				    for(int i = 0; i < COLS * 2 - 1; i++) {
				        if(i % 2) printf(SYMBOL_T_SECOND_TYPE);
				        else printf(HORIZONTAL_LINE);
				    }
				// Right edge
				    printf(SYMBOL_UPPER_RIGHT_EDGE);
					printf("\n");
		// Middle layer
		    for(int i = 0; i < ROWS * 2 - 1; i++) {
		        if(i % 2) {
					// Y axis
						// Left edge
							printf(SYMBOL_T_ROTATED_RIGHT);
						// Middle
							printf(HORIZONTAL_LINE);
						// Right edge
							printf(SYMBOL_T_ROTATED_LEFT);
					// Board
						// Left edge
			            	printf(SYMBOL_T_ROTATED_RIGHT_SECOND);
						// Middle
				            for(int j = 0; j < COLS * 2 - 1; j++) {
				                if(j % 2) printf(SYMBOL_CROSS);
								else printf(HORIZONTAL_LINE_SINGLE);
							}
						// Right edge
				            printf(SYMBOL_T_ROTATED_LEFT_SECOND);
							printf("\n");
		        } else {
					// Y axis
						// Left edge
							printf(SYMBOL_VERTICAL_LINE);
						// Middle
							printf(" %c ", (i+1)/2 + 'A');
						// Right edge
							printf(SYMBOL_VERTICAL_LINE);
					// Board
						// Left edge
			            	printf(SYMBOL_VERTICAL_LINE);
						// Middle
				            for(int j = 0; j < COLS * 2 - 1; j++) {
				                if(j % 2) printf(SYMBOL_VERTICAL_LINE_SINGLE);
								else
									switch(board[(i + 1) / 2][(j + 1) / 2].symbol) {
										case HIT:
										case MISS:
										case WATER:
											printf(" %c ", board[(i + 1) / 2][(j + 1) / 2].symbol);
											break;
										default:
											if(show)
												printf(" %c ", board[(i + 1) / 2][(j + 1) / 2].symbol);
											else
												printf(" %c ", WATER);
											break;
									}
							}
						// Right edge
				            printf(SYMBOL_VERTICAL_LINE);
							printf("\n");
		        }
		    }
		// Bottom layer
			// Y axis
				// Left edge
					printf(SYMBOL_LOWER_LEFT_EDGE);
				// Middle
					printf(HORIZONTAL_LINE);
				// Right edge
					printf(SYMBOL_LOWER_RIGHT_EDGE);
			// Board
				// Left edge
			    	printf(SYMBOL_LOWER_LEFT_EDGE);
				// Middle
				    for(int i = 0; i < COLS * 2 - 1; i++) {
				        if(i % 2) printf(SYMBOL_T_ROTATED_SECOND);
				        else printf(HORIZONTAL_LINE);
				    }
				// Right edge
				    printf(SYMBOL_LOWER_RIGHT_EDGE);
					printf("\n");
}

/*
 * Updates board's symbols with new target
 *
 * Parameters:
 *     board  - matrix of cells
 *     target - coordinates of a cell to update
 *
 * Notes: If targeted water, sets symbol to MISS.
 *       If targeted ship, sets symbol to HIT.
 *       Everything else is ignored.
 *
 * Return (void):
 *     Nothing
 */

void updateCell (cell board[][COLS], coordinates target) {
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
