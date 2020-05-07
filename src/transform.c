#include "../include/simplelib/transform.h"

#include <stdlib.h>

#include "../include/simplelib/simple_bin_tree.h"
#include "../include/simplelib/simple_linked_list.h"

typedef struct btree_leaf
{
    int _key;
    __BTREE_T _elem;
    struct btree_leaf* _left;
    struct btree_leaf* _right;
} btree_leaf_t;

typedef struct simple_btree
{   
    int _size;
    btree_leaf_t* _root;
} simple_btree_t;

static void deep_add_leafs(btree_leaf_t * root, simple_dlist_t * list)
{
    if (root->_left != NULL)
    {
        deep_add_leafs(root->_left, list);
        
    }
    add_dlist(list, root->_elem);
    if (root->_right != NULL)
    {
        deep_add_leafs(root->_right, list);
    }
}

simple_dlist_t* bin_tree_to_sorted_list(simple_btree_t* btree)
{
    simple_dlist_t * sorted_list = create_dlist();
    deep_add_leafs(btree->_root, sorted_list);

    return sorted_list;
}