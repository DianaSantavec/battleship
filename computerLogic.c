#include "battleship.h"

coordinates tryEveryDirection(cell board[][COLS], stackElement **stack){

	coordinates target = (*stack)->coordinate;
	int shot_checker;

	if ((*stack)->number_of_tested_shots == -1){	//right
	printf("right");
		target.y += 1;
		(*stack)->number_of_tested_shots = 0;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				printf("pokusava da odradi push\n");
				*stack = Push(*stack,target,-1);
				return target;
			}
		}

		else{
			target.y -=1;
		}
	}

	if ((*stack)->number_of_tested_shots == 0){	//left
		printf("left");
		target.y -= 1;
		(*stack)->number_of_tested_shots = 1;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
		}

		else{
			target.y +=1;
		}
	}

	if ((*stack)->number_of_tested_shots == 1){	//up
	printf("up");
		target.x += 1;
		(*stack)->number_of_tested_shots = 2;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
		}

		else{
			target.x -=1;
		}
	}

	if ((*stack)->number_of_tested_shots == 2){	//down
	printf("down");
		target.x -= 1;
		(*stack)->number_of_tested_shots = 3;
		shot_checker =checkShot(board,target);
		if (shot_checker != -1 && !(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
		}

		else{
			target.x +=1;
		}
	}

	if ((target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS)  || shot_checker == -1 || (*stack)->number_of_tested_shots == 3 ){
		do {
        	target.x = rand() % 10;
        	target.y = rand() % 10;
        } while(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=COLS);

		(*stack)->number_of_tested_shots = -2;
		printf("pokusava pop\n");
		*stack = Pop(*stack);
		return target;
	}
}