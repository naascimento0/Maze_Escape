#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "deque.h"

struct deque{
	int blocks_amount;
	int front_block;
	int rear_block;
	int front;
	int rear;
	deque_type **data;
};

Deque *deque_construct(void){
	Deque *d = malloc(sizeof(Deque));
	d->blocks_amount = INITIAL_BLOCK_COUNT;
	d->front_block = d->rear_block = INITIAL_BLOCK_COUNT / 2;
	d->front = d->rear = 0;
	d->data = calloc(INITIAL_BLOCK_COUNT, sizeof(deque_type*));
	d->data[d->front_block] = calloc(BLOCK_SIZE, sizeof(deque_type));

	return d;
}

void deque_push_back(Deque *d, void *value){
	if(!d->rear){
		if(d->rear_block + 1 >= d->blocks_amount)
			deque_data_move(d);

		d->rear_block++;
		if(d->data[d->rear_block] == NULL)
			d->data[d->rear_block] = calloc(BLOCK_SIZE, sizeof(deque_type));

		d->data[d->rear_block][d->rear] = value;
		d->rear++;

	}else if(d->rear == BLOCK_SIZE - 1){
		d->data[d->rear_block][d->rear] = value;
		d->rear = 0;

	}else
		d->data[d->rear_block][d->rear++] = value;
}

void deque_push_front(Deque *d, void *value){
	if(!d->front){
		if(d->front_block - 1 < 0)
			deque_data_move(d);

		d->front_block--;
		if(d->data[d->front_block] == NULL){
			d->data[d->front_block] = calloc(BLOCK_SIZE, sizeof(deque_type));
			d->front = BLOCK_SIZE - 1;
			d->data[d->front_block][d->front] = value;
		}

	}else
		d->data[d->front_block][--d->front] = value;
}


void deque_data_move(Deque *d){
	int index = d->front_block / 2;

	if(!index && !d->front_block){
		deque_type **new_data = calloc(d->blocks_amount + 2, sizeof(deque_type*));
		if(new_data == NULL){
			exit(printf("in 'deque_data_move' realloc error"));
		}

		int i, j;
		for(i = 0, j = 1; i < d->blocks_amount; i++, j++){
			new_data[j] = d->data[i];
		}

		d->blocks_amount += 2;
		d->data = new_data;
		d->front_block++;
		d->rear_block++;

	}else{
		int i, j;
		for(i = index, j = d->front_block; j < d->rear_block; i++, j++){
			d->data[i] = d->data[j];
		}

		d->front_block = index;
		d->rear_block -= index;
	}
}


void* deque_pop_back(Deque *d){
	if(!deque_size(d))
		exit(printf("the deque is empty (deque_pop_back)"));

	deque_type pop_element;
	int index = d->rear - 1;
	if(index < 0){
		pop_element = d->data[d->rear_block][BLOCK_SIZE - 1];
		d->data[d->rear_block][BLOCK_SIZE - 1] = NULL;
		d->rear = BLOCK_SIZE - 1;

	}else if(!index){
		pop_element = d->data[d->rear_block][--d->rear];
		deque_type *block_to_free = d->data[d->rear_block];
		free(block_to_free);
		d->rear_block--;

	}else{
		pop_element = d->data[d->rear_block][--d->rear];
		d->data[d->rear_block][d->rear] = NULL;
	}

	return pop_element;
}

void* deque_pop_front(Deque *d){
	if(!deque_size(d))
		exit(printf("the deque is empty (deque_pop_back)"));

	deque_type pop_element;
	if(d->front == BLOCK_SIZE - 1){
		pop_element = d->data[d->front_block][d->front];
		deque_type *block_to_free = d->data[d->front_block];
		free(block_to_free);
		d->front = 0;
		d->front_block++;

	}else{
		pop_element = d->data[d->front_block][d->front];
		d->data[d->front_block][d->front++] = NULL;
	}

	return pop_element;
}

int deque_size(Deque *d){
	return (d->rear_block - d->front_block) * BLOCK_SIZE + (d->rear - d->front);
}

void* deque_get(Deque *d, int idx){
	if(idx >= 0 && idx < deque_size(d)){
		int element_position = d->front + idx;
		int block_position = element_position / BLOCK_SIZE;
		return d->data[block_position][element_position % BLOCK_SIZE];
	}

	return NULL;
}

void deque_destroy(Deque *d){
	int i;
	for(i = d->front_block; i < d->rear_block; i++)
		free(d->data[i]);

	free(d->data);
	free(d);
}






