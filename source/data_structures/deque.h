#ifndef DEQUE_H_
#define DEQUE_H_
#define BLOCK_SIZE 3
#define INITIAL_BLOCK_COUNT 5

typedef void* deque_type;

typedef struct deque Deque;

Deque *deque_construct();

void deque_push_back(Deque *d, void *value);

void deque_push_front(Deque *d, void *value);

void deque_data_move(Deque *d);

void* deque_pop_back(Deque *d);

void* deque_pop_front(Deque *d);

int deque_size(Deque *d);

void* deque_get(Deque *d, int idx);

void deque_destroy(Deque *d);


#endif
