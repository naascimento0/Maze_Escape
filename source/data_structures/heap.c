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
	HeapNode *nodes;
	int capacity;
};

Heap *heap_construct(HashTable *h){
	Heap *heap = malloc(sizeof(Heap));
	heap->h = h;
	heap->size = 0;
	heap->capacity = INITIAL_CAPACITY;
	heap->nodes = calloc(INITIAL_CAPACITY, sizeof(HeapNode));
	return heap;
}

void heap_push(Heap *heap, void *data, double priority){
	if(heap->size >= heap->capacity){
		heap->capacity *= 2;
		heap->nodes = realloc(heap->nodes, heap->capacity * sizeof(HeapNode));
	}

	HeapNode *heap_node = malloc(sizeof(HeapNode));
	heap_node->data = data;
	heap_node->priority = priority;
	heap->nodes[heap->size++] = heap_node;

	int i;
	for(i = (heap->size / 2) - 1; i >= 0; i--){
		heap_heapify(heap);
	}
}

int heap_empty(Heap *heap){
	return !heap->size;
}

void* heap_max(Heap *heap){
	if(heap->size)
		return heap->nodes[0].data;
	else
		return NULL;
}

double heap_max_priority(Heap *heap){

}

void *heap_pop(Heap *heap){

}

void heap_destroy(Heap *heap){

}
