#ifndef NODE_H_
#define NODE_H_

typedef void *data_type;
typedef struct node Node;

Node* node_construct(data_type value, Node *next);
void node_destroy(Node *n);

#endif