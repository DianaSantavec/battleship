#include "battleship.h"

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
