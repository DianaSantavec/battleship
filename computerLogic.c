#include "battleship.h"

/*
 * Implements a simple form of an artificial inteligence for CO-OP
 *
 * Parameters:
 *     board                  - matrix of cells
 *     target                 - pointer to coordinates value of a current target
 *     number_of_tested_shots - pointer to a variable that stores how many times computer played in a row
 */

coordinates tryEveryDirection(cell board[][COLS], stackElement *stack){
	printf("pristupa koordinatama\n");
	coordinates target = stack->coordinate;
	printf("[%d,%d]",target.x,target.y);
	int shot_checker;
printf("pristupa broju udaraca\n");
	if (stack->number_of_tested_shots == -1){	//right
		target.y += 1;
		stack->number_of_tested_shots = 0;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				printf("pokusava da odradi push\n");
				Push(stack,target,-1);
				return target;
			}
		}

		else{
			target.y -=1;
		}
	}

	if (stack->number_of_tested_shots == 0){	//left
		target.y -= 1;
		stack->number_of_tested_shots = 1;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				Push(stack,target,-1);
				return target;
			}
		}

		else{
			target.y +=1;
		}
	}

	if (stack->number_of_tested_shots == 1){	//up
		target.x += 1;
		stack->number_of_tested_shots = 2;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				Push(stack,target,-1);
				return target;
			}
		}

		else{
			target.x -=1;
		}
	}

	if (stack->number_of_tested_shots == 2){	//down
		target.x -= 1;
		stack->number_of_tested_shots = 3;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				Push(stack,target,-1);
				return target;
			}
		}

		else{
			target.x +=1;
		}
	}

	if ((target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)  || shot_checker == -1 || stack->number_of_tested_shots == 3 ){
		do {
        	target.x = rand() % 10;
        	target.y = rand() % 10;
        } while(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS);

		stack->number_of_tested_shots = -2;
		printf("pokusava pop\n");
		stack = Pop(stack);
	}
}


/*
	if (shot_checker != -1 && shot_checker != 0) {  //if boat is hitted remeber new coordinates
                        stack = Push(stack,target,number_of_tested_shots);
                        //last_target = target;
                        //number_of_tested_shots = 0;
                        printf("URADIO SAM PUSH <3");
                    }

                    else if (number_of_tested_shots == -2){
                        stack = Pop(stack);
                        printf("URADIO SAM POP AH AH AH AH >:)");
                    }

	return checkShot(board, *target);
}
*/