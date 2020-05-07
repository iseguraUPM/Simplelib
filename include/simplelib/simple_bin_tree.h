#ifndef SIMPLELIB_SIMPLE_BIN_TREE
#define SIMPLELIB_SIMPLE__BIN_TREE

#define __BTREE_T int

typedef struct simple_bin_tree_t simple_bin_tree_t;

simple_bin_tree_t* bin_tree_create();

void bin_tree_free(simple_bin_tree_t *tree);

int bin_tree_get_size(simple_bin_tree_t *tree);

int bin_tree_is_empty(simple_bin_tree_t *tree);

int bin_tree_put(simple_bin_tree_t* tree, int key, __BTREE_T value);

__BTREE_T* bin_tree_find(simple_bin_tree_t* tree, int key);

int bin_tree_remove(simple_bin_tree_t* tree, int key);

#endif