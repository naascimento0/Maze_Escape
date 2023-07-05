#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

struct HeapNode{
	heap_type data;
	double priority;
};

struct Heap{
	HashTable *h;
	int size;
	HeapNode **nodes;
	int capacity;
};

Heap *heap_construct(HashTable *h){
	Heap *heap = malloc(sizeof(Heap));
	heap->h = h;
	heap->size = 0;
	heap->capacity = INITIAL_CAPACITY;
	heap->nodes = calloc(INITIAL_CAPACITY, sizeof(HeapNode*));
	return heap;
}

void* heap_push(Heap *heap, void *data, double priority){
	if(heap->size >= heap->capacity){
		heap->capacity *= 2;
		heap->nodes = realloc(heap->nodes, heap->capacity * sizeof(HeapNode*));
	}

	int *index = hash_table_get(heap->h, data);
	if(index == NULL){
		HeapNode *heap_node = malloc(sizeof(HeapNode));
		heap_node->data = data;
		heap_node->priority = priority;

		heap_type *aux = malloc(sizeof(int));
		*(int*)aux = heap->size;
		hash_table_set(heap->h, data, aux);

		heap->nodes[heap->size++] = heap_node;
		data = NULL;
	}else{
		if(priority < heap->nodes[(*index)]->priority)
			heap->nodes[*(index)]->priority = priority;
	}

	int i;
	for(i = heap->size / 2 - 1; i >= 0; i--)
		heap_heapify_up(heap, i);

	return data;
}

void heap_heapify_up(Heap *heap, int parent){
	if(heap->size == 1){
		printf("Single element in the heap!");
		return;
	} //heap empty tambem?

	int left_child = 2 * parent + 1;
	int right_child = 2 * parent + 2;
	int new_parent = parent;

	if(left_child < heap->size){
		if(heap->nodes[left_child]->priority < heap->nodes[parent]->priority)
			new_parent = left_child;
	}

	if(right_child < heap->size){
		if(heap->nodes[right_child]->priority < heap->nodes[parent]->priority)
			new_parent = right_child;
	}

	if(new_parent != parent){
//		HeapNode *temp = heap->nodes[parent];
//		heap->nodes[parent] = heap->nodes[new_parent];
//		heap->nodes[new_parent] = temp;
//		heap_heapify_up(heap, parent);

		HeapNode *temp = heap->nodes[parent];
		heap->nodes[parent] = heap->nodes[new_parent];

		int* parent_index = malloc(sizeof(int));
		*parent_index = parent;

		heap_type store = hash_table_set(heap->h, heap->nodes[parent]->data, parent_index);
		//free(store); //AQUI O Q EU FACO?

		heap->nodes[new_parent] = temp;

		int* new_parent_index = malloc(sizeof(int));
		*new_parent_index = new_parent;

		store = hash_table_set(heap->h, heap->nodes[new_parent]->data, new_parent_index);
		//free(store);

		heap_heapify_up(heap, parent);
	}
}

int heap_empty(Heap *heap){
	return !heap->size;
}

void* heap_min(Heap *heap){
	return heap->size ? heap->nodes[0]->data : NULL;
}

double heap_min_priority(Heap *heap){
	return heap->nodes[0] != NULL ? heap->nodes[0]->priority : 0;
}

void *heap_pop(Heap *heap){
	if(!heap->size)
		exit(printf("the heap is empty (heap_pop)"));

	heap_type index = hash_table_pop(heap->h, heap->nodes[0]->data);
	free(index);

	heap_type store = heap->nodes[0]->data;
	HeapNode *aux = heap->nodes[0];
	free(aux);
	heap->nodes[0] = NULL;

	heap->nodes[0] = heap->nodes[--heap->size];
	heap->nodes[heap->size] = NULL;

	int i;
	for(i = heap->size / 2 - 1; i >= 0; i--)
		heap_heapify_up(heap, i);

	return store;
}

void heap_destroy(Heap *heap){

	int i;
	for(i = 0; i < heap->size; i++){
		free(heap->nodes[i]);
	}

	free(heap->nodes);
	hash_table_destroy(heap->h);
	free(heap);
}
