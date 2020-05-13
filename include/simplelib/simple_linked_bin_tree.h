#ifndef SIMPLELIB_SIMPLE_LINKED_BIN_TREE_H
#define SIMPLELIB_SIMPLE_LINKED_BIN_TREE_H

#define __DBTREE_T int

typedef struct simple_dbin_tree_t simple_dbin_tree_t;

simple_dbin_tree_t* dbin_tree_create();

void dbin_tree_free(simple_dbin_tree_t *tree);

/**
 * @param tree
 * @return the number of elements contained in the tree
 */
int dbin_tree_get_size(simple_dbin_tree_t *tree);

/**
 * @param tree
 * @return 1 if the tree is empty or 0 if is not
 */
int dbin_tree_is_empty(simple_dbin_tree_t *tree);

/**
 * @param tree
 * @param key associated with the value
 * @param value to store in the tree
 * @return 1 if the element was placed or 0 if the key already exists
 */
int dbin_tree_put(simple_dbin_tree_t* tree, int key, __DBTREE_T value);

/**
 * @param tree
 * @param key to look for
 * @return the key associated value or NULL if the key does not exist
 */
__DBTREE_T* dbin_tree_find(simple_dbin_tree_t* tree, int key);

/**
 * @param tree
 * @param key associated with a value
 * @return 1 if the key and value were removed or 0 if the key does not exist
 */ 
int dbin_tree_remove(simple_dbin_tree_t* tree, int key);

#endif /* SIMPLELIB_SIMPLE_LINKED_BIN_TREE_H */