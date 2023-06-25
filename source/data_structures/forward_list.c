#include <stdlib.h>
#include <stdio.h>
#include "forward_list.h"

struct forward{
    Node *head;
    Node *last;
    int size;
};

ForwardList* forward_list_construct(){
    ForwardList *l = malloc(sizeof(ForwardList));
    l->head = l->last = NULL;
    l->size = 0;
    return l;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key)){
    
}

