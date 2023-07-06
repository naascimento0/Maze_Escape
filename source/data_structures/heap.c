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
	}

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
		int *old_parent_index = hash_table_get(heap->h, heap->nodes[parent]->data);
		int *new_parent_index = hash_table_set(heap->h, heap->nodes[new_parent]->data, old_parent_index);
		hash_table_set(heap->h, heap->nodes[parent]->data, new_parent_index);

		HeapNode *temp = heap->nodes[parent];
		heap->nodes[parent] = heap->nodes[new_parent];
		heap->nodes[new_parent] = temp;

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

	static int a = 0;
	if(a < 20){
		printf("\natual versao %d:\n", a++);
		heap_display(heap); //MODIFICADO
		printf("\n");
	}

	if(!heap->size)
		exit(printf("the heap is empty (heap_pop)"));

	heap_type index = hash_table_pop(heap->h, heap->nodes[0]->data);

	heap_type store = heap->nodes[0]->data;
	HeapNode *aux = heap->nodes[0];
	free(aux);

	heap->nodes[0] = heap->nodes[--heap->size];
	heap->nodes[heap->size] = NULL;
	if(heap->size){
		int *old_index = hash_table_set(heap->h, heap->nodes[0]->data, index);
		free(old_index);
	}
	else
		free(index);

	heap_heapify_down(heap, 0);

	if(a < 20){
		printf("versao nova\n");
		heap_display(heap); //MODIFICADO
		printf("\n");
	}

	return store;
}


void heap_heapify_down(Heap *heap, int parent){
	if(heap->size <= 1)
		return;

	int left_child = 2 * parent + 1;
	int right_child = 2 * parent + 2;
	int new_parent = parent;

	if(right_child < heap->size){
		if(heap->nodes[right_child]->priority < heap->nodes[parent]->priority)
			new_parent = right_child;
	}

	if(left_child < heap->size){
		if(heap->nodes[left_child]->priority < heap->nodes[parent]->priority){
			new_parent = new_parent != parent ? ((heap->nodes[left_child]->priority < heap->nodes[right_child]->priority) ? left_child : new_parent) : left_child;
		}
	}

	if(new_parent != parent){
		int *old_parent_index = hash_table_get(heap->h, heap->nodes[parent]->data);
		int *new_parent_index = hash_table_set(heap->h, heap->nodes[new_parent]->data, old_parent_index);
		hash_table_set(heap->h, heap->nodes[parent]->data, new_parent_index);

		HeapNode *temp = heap->nodes[parent];
		heap->nodes[parent] = heap->nodes[new_parent];
		heap->nodes[new_parent] = temp;

		heap_heapify_down(heap, new_parent);
	}
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

void heap_display(Heap *heap){
	int i;
	for(i = 0; i < heap->size; i++){
		printf("%d: %lf\n", i, heap->nodes[i]->priority);
	}
}
