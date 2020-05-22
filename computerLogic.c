#include "battleship.h"

/*
 * Implements a simple form of an artificial inteligence for CO-OP
 *
 * Parameters:
 *     board                  - matrix of cells
 *     target                 - pointer to coordinates value of a current target
 *     number_of_tested_shots - pointer to a variable that stores how many times computer played in a row
 */

int tryEveryDirection(cell board[][COLS], coordinates *target, int *number_of_tested_shots){
	target->y += 1;
	if (checkShot(board, *target) == -1 && *number_of_tested_shots == 0) {
		target->y -= 2;
		*number_of_tested_shots += 1;
		if (checkShot(board, *target) == -1 && *number_of_tested_shots == 1) {
			target->y += 1;
			target->x += 1;
			*number_of_tested_shots += 1;
			if (checkShot(board, *target) == -1 && *number_of_tested_shots == 2) {
				target->x -= 2;
				*number_of_tested_shots += 1;
				if (checkShot(board, *target) == -1 && *number_of_tested_shots == 3) {
					do {
                		target->x = rand() % 10;
                		target->y = rand() % 10;
                	} while(checkShot(board, *target) == -1);
					*number_of_tested_shots = 0;
				}
			}
		}
	}

	return checkShot(board, *target);
}
