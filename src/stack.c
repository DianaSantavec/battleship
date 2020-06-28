#include "battleship.h"

stackElement *Push(stackElement *stack, coordinates new_coordinates, int number_of_tested_shots){
    stackElement *new_element = (stackElement*) malloc(sizeof(stackElement));
    
    if(new_element == NULL){
        return NULL;
    }

    new_element->coordinate = new_coordinates;
    new_element->number_of_tested_shots = -1;
    new_element->number_of_tested_shots = number_of_tested_shots;
    new_element->next = stack;
    return new_element;
}


stackElement * Pop(stackElement *stack){
    if (stack == NULL){
        return NULL;
    }
    else{
        stackElement *current = stack;
        stack = stack->next;
        free(current);
        return stack;
    }
}

const stackElement *Top(const stackElement *stack){
    if (stack == NULL){
        //stackElement empty;
        //empty.coordinate.x = -1;
        //empty.coordinate.y = -1;
        //empty.number_of_tested_shots = -1;
        return NULL;
    }
    else{
        stackElement new;
        new.coordinate.x = stack->coordinate.x;
        new.coordinate.y = stack->coordinate.y;
        new.number_of_tested_shots = stack->number_of_tested_shots;
        return &new;
    }

}

void Free(stackElement *stack){
    while (stack != NULL){
        stack = Pop(stack);
    }
}

int isEmpty(stackElement *stack) {
    return !stack;
}