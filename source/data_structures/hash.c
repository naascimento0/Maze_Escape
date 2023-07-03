#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

struct HashTable{
    ForwardList **buckets;
    HashFunction hash_fun;
    CmpFunction cmp_fun;
    int table_size;
    int table_elements;
};

void _hash_pair_destroy(HashTableItem *p){
    free(p);
}

HashTable* hash_table_construct(int table_size, HashFunction hash_fun, CmpFunction cmp_fun){
    HashTable *hash_tbl = malloc(sizeof(HashTable));
    hash_tbl->table_size = table_size;
    hash_tbl->hash_fun = hash_fun;
    hash_tbl->cmp_fun = cmp_fun;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList*));
    hash_tbl->table_elements = 0;
    return hash_tbl;
}

void* hash_table_set(HashTable *h, void *key, void *value){
    int index = h->hash_fun(h, key);
    ForwardList *bucket = h->buckets[index];
    if(bucket == NULL){
    	bucket = forward_list_construct();
    	h->buckets[index] = bucket;
    }

    void *old_value = NULL;
    HashTableItem *new_pair = malloc(sizeof(HashTableItem));
    new_pair->key = key;
    new_pair->value = value;

    data_type found_item = forward_list_find(bucket, new_pair, h->cmp_fun);
    if(found_item == NULL){
    	forward_list_push_front(h->buckets[index], new_pair);
    	h->table_elements++;
    }else{
    	HashTableItem *aux = (HashTableItem*)found_item;
    	old_value = aux->value;
    	aux->value = value;
    	_hash_pair_destroy(new_pair);
    }

    return old_value;
}

void* hash_table_get(HashTable *h, void *key){
	int index = h->hash_fun(h, key);
	ForwardList *bucket = h->buckets[index];
	if(bucket == NULL)
		return NULL;

	data_type found_item = forward_list_find(bucket, key, h->cmp_fun);
	if(found_item == NULL)
		return NULL;
	else{
		HashTableItem *aux = (HashTableItem*)found_item;
		return aux->value;
	}
}

void* hash_table_pop(HashTable *h, void *key){
	int index = h->hash_fun(h, key);
	ForwardList *bucket = h->buckets[index];
	if(bucket == NULL)
		return NULL;

	void *pop_value = NULL;
	data_type found_item = forward_list_find(bucket, key, h->cmp_fun);
	if(found_item != NULL){
		HashTableItem *aux = (HashTableItem*)found_item;
		pop_value = aux->value;
		forward_list_remove(h->buckets[index], found_item);
		h->table_elements--;
	}

	return pop_value;
}

int hash_table_size(HashTable *h){
	return h->table_size;
}

int hash_table_num_elems(HashTable *h){
	return h->table_elements;
}

void hash_table_destroy(HashTable *h){
	int i;
	for(i = 0; i < h->table_size; i++){
		if(h->buckets[i] != NULL){
			Node *aux = h->buckets[i]->head;

			while(aux != NULL){
				_hash_pair_destroy(aux->value);
				aux = aux->next;
			}

			forward_list_destroy(h->buckets[i]);
		}
	}

	free(h->buckets);
	free(h);
}

struct HashTableIterator{
	HashTable *hashtable;
	int curr_bucket;
	Node *current_node;
	int buckets_qtt;
};

HashTableIterator *hash_table_iterator(HashTable *h){
	HashTableIterator *it = malloc(sizeof(HashTableIterator));
	it->hashtable = h;
	it->curr_bucket = 0;
	it->current_node = NULL;
	it->buckets_qtt = h->table_elements;
	return it;
}

int hash_table_iterator_is_over(HashTableIterator *it){
	return it->curr_bucket >= it->hashtable->table_size || !it->buckets_qtt;
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it){
	if(hash_table_iterator_is_over(it))
		return NULL;

	if(it->current_node == NULL){
		while((it->curr_bucket < it->hashtable->table_size) && (it->hashtable->buckets[it->curr_bucket] == NULL))
			it->curr_bucket++;

		if(it->curr_bucket < it->hashtable->table_size)
			it->current_node = it->hashtable->buckets[it->curr_bucket]->head;
	}else
		it->current_node = it->current_node->next;


	while(it->curr_bucket < it->hashtable->table_size && it->current_node == NULL){
		it->curr_bucket++;
		if((it->curr_bucket < it->hashtable->table_size) && (it->hashtable->buckets[it->curr_bucket] != NULL))
			it->current_node = it->hashtable->buckets[it->curr_bucket]->head;
	}

	it->buckets_qtt--;

	if(it->current_node == NULL)
		return NULL;

    HashTableItem *item = (HashTableItem*)it->current_node->value;
    return item;
}


void hash_table_iterator_destroy(HashTableIterator *it){
	free(it);
}

void* return_hash_item_key(HashTableItem *item){
	return item->key;
}

