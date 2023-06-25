#ifndef QUEUE_H_
#define QUEUE_H_
#include "forward_list.h"

typedef struct queue Queue;

Queue *queue_construct();

void queue_push(Queue *queue, void *data);

int queue_empty(Queue *queue);

void *queue_pop(Queue *queue);

void queue_destroy(Queue *queue);

#endif
