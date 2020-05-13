#ifndef SIMPLELIB_TRANSFORM_H
#define SIMPLELIB_TRANSFORM_H

#include "simple_linked_bin_tree.h"
#include "simple_bin_tree.h"
#include "simple_linked_list.h"

/**
 * 
 * @param tree
 * @return the linked list with the binary tree elements in ascending order
 */
simple_dlist_t* dbin_tree_to_sorted_list(simple_dbin_tree_t* tree);


/**
 * 
 * @param tree
 * @return the linked list with the binary tree elements in ascending order
 */
simple_dlist_t* bin_tree_to_sorted_list(simple_bin_tree_t* tree);

#endif /* SIMPLELIB_TRANSFORM_H */