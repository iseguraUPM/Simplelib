#ifndef SIMPLELIB_SIMPLE_BIN_TREE
#define SIMPLELIB_SIMPLE__BIN_TREE

#define __BTREE_T int

typedef struct simple_bin_tree_t simple_bin_tree_t;

simple_bin_tree_t* bin_tree_create();

void bin_tree_free(simple_bin_tree_t *tree);

/**
 * @param tree
 * @return the number of elements contained in the tree
 */
int bin_tree_get_size(simple_bin_tree_t *tree);

/**
 * @param tree
 * @return 1 if the tree is empty or 0 if is not
 */
int bin_tree_is_empty(simple_bin_tree_t *tree);

/**
 * @param tree
 * @param key associated with the value
 * @param value to store in the tree
 * @return 1 if the element was placed or 0 if the key already exists
 */
int bin_tree_put(simple_bin_tree_t* tree, int key, __BTREE_T value);

/**
 * @param tree
 * @param key to look for
 * @return the key associated value or NULL if the key does not exist
 */
__BTREE_T* bin_tree_find(simple_bin_tree_t* tree, int key);

/**
 * @param tree
 * @param key associated with a value
 * @return 1 if the key and value were removed or 0 if the key does not exist
 */ 
int bin_tree_remove(simple_bin_tree_t* tree, int key);

#endif