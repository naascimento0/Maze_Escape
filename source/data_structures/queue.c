#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

struct queue{
	ForwardList *list;
};

Queue *queue_construct(){
	Queue *q = malloc(sizeof(Queue));
	q->list = forward_list_construct();
	return q;
}

void queue_push(Queue *queue, void *data){
	forward_list_push_back(queue->list, data);
}

int queue_empty(Queue *queue){
	return !forward_list_size(queue->list);
}

void* queue_pop(Queue *queue){
	return forward_list_pop_front(queue->list);
}
void queue_destroy(Queue *queue){
	forward_list_destroy(queue->list);
	free(queue);
}
