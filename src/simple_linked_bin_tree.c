#include "../include/simplelib/simple_linked_bin_tree.h"

#include <stdlib.h>
#include <time.h>

int once = 1;

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

simple_dbin_tree_t* dbin_tree_create()
{
    if (once)
    {
        srand( (unsigned) time(NULL));
        once = 0;
    }
    
    simple_dbin_tree_t* new_btree = (simple_dbin_tree_t*) malloc(sizeof(simple_dbin_tree_t));
    new_btree->_root = NULL;
    new_btree->_size = 0;
    return new_btree;
}

static void free_leafs(dbin_tree_leaf_t* leaf)
{
    if (leaf != NULL)
    {
        free_leafs(leaf->_left);
        free_leafs(leaf->_right);
        free(leaf);
    }
}

void dbin_tree_free(simple_dbin_tree_t *btree)
{
    if (btree != NULL)
    {
        free_leafs(btree->_root);
        free(btree);
    }
}

int dbin_tree_get_size(simple_dbin_tree_t *btree)
{
    return btree->_size;
}

int dbin_tree_is_empty(simple_dbin_tree_t *btree)
{
    return btree->_root == NULL;
}

static dbin_tree_leaf_t* create_leaf()
{
    dbin_tree_leaf_t* new_leaf = (dbin_tree_leaf_t*) malloc(sizeof(dbin_tree_leaf_t));
    new_leaf->_left = NULL;
    new_leaf->_right = NULL;

    return new_leaf;
}

/**
 * Find the leaf matching the key
 * @param root of the search
 * @param key to look for
 * @return the leaf or the last leaf searched
 */
static dbin_tree_leaf_t* find_leaf(dbin_tree_leaf_t* root, int key)
{
    if (root->_key == key)
        return root;

    if (root->_left != NULL && root->_key > key)
    {
        return find_leaf(root->_left, key);
    }
    else if (root->_right != NULL && root->_key < key)
    {
        return find_leaf(root->_right, key);
    }
    else
    {
        return root;
    }
}

int dbin_tree_put(simple_dbin_tree_t* btree, int key, __DBTREE_T value)
{
    if (dbin_tree_is_empty(btree))
    {
        dbin_tree_leaf_t* new_leaf = create_leaf();
        new_leaf->_key = key;
        new_leaf->_value = value;
        btree->_root = new_leaf;
        btree->_size++;
        return 1;
    }

    dbin_tree_leaf_t* found_leaf = find_leaf(btree->_root, key);
    if (found_leaf->_key == key)
    {
        return 0;
    }
    else if (found_leaf->_key > key)
    {
        dbin_tree_leaf_t* new_leaf = create_leaf();
        new_leaf->_key = key;
        new_leaf->_value = value;
        found_leaf->_left = new_leaf;
        btree->_size++;
        return 1;
    }
    else // if (found_leaf->_key < key)
    {
        dbin_tree_leaf_t* new_leaf = create_leaf();
        new_leaf->_key = key;
        new_leaf->_value = value;
        found_leaf->_right = new_leaf;
        btree->_size++;
        return 1;
    }
}

__DBTREE_T* dbin_tree_find(simple_dbin_tree_t* btree, int key)
{
    if (dbin_tree_is_empty(btree))
        return NULL;

    dbin_tree_leaf_t* found_leaf = find_leaf(btree->_root, key);
    if (found_leaf->_key != key)
        return NULL;

    return &found_leaf->_value;
}

/**
 * Find the closest leaf root to the key. This indicates the leaf parent of the key or
 * where this key would be placed if it existed.
 * @param root of the search
 * @param key to look for
 * @return the closest leaf root
 */
static dbin_tree_leaf_t* find_closest_parent(dbin_tree_leaf_t* root, int key)
{
    if ((root->_left != NULL && root->_left->_key == key)
     || (root->_right != NULL && root->_right->_key == key))
        return root;

    if (root->_left != NULL && root->_key > key)
    {
        return find_closest_parent(root->_left, key);
    }
    else if (root->_right != NULL && root->_key < key)
    {
        return find_closest_parent(root->_right, key);
    }
    else
    {
        return root;
    }
}

/**
 * Chooses a random leaf (left or right) and makes it the new subtree root from all the subsequent leafs.
 * The former root no longer has leafs.
 * @param root on which its leafs will be promoted.
 * @return the promoted leaf or NULL if the root has no leafs
 **/
static dbin_tree_leaf_t* promote_leaf(dbin_tree_leaf_t* root)
{
    // NOTE: can return NULL
    if (root->_left == NULL)
        return root->_right;
    else if (root->_right == NULL)
        return root->_left;

    int choice = rand() > RAND_MAX / 2;
    if (choice)
    {
        dbin_tree_leaf_t* new_root = root->_left;

        // look for the greatest key leaf
        dbin_tree_leaf_t* max_root = find_closest_parent(new_root, root->_right->_key);
        max_root->_right = root->_right;

        root->_right = NULL;
        root->_left = NULL;
        return new_root;
    }
    else
    {
        dbin_tree_leaf_t* new_root = root->_right;

        // look for the least key leaf
        dbin_tree_leaf_t* min_root = find_closest_parent(new_root, root->_left->_key);
        min_root->_left = root->_left;

        root->_right = NULL;
        root->_left = NULL;
        return new_root;
    }
}

int dbin_tree_remove(simple_dbin_tree_t* btree, int key)
{
    if (dbin_tree_is_empty(btree))
        return 0;

    if (btree->_root->_key == key)
    {
        dbin_tree_leaf_t* new_root = promote_leaf(btree->_root);
        free(btree->_root);
        btree->_root = new_root;
        btree->_size--;
        return 1;
    }

    dbin_tree_leaf_t* found_root = find_closest_parent(btree->_root, key);
    if (found_root->_left != NULL && found_root->_left->_key == key)
    {
        dbin_tree_leaf_t* new_root = promote_leaf(found_root->_left);
        free(found_root->_left);
        found_root->_left = new_root;
        btree->_size--;
        return 1;
    }
    else if (found_root->_right != NULL && found_root->_right->_key == key)
    {
        dbin_tree_leaf_t* new_root = promote_leaf(found_root->_right);
        free(found_root->_right);
        found_root->_right = new_root;
        btree->_size--;
        return 1;
    }
    
    return 0;
}