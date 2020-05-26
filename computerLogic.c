#include "battleship.h"

coordinates tryEveryDirection(cell board[][COLS], stackElement **stack){

	coordinates target = (*stack)->coordinate;		
	int shot_checker;

	if ((*stack)->number_of_tested_shots == -1){	//right   provera sta se nalazi desno od pogotka
		target.y += 1;
		(*stack)->number_of_tested_shots = 0;
		shot_checker =checkShot(board,target);
		printf("%d",shot_checker);
		if (shot_checker != -1 && (target.x > 0 && target.x < COLS && target.y >0 && target.y <ROWS)){ 	//try to go right
		//if right is not tested already and it exist (is not out of the boundaries)
			
			if (shot_checker != 0){		//if new target is a hit remember coordinates for next testing
				*stack = Push(*stack,target,-1); 	
				return target;
			}
			return target;		//return new target even if it is a miss
		}
		
		target.y -=1; 		//return to a hit from beginning
		
	}
<<<<<<< HEAD

	if ((*stack)->number_of_tested_shots == 0){	//left
		target.y -= 1;
		(*stack)->number_of_tested_shots = 1;
		shot_checker =checkShot(board,target);
		printf("%d",shot_checker);
		if (shot_checker != -1 && (target.x > 0 && target.x < COLS && target.y >0 && target.y <ROWS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
			return target;
		}

		
		target.y +=1;
		
||||||| 1592903
	if (checkShot(board, *target) == -1 && *number_of_tested_shots == 1) {
		target->y += 1;
		target->x += 1;
		*number_of_tested_shots = 2;
=======

	if ((*stack)->number_of_tested_shots == 0){	//left
		target.y -= 1;
		(*stack)->number_of_tested_shots = 1;
		shot_checker =checkShot(board,target);
		printf("%d",shot_checker);
		if (shot_checker != -1 && (target.x > 0 && target.x < COLS && target.y >0 && target.y <ROWS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
			return target;
		}

		
		target.y +=1;
		
	}

	if ((*stack)->number_of_tested_shots == 1){	//up
		target.x += 1;
		(*stack)->number_of_tested_shots = 2;
		shot_checker =checkShot(board,target);
		printf("%d",shot_checker);
		if (shot_checker != -1 && (target.x > 0 && target.x < COLS && target.y >0 && target.y <ROWS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
			return target;
		}

		
		target.x -=1;
		
>>>>>>> main2_0
	}
<<<<<<< HEAD

	if ((*stack)->number_of_tested_shots == 1){	//up
		target.x += 1;
		(*stack)->number_of_tested_shots = 2;
		shot_checker =checkShot(board,target);
		printf("%d",shot_checker);
		if (shot_checker != -1 && (target.x > 0 && target.x < COLS && target.y >0 && target.y <ROWS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
			return target;
		}

		
		target.x -=1;
		
||||||| 1592903
	if (checkShot(board, *target) == -1 && *number_of_tested_shots == 2) {
		target->x -= 2;
		*number_of_tested_shots = 3;
=======

	if ((*stack)->number_of_tested_shots == 2){	//down
		target.x -= 1;
		(*stack)->number_of_tested_shots = 3;
		shot_checker =checkShot(board,target);
		printf("%d",shot_checker);
		if (shot_checker != -1 && (target.x > 0 && target.x < COLS && target.y >0 && target.y <ROWS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
			return target;
		}

		
		target.x +=1;
		
>>>>>>> main2_0
	}
<<<<<<< HEAD
||||||| 1592903
	if (checkShot(board, *target) == -1) {
		do {
        	target->x = rand() % 10;
        	target->y = rand() % 10;
        } while(checkShot(board, *target) == -1);
=======

	//if all fields around hit are tested do a random shot
	if ((target.x < 0 || target.x >= COLS || target.y <0 || target.y >=ROWS)  || shot_checker == -1 || (*stack)->number_of_tested_shots == 3 ){
		do {
        	target.x = rand() % 10;
        	target.y = rand() % 10;
			shot_checker = checkShot(board,target);
        } while(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=ROWS || shot_checker == -1);
>>>>>>> main2_0

<<<<<<< HEAD
	if ((*stack)->number_of_tested_shots == 2){	//down
		target.x -= 1;
		(*stack)->number_of_tested_shots = 3;
		shot_checker =checkShot(board,target);
		printf("%d",shot_checker);
		if (shot_checker != -1 && (target.x > 0 && target.x < COLS && target.y >0 && target.y <ROWS)){
			
			if (shot_checker != 0){
				*stack = Push(*stack,target,-1);
				return target;
			}
			return target;
		}

		
		target.x +=1;
		
||||||| 1592903
		*number_of_tested_shots = -1;
=======
		(*stack)->number_of_tested_shots = -2;	//everything is tested
		*stack = Pop(*stack);			//forget field
		return target;
>>>>>>> main2_0
	}
<<<<<<< HEAD

	//if all fields around hit are tested do a random shot
	if ((target.x < 0 || target.x >= COLS || target.y <0 || target.y >=ROWS)  || shot_checker == -1 || (*stack)->number_of_tested_shots == 3 ){
		do {
        	target.x = rand() % 10;
        	target.y = rand() % 10;
			shot_checker = checkShot(board,target);
        } while(target.x < 0 || target.x >= COLS || target.y <0 || target.y >=ROWS || shot_checker == -1);

		(*stack)->number_of_tested_shots = -2;	//everything is tested
		*stack = Pop(*stack);			//forget field
		return target;
	}
}
||||||| 1592903

	return checkShot(board, *target);
}
=======
}
>>>>>>> main2_0
