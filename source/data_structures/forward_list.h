#ifndef FORWARD_LIST_H_
#define FORWARD_LIST_H_
#include "node.h"

typedef struct{
    Node *head;
    Node *last;
    int size;
}ForwardList;

ForwardList* forward_list_construct();

int forward_list_size(ForwardList *l);

data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key));

void forward_list_push_front(ForwardList *l, data_type data);

void forward_list_push_back(ForwardList *l, data_type data);

void forward_list_print(ForwardList *l, void (*print_fn)(data_type));

data_type forward_list_get(ForwardList *l, int i);

data_type forward_list_pop_front(ForwardList *l);

ForwardList* forward_list_reverse(ForwardList *l);

void forward_list_clear(ForwardList *l);

void forward_list_remove(ForwardList *l, data_type val);

void forward_list_destroy(ForwardList *l);


#endif
