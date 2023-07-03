#ifndef HEAP_H_
#define HEAP_H_
#include "hash.h"
#define INITIAL_CAPACITY 10

typedef void* heap_type;

typedef struct HeapNode HeapNode;

typedef struct Heap Heap;

Heap *heap_construct(HashTable *h);

void* heap_push(Heap *heap, void *data, double priority);

void heap_heapify_up(Heap *heap, int parent);

int heap_empty(Heap *heap);

void *heap_min(Heap *heap);

double heap_min_priority(Heap *heap);

void *heap_pop(Heap *heap);

void heap_destroy(Heap *heap);

#endif
