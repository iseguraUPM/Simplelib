#include "../include/simplelib/transform.h"

#include <stdlib.h>

typedef struct bin_tree_leaf_t
{
    int _key;
    __BTREE_T _value;
    struct bin_tree_leaf_t* _left;
    struct bin_tree_leaf_t* _right;
} bin_tree_leaf_t;

typedef struct simple_bin_tree_t
{   
    int _size;
    bin_tree_leaf_t* _root;
} simple_bin_tree_t;

static void deep_add_leafs(bin_tree_leaf_t * root, simple_dlist_t * list)
{
    if (root->_left != NULL)
    {
        deep_add_leafs(root->_left, list);
        
    }
    dlist_add(list, root->_value);
    if (root->_right != NULL)
    {
        deep_add_leafs(root->_right, list);
    }
}

simple_dlist_t* bin_tree_to_sorted_list(simple_bin_tree_t* tree)
{
    simple_dlist_t * sorted_list = dlist_create();
    deep_add_leafs(tree->_root, sorted_list);

    return sorted_list;
}