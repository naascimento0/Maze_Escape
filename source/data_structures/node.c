#include <stdlib.h>
#include <stdio.h>
#include "node.h"

struct node{
    data_type value;
    struct node *next;
};

Node* node_construct(data_type value, Node *next){
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

void node_destroy(Node *n){
    free(n);
}
