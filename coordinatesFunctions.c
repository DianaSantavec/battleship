#include "battleship.h"

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