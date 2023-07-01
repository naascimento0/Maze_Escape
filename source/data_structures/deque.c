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
	d->front = 0;
	d->rear = 0;
	d->data = calloc(INITIAL_BLOCK_COUNT, sizeof(deque_type*));
	d->data[d->front_block] = calloc(BLOCK_SIZE, sizeof(deque_type));
	return d;
}

void deque_push_back(Deque *d, void *value){
	if(d->rear == BLOCK_SIZE){
		if(d->rear_block == d->blocks_amount - 1)
			deque_data_move(d);

		d->rear_block++;
		d->rear = 0;
	}

	if(d->data[d->rear_block] == NULL)
		d->data[d->rear_block] = calloc(BLOCK_SIZE, sizeof(deque_type));

	d->data[d->rear_block][d->rear++] = value;
}

void deque_push_front(Deque *d, void *value){
	if(!d->front){
		if(!d->front_block)
			deque_data_move(d);

		if(d->data[d->front_block][d->front] == NULL){
			d->data[d->front_block][d->front] = value;
			d->rear = (d->rear == d->front) && (d->rear_block == d->front_block) ? d->rear + 1 : d->rear;
			return;
		}

		d->front_block--;
		if(d->data[d->front_block] == NULL)
			d->data[d->front_block] = calloc(BLOCK_SIZE, sizeof(deque_type));

		d->front = BLOCK_SIZE - 1;
		d->data[d->front_block][d->front] = value;

	}else
		d->data[d->front_block][--d->front] = value;
}

void deque_data_move(Deque *d){
	if(!d->front_block && d->rear_block == d->blocks_amount - 1){
		deque_type **new_data = calloc(d->blocks_amount * 2, sizeof(deque_type*));
		d->blocks_amount *= 2;
		int aux = d->rear_block - d->front_block;
		d->front_block = d->blocks_amount / 4;

		int i, j;
		for(i = 0, j = d->front_block; i <= d->rear_block; i++, j++)
			new_data[j] = d->data[i];

		d->rear_block = d->front_block + aux;
		free(d->data);
		d->data = new_data;

	}else{
		deque_type **new_data = calloc(d->blocks_amount, sizeof(deque_type*));
		int new_center;
		if(d->rear_block < d->blocks_amount - 1){
			new_center = d->blocks_amount / 4;
			while(new_center + d->rear_block - d->front_block >= d->blocks_amount)
				new_center--;

		}else if(d->front_block >= 1)
			new_center = d->front_block / 2;

		int i, j;
		for(i = new_center, j = d->front_block; j <= d->rear_block; i++, j++)
			new_data[i] = d->data[j];

		free(d->data);
		d->rear_block = new_center + (d->rear_block - d->front_block);
		d->front_block = new_center;
		d->data = new_data;
	}
}

void* deque_pop_back(Deque *d){
	if(!deque_size(d))
		exit(printf("the deque is empty (deque_pop_back)"));

	deque_type pop_element;
	if(!d->rear){
		d->rear = BLOCK_SIZE - 1;
		pop_element = d->data[--d->rear_block][d->rear];
		free(d->data[d->rear_block + 1]);
		d->data[d->rear_block + 1] = NULL;
	}else
		pop_element = d->data[d->rear_block][--d->rear];

	if(!deque_size(d))
		d->front = d->rear = 0;

	d->data[d->rear_block][d->rear] = NULL;
	return pop_element;
}

void* deque_pop_front(Deque *d){
	if(!deque_size(d))
		exit(printf("the deque is empty (deque_pop_front)"));

	deque_type pop_element;
	if(d->front == BLOCK_SIZE - 1){
		pop_element = d->data[d->front_block][d->front];
		d->data[d->front_block][d->front] = NULL;
		free(d->data[d->front_block]);
		d->data[d->front_block++] = NULL;
		d->front = 0;
	}else{
		pop_element = d->data[d->front_block][d->front];
		d->data[d->front_block][d->front++] = NULL;
	}

	if(!deque_size(d)){
		d->front = d->rear = 0;
		d->front_block = d->rear_block;
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
	for(i = d->front_block; i <= d->rear_block; i++){

		int j = i == d->front_block ? d->front : 0;
		int limit = i == d->rear_block ? d->rear : BLOCK_SIZE;
		for(; j < limit; j++){
			free(d->data[i][j]);
		}

		free(d->data[i]);
	}

	free(d->data);
	free(d);
}
