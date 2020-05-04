#ifndef SIMPLELIB_SIMPLE_BTREE
#define SIMPLELIB_SIMPLE_BTREE

#define __BTREE_T int

typedef struct simple_btree simple_btree_t;

simple_btree_t* create_btree();

void free_btree(simple_btree_t *btree);

int get_btree_size(simple_btree_t *btree);

int is_btree_empty(simple_btree_t *btree);

int add_btree(simple_btree_t* btree, int key, __BTREE_T e);

__BTREE_T* find_btree(simple_btree_t* btree, int key);

int remove_btree(simple_btree_t* btree, int key);

#endif