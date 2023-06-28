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

//void deque_push_back(Deque *d, void *value){
//	if(!d->rear){ //LOGICA ESTA ERRADA QUANDO EU COLOCO O PRIMEIRO ELEMENTO
//		if(d->rear_block + 1 >= d->blocks_amount)
//			deque_data_move(d);
//
//		if(!deque_size(d)){
//			d->data[d->rear_block][d->rear++] = value;
//			return;
//		}
//
//		d->rear_block++;
//		if(d->data[d->rear_block] == NULL)
//			d->data[d->rear_block] = calloc(BLOCK_SIZE, sizeof(deque_type));
//
//		d->data[d->rear_block][d->rear++] = value;
//
//	}else if(d->rear == BLOCK_SIZE - 1){
//		d->data[d->rear_block][d->rear] = value;
//		d->rear = 0;
//	}else
//		d->data[d->rear_block][d->rear++] = value;
//}

void deque_push_back(Deque *d, void *value){
	if(d->rear >= BLOCK_SIZE){
		if(d->rear_block + 1 >= d->blocks_amount)
			deque_data_move(d);

		d->rear_block++;
		if(d->data[d->rear_block] == NULL)
			d->data[d->rear_block] = calloc(BLOCK_SIZE, sizeof(deque_type));

		d->rear = 0;
		d->data[d->rear_block][d->rear++] = value;

	}else
		d->data[d->rear_block][d->rear++] = value;
}

void deque_push_front(Deque *d, void *value){
	if(!d->front){
		if(d->front_block - 1 < 0)
			deque_data_move(d);

		if(!deque_size(d)){
			d->data[d->front_block][d->front] = value;
			d->rear++;
			return;
		}

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

	deque_display(d);

	int index = d->front_block / 2;

	if(!index && !d->front_block){
		deque_type **new_data = calloc(d->blocks_amount + 4, sizeof(deque_type*));

		int i, j;
		for(i = 0, j = 2; i < d->blocks_amount; i++, j++){
			new_data[j] = d->data[i];
		}

		d->blocks_amount += 4;
		d->data = new_data;
		d->front_block += 2;
		d->rear_block += 2;

	}else{
		int i, j;
		deque_type **new_data = calloc(d->blocks_amount, sizeof(deque_type*));
		for(i = index, j = d->front_block; j < d->rear_block; i++, j++){
			//d->data[i] = d->data[j]; //aqui está o erro
			new_data[i] = d->data[j];

		}

		d->front_block = index;
		d->rear_block -= index;
		//d->rear_block = index + (d->rear_block - d->front_block);
	}

	deque_display(d);
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
		deque_type *block_to_free = d->data[d->rear_block--];
		free(block_to_free);

	}else{
		pop_element = d->data[d->rear_block][--d->rear];
		d->data[d->rear_block][d->rear] = NULL;
	}

	return pop_element;
}

void* deque_pop_front(Deque *d){
	if(!deque_size(d))
		exit(printf("the deque is empty (deque_pop_front)"));

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
//	int i;
//	for(i = d->front_block; i <= d->rear_block; i++){
//		int j;
//		int data_amount = deque_size(d);
//		for(j = d->front, j <)
//	}
//		free(d->data[i]);

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

void deque_display(Deque *d){
	int i;
	for(i = d->front_block; i <= d->rear_block; i++){
		printf("BLOCK %d: ", i);

		int j = i == d->front_block ? d->front : 0;
		int limit = i == d->rear_block ? d->rear : BLOCK_SIZE;
		for(; j < limit; j++){
			Celula *c = d->data[i][j];
			printf("%d %d, ", c->x, c->y);
		}

		printf("\n");
	}
}






