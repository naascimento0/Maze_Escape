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
	Node *aux = l->head;
	while(aux != NULL){
		if(cmp_fn(key, aux->value))
			return aux->value;
		aux = aux->next;
	}

	return NULL;
}

void forward_list_push_front(ForwardList *l, data_type data){
	Node *new = node_construct(data, l->head);
	if(l->head == NULL)
		l->head = l->last = new;
	else
		l->head = new;

	l->size++;
}

void forward_list_push_back(ForwardList *l, data_type data){
	Node *new = node_construct(data, NULL);
	if(l->last == NULL)
		l->head = l->last = new;
	else
		l->last = l->last->next = new;

	l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
	Node *aux = l->head;
	while(aux != NULL){
		print_fn(aux->value);
		aux = aux->next;
		if(aux != NULL)
			printf(", ");
	}
}

data_type forward_list_get(ForwardList *l, int i){
	if(i < 0 || i >= l->size)
		exit(printf("Error: forward_list_get(): index out of bounds."));
	
	Node *aux = l->head;
	while(i--){
		aux = aux->next;
	}

	return aux->value;
}

data_type forward_list_pop_front(ForwardList *l){
	if(l->head == NULL)
		exit(printf("Error: forward_list_pop_front(): list is empty."));

	Node *aux = l->head;
	data_type value = aux->value;
	l->head = l->head->next;
	node_destroy(aux);
	l->size--;

	if(l->head == NULL)
		l->last = NULL;

	return value;
}

ForwardList* forward_list_reverse(ForwardList *l){
	ForwardList *new = forward_list_construct();
	Node *aux = l->head;
	while(aux != NULL){
		forward_list_push_front(new, aux->value);
		aux = aux->next;
	}

	return new;
}

void forward_list_clear(ForwardList *l){
	int list_size = l->size;
	int i;
	for(i = 0; i < list_size; i++)
		forward_list_pop_front(l);
}

void forward_list_remove(ForwardList *l, data_type val){
	Node *current = l->head;
	Node *previous = NULL;
	while(current != NULL){
		if(current->value == val){
			Node *aux = current;

			if(previous != NULL){  // O nó a ser removido não é o primeiro da lista
				previous->next = current->next;
				if(current == l->last) // O nó a ser removido é o último da lista
					l->last = previous;
			}else{ // O nó a ser removido é o primeiro da lista
				l->head = current->next;
				if(current == l->last){ // A lista ficou vazia
					l->last = NULL;
				}
			}

			current = current->next;
			node_destroy(aux);
			l->size--;

		}else{
			previous = current;
			current = current->next;
		}
	}
}

void forward_list_destroy(ForwardList *l){
	Node *aux = l->head;
	while(aux != NULL){
		Node *temp = aux->next;
		node_destroy(aux);
		aux = temp;
	}
	
	free(l);
}
