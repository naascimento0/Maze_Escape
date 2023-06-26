#ifndef HASH_H_
#define HASH_H_
#include "forward_list.h"

typedef struct HashTable HashTable;

typedef int (*HashFunction)(HashTable*, void*);
typedef int (*CmpFunction)(void *k1, void *k2);

typedef struct{
	void *key;
	void *value;
}HashTableItem;

//hashtable iterator

HashTable* hash_table_construct(int table_size, HashFunction hash_fun, CmpFunction cmp_fun);

void* hash_table_set(HashTable *h, void *key, void *val);

void* hash_table_get(HashTable *h, void *key);

void* hash_table_pop(HashTable *h, void *key);

int hash_table_size(HashTable *h);

int hash_table_num_elems(HashTable *h);

void hash_table_destroy(HashTable *h);

#endif
