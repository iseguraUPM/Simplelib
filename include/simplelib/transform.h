#ifndef SIMPLELIB_TRANSFORM
#define SIMPLELIB_TRANSFORM

typedef struct simple_btree simple_btree_t;
typedef struct simple_dlist simple_dlist_t;

simple_dlist_t* bin_tree_to_sorted_list(simple_btree_t* btree);

#endif