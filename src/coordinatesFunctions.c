#include "battleship.h"

/*
 * Handles user input of coordinates.
 * Each input is supposed to be in form of 2 characters.
 * First character represents Y axis and is a letter from A to J (doesn't matter if it's capital or not).
 * Second character represents X axis and is a number from 0 to 9.
 *
 * Return (coordinates):
 *     Newly inputed coordinates
 */

coordinates inputCoordinate() {
    coordinates input;
	char temp[3];
    temp[0] = 0;
    do {
        if(temp[0]) printf("> Try again\n");
    	//fflush (stdin);
    	printf ("> Enter field(ex. A8):\n");
    	printf ("> ");
    	scanf ("%2s", temp);
		while ((getchar()) != '\n');
        // Format first character
        temp[0] = toupper(temp[0]) - 'A';
        // If wrong input, return to the beginning.
        if(temp[0] < 0 || temp[0] > 9) continue;
        // Format second character
        temp[1] = temp[1] - '0';
        // If wrong input, return to the beginning.
		if(temp[1] < 0 || temp[1] > 9) continue;
        // Save new coordinates
		input.x = temp[0];
		input.y = temp[1];
        // End
        break;
    } while(true);
	return input;
}

/*
 * Checks what's hit on the board
 *
 * Return (int):
 *     0  - hit WATER
 *     1  - hit any ship
 *     -1 - invalid target
 */

int checkShot (cell board[][COLS], coordinates target) {
	int hit = -2;
	switch (board[target.x][target.y].symbol) {
		case WATER:
			hit = 0;
			break;
		case NOSAC_AVIONA:
			hit = 1;
			break;
		case KRSTARICA:
			hit = 2;
			break;
		case RAZARAC:
			hit = 3;
			break;
		case PODMORNICA:
			hit = 4;
			break;
		case HIT:
		case MISS:
		default:
			hit = -1;
			break;
	}
	return hit;
}
