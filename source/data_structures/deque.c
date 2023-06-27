#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

struct deque{
	int blocks_amount;
	int front_block;
	int back_block;
	int front;
	int rear;
	deque_type **data;
	int data_amount;
};

Deque* deque_construct(void){
	Deque *d = malloc(sizeof(Deque));
	d->blocks_amount = INITIAL_BLOCK_COUNT;
	d->front_block = d->back_block = INITIAL_BLOCK_COUNT / 2;
	d->front = d->rear = 0;
	d->data = calloc(BLOCK_SIZE, sizeof(deque_type*));
	d->data_amount = 0;

	int i;
	for(i = 0; i < d->blocks_amount; i++){
		d->data[i] = calloc(BLOCK_SIZE, sizeof(deque_type));
	}

	return d;
}

void deque_push_back(Deque *d, void *val){
	if(d->rear == BLOCK_SIZE){
		if(d->back_block == d->blocks_amount - 1){
			d->blocks_amount += 2;
			d->data = realloc(d->data, d->blocks_amount * sizeof(deque_type*));

			int i = d->blocks_amount;
			while(--i && (i >= d->blocks_amount - 2))
				d->data[i] = calloc(BLOCK_SIZE, sizeof(deque_type));
		}

		d->back_block++;
		d->rear = 0;
	}

	d->data[d->back_block][d->rear] = val;
	d->rear++;
	d->data_amount++;
}

void deque_data_move(Deque *d){

}
