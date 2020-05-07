#include "../include/simplelib/simple_bin_tree.h"

#include <stdlib.h>
#include <time.h>

int once = 1;

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

simple_bin_tree_t* bin_tree_create()
{
    if (once)
    {
        srand( (unsigned) time(NULL));
        once = 0;
    }
    
    simple_bin_tree_t* new_btree = (simple_bin_tree_t*) malloc(sizeof(simple_bin_tree_t));
    new_btree->_root = NULL;
    new_btree->_size = 0;
    return new_btree;
}

static void free_leafs(bin_tree_leaf_t* leaf)
{
    if (leaf != NULL)
    {
        free_leafs(leaf->_left);
        free_leafs(leaf->_right);
        free(leaf);
    }
}

void bin_tree_free(simple_bin_tree_t *btree)
{
    if (btree != NULL)
    {
        free_leafs(btree->_root);
        free(btree);
    }
}

int bin_tree_get_size(simple_bin_tree_t *btree)
{
    return btree->_size;
}

int bin_tree_is_empty(simple_bin_tree_t *btree)
{
    return btree->_root == NULL;
}

static bin_tree_leaf_t* create_leaf()
{
    bin_tree_leaf_t* new_leaf = (bin_tree_leaf_t*) malloc(sizeof(bin_tree_leaf_t));
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
static bin_tree_leaf_t* find_leaf(bin_tree_leaf_t* root, int key)
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

int bin_tree_put(simple_bin_tree_t* btree, int key, __BTREE_T value)
{
    if (bin_tree_is_empty(btree))
    {
        bin_tree_leaf_t* new_leaf = create_leaf();
        new_leaf->_key = key;
        new_leaf->_value = value;
        btree->_root = new_leaf;
        btree->_size++;
        return 1;
    }

    bin_tree_leaf_t* found_leaf = find_leaf(btree->_root, key);
    if (found_leaf->_key == key)
    {
        return 0;
    }
    else if (found_leaf->_key > key)
    {
        bin_tree_leaf_t* new_leaf = create_leaf();
        new_leaf->_key = key;
        new_leaf->_value = value;
        found_leaf->_left = new_leaf;
        btree->_size++;
        return 1;
    }
    else // if (found_leaf->_key < key)
    {
        bin_tree_leaf_t* new_leaf = create_leaf();
        new_leaf->_key = key;
        new_leaf->_value = value;
        found_leaf->_right = new_leaf;
        btree->_size++;
        return 1;
    }
}

__BTREE_T* bin_tree_find(simple_bin_tree_t* btree, int key)
{
    if (bin_tree_is_empty(btree))
        return NULL;

    bin_tree_leaf_t* found_leaf = find_leaf(btree->_root, key);
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
static bin_tree_leaf_t* find_closest_parent(bin_tree_leaf_t* root, int key)
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
static bin_tree_leaf_t* promote_leaf(bin_tree_leaf_t* root)
{
    // NOTE: can return NULL
    if (root->_left == NULL)
        return root->_right;
    else if (root->_right == NULL)
        return root->_left;

    int choice = rand() > RAND_MAX / 2;
    if (choice)
    {
        bin_tree_leaf_t* new_root = root->_left;

        // look for the greatest key leaf
        bin_tree_leaf_t* max_root = find_closest_parent(new_root, root->_right->_key);
        max_root->_right = root->_right;

        root->_right = NULL;
        root->_left = NULL;
        return new_root;
    }
    else
    {
        bin_tree_leaf_t* new_root = root->_right;

        // look for the least key leaf
        bin_tree_leaf_t* min_root = find_closest_parent(new_root, root->_left->_key);
        min_root->_left = root->_left;

        root->_right = NULL;
        root->_left = NULL;
        return new_root;
    }
}

int bin_tree_remove(simple_bin_tree_t* btree, int key)
{
    if (bin_tree_is_empty(btree))
        return 0;

    if (btree->_root->_key == key)
    {
        bin_tree_leaf_t* new_root = promote_leaf(btree->_root);
        free(btree->_root);
        btree->_root = new_root;
        btree->_size--;
        return 1;
    }

    bin_tree_leaf_t* found_root = find_closest_parent(btree->_root, key);
    if (found_root->_left != NULL && found_root->_left->_key == key)
    {
        bin_tree_leaf_t* new_root = promote_leaf(found_root->_left);
        free(found_root->_left);
        found_root->_left = new_root;
        btree->_size--;
        return 1;
    }
    else if (found_root->_right != NULL && found_root->_right->_key == key)
    {
        bin_tree_leaf_t* new_root = promote_leaf(found_root->_right);
        free(found_root->_right);
        found_root->_right = new_root;
        btree->_size--;
        return 1;
    }
    
    return 0;
}