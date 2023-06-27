#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

struct deque{
	int blocks_amount;
	int front_block;
	int rear_block;
	int front;
	int rear;
	deque_type **data;
	int data_amount;
};

Deque *deque_construct(void){
	Deque *d = malloc(sizeof(Deque));
	d->blocks_amount = INITIAL_BLOCK_COUNT;
	d->front_block = d->rear_block = INITIAL_BLOCK_COUNT / 2;
	d->front = d->rear = 0;
	d->data = calloc(INITIAL_BLOCK_COUNT, sizeof(deque_type*));
	d->data[d->front_block] = calloc(BLOCK_SIZE, sizeof(deque_type));
	d->data_amount = 0;

	return d;
}

//Deque* deque_construct(void){
//	Deque *d = malloc(sizeof(Deque));
//	d->blocks_amount = INITIAL_BLOCK_COUNT;
//	d->front_block = d->rear_block = INITIAL_BLOCK_COUNT / 2;
//	d->front = d->rear = 0;
//	d->data = calloc(BLOCK_SIZE, sizeof(deque_type*));
//	d->data_amount = 0;
//
//	int i;
//	for(i = 0; i < d->blocks_amount; i++){
//		d->data[i] = calloc(BLOCK_SIZE, sizeof(deque_type));
//	}
//
//	return d;
//}

void deque_push_back(Deque *d, void *value){
	if(!d->rear){
		d->rear_block++; //verificar se e o ultimo bloco para assim jogar pro centro
		if(d->data[d->rear_block] == NULL)
			d->data[d->rear_block] = calloc(BLOCK_SIZE, sizeof(deque_type));
		d->data[d->rear_block][d->rear] = value;
		d->rear++;
	}else if(d->rear == BLOCK_SIZE - 1){
		d->data[d->rear_block][d->rear] = value;
		d->rear = 0;

	}else
		d->data[d->rear_block][d->rear++] = value;


	d->data_amount++;
}

void deque_push_front(Deque *d, void *value){
	if(!d->front){
		d->front_block--; //verificar se precisa de jogar pro centro ou realloc
		if(d->data[d->front_block] == NULL){
			d->data[d->front_block] = calloc(BLOCK_SIZE, sizeof(deque_type));
			d->front = BLOCK_SIZE - 1;
			d->data[d->front_block][d->front] = value;
		}

	}else
		d->data[d->front_block][--d->front] = value;

	d->data_amount++;
}

void *deque_pop_back(Deque *d){


}
void *deque_pop_front(Deque *d){

}


void deque_data_move(Deque *d){

}
