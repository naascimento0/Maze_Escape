#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct stack{
    ForwardList *list;
};

Stack *stack_construct(){
	Stack *s = malloc(sizeof(Stack));
	s->list = forward_list_construct();
	return s;
}
void stack_push(Stack *stack, void *data){
	forward_list_push_front(stack->list, data);
}
int stack_empty(Stack *stack){
	return !forward_list_size(stack->list);
}
void* stack_pop(Stack *stack){
	return forward_list_pop_front(stack->list);
}
void stack_destroy(Stack *stack){
	forward_list_destroy(stack->list);
	free(stack);
}
