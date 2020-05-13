#include "../include/simplelib/simple_bin_tree.h"

#include <stdlib.h>

#define BTREE_INITIAL_SIZE 64

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

static simple_bin_tree_t* create_sized_tree(int size)
{
    simple_bin_tree_t* new_tree = (simple_bin_tree_t*) malloc(sizeof(simple_bin_tree_t));
    new_tree->_size = size;
    new_tree->_count = 0;
    new_tree->_elems = calloc((size_t) size, sizeof(bin_tree_leaf_t*));

    return new_tree;
}

simple_bin_tree_t* bin_tree_create()
{
    return create_sized_tree(BTREE_INITIAL_SIZE);
}

static void free_leaf(bin_tree_leaf_t* leaf)
{
    free(leaf);
}

void bin_tree_free(simple_bin_tree_t *tree)
{
    for (int i = 0; i < tree->_size; i++)
    {
        bin_tree_leaf_t* leaf = tree->_elems[i];
        if (leaf != NULL)
            free_leaf(leaf);
    }
}

int bin_tree_get_size(simple_bin_tree_t *tree)
{
    return tree->_count;
}

int bin_tree_is_empty(simple_bin_tree_t *tree)
{
    return tree->_count == 0;
}

static bin_tree_leaf_t* create_leaf(int key, __BTREE_T value)
{
    bin_tree_leaf_t* new_leaf = (bin_tree_leaf_t*) malloc(sizeof(bin_tree_leaf_t));
    new_leaf->_key = key;
    new_leaf->_value = value;
    new_leaf->_dirty = 0;
}

static void resize_up(simple_bin_tree_t* tree)
{
    int new_size = tree->_size * 2;

    simple_bin_tree_t* temp_tree = create_sized_tree(new_size);
    for (int i = 0; i < tree->_size; i++)
    {
        bin_tree_leaf_t* leaf = tree->_elems[i];
        if (leaf != NULL && !leaf->_dirty)
            bin_tree_put(temp_tree, leaf->_key, leaf->_value);
    }

    bin_tree_leaf_t** new_elems = temp_tree->_elems;
    temp_tree->_elems = tree->_elems;
    temp_tree->_size = tree->_size;

    tree->_elems = new_elems;
    tree->_size = new_size;

    bin_tree_free(temp_tree);
}

int bin_tree_put(simple_bin_tree_t* tree, int key, __BTREE_T value)
{
    int leaf_idx = 0;
    while (leaf_idx < tree->_size)
    {
        bin_tree_leaf_t* leaf = tree->_elems[leaf_idx];
        if (leaf == NULL)
        {
            tree->_elems[leaf_idx] = create_leaf(key, value);
            tree->_count++;
            return 1;
        }

        if (leaf->_key > key)
            leaf_idx = 2 * leaf_idx + 1;
        else if (leaf->_key < key)
            leaf_idx = 2 * leaf_idx + 2;
        else if (leaf->_dirty) // leaf->_key == key
        {
            leaf->_value = value;
            leaf->_dirty = 0;
            tree->_count++;
            return 1;
        }
        else
            return 0;
    }

    do
    {
        resize_up(tree);
    } while(leaf_idx >= tree->_size);

    tree->_elems[leaf_idx] = create_leaf(key, value);
    tree->_count++;
    return 1;
}

/**
 * @param tree
 * @param key to look for
 * @return the key associated value or NULL if the key does not exist
 */
__BTREE_T* bin_tree_find(simple_bin_tree_t* tree, int key)
{
    int leaf_idx = 0;
    while (leaf_idx < tree->_size)
    {
        bin_tree_leaf_t* leaf = tree->_elems[leaf_idx];
        if (leaf == NULL)
            return NULL;
        

        if (leaf->_key > key)
            leaf_idx = 2 * leaf_idx + 1;
        else if (leaf->_key < key)
            leaf_idx = 2 * leaf_idx + 2;
        else if (leaf->_dirty) // leaf->_key == key
            return NULL;
        else
            return &leaf->_value;
    }

    return NULL;
}

/**
 * @param tree
 * @param key associated with a value
 * @return 1 if the key and value were removed or 0 if the key does not exist
 */ 
int bin_tree_remove(simple_bin_tree_t* tree, int key)
{
    int leaf_idx = 0;
    while (leaf_idx < tree->_size)
    {
        bin_tree_leaf_t* leaf = tree->_elems[leaf_idx];
        if (leaf == NULL)
            return 0;

        if (leaf->_key > key)
            leaf_idx = 2 * leaf_idx + 1;
        else if (leaf->_key < key)
            leaf_idx = 2 * leaf_idx + 2;
        else if (leaf->_dirty)
            return 0;
        else
        {
            leaf->_dirty = 1;
            tree->_count--;
            return 1;
        }
    }

    return 0;
}