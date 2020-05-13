#include "../include/simplelib/transform.h"

#include <stdlib.h>

typedef struct dbin_tree_leaf_t
{
    int _key;
    __DBTREE_T _value;
    struct dbin_tree_leaf_t* _left;
    struct dbin_tree_leaf_t* _right;
} dbin_tree_leaf_t;

typedef struct simple_dbin_tree_t
{   
    int _size;
    dbin_tree_leaf_t* _root;
} simple_dbin_tree_t;

static void deep_add_linked_leafs(dbin_tree_leaf_t * root, simple_dlist_t * list)
{
    if (root->_left != NULL)
    {
        deep_add_linked_leafs(root->_left, list);
        
    }
    dlist_add(list, root->_value);
    if (root->_right != NULL)
    {
        deep_add_linked_leafs(root->_right, list);
    }
}

simple_dlist_t* dbin_tree_to_sorted_list(simple_dbin_tree_t* tree)
{
    simple_dlist_t * sorted_list = dlist_create();
    deep_add_linked_leafs(tree->_root, sorted_list);

    return sorted_list;
}

typedef struct bin_tree_leaf_t
{
    int _key;
    __BTREE_T _value;
    int _dirty;
} bin_tree_leaf_t;


typedef struct simple_bin_tree_t
{
    int _size;
    int _count;
    bin_tree_leaf_t** _elems;
} simple_bin_tree_t;

static void deep_add_leafs(simple_bin_tree_t * tree, int leaf_idx, simple_dlist_t * list)
{
    if (leaf_idx >= tree->_size)
        return;

    bin_tree_leaf_t * leaf = tree->_elems[leaf_idx];
    if (leaf == NULL)
        return;

    deep_add_leafs(tree, 2 * leaf_idx + 1, list);
    if (!leaf->_dirty)
        dlist_add(list, leaf->_value);
    deep_add_leafs(tree, 2 * leaf_idx + 2, list);
}

simple_dlist_t* bin_tree_to_sorted_list(simple_bin_tree_t* tree)
{
    simple_dlist_t * sorted_list = dlist_create();
    deep_add_leafs(tree, 0, sorted_list);

    return sorted_list;
}