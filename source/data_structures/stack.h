#ifndef STACK_H_
#define STACK_H_
#include "forward_list.h"

typedef struct stack Stack;

Stack *stack_construct();

void stack_push(Stack *stack, void *data);

int stack_empty(Stack *stack);

void* stack_pop(Stack *stack);

void stack_destroy(Stack *stack);

#endif
