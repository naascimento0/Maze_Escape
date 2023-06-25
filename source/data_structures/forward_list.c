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
	if(l->head == NULL)
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
	}
}

data_type forward_list_get(ForwardList *l, int i){
	Node *aux = l->head;
	while(i--){
		aux = aux->next;
	}

	return aux->value;
}

data_type forward_list_pop_front(ForwardList *l){
	if(l->head == NULL)
		return NULL;

	Node *aux = l->head;
	data_type value = aux->value;
	node_destroy(aux);
	l->head = l->head->next;

	if(l->head == NULL)
		l->last = NULL;

	l->size--;
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
	Node *aux = l->head;
	while(aux != NULL){
		Node *temp = aux;
		aux = aux->next;
		node_destroy(temp);
		l->size--;
	}
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
	forward_list_clear(l);
	free(l);
}
