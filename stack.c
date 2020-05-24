#include "battleship.h"

stackElement *Push(stackElement *stack, coordinates new_coordinates){
    stackElement *new_element = (stackElement*) malloc(sizeof(stackElement));
    
    if(new_element == NULL){
        return NULL;
    }

    new_element->coordinate = new_coordinates;
    new_element->next = stack;
    return new_element;
}


stackElement * Pop(stackElement *stack){
    if (stack == NULL){
        return stack;
    }
    else{
        stackElement *current = stack;
        stack = stack->next;
        free(current);
        return stack;
    }
}

const coordinates Top(const stackElement *stack){
    if (stack == NULL){
        coordinates empy;
        empy.x = -1;
        empy.y = -1;
        return empy;
    }
    else{
        return stack->coordinate;
    }

}

void Free(stackElement *stack){
    while (stack != NULL){
        stack = Pop(stack);
    }
}