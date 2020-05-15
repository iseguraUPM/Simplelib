#include "../include/simplelib/simple_bin_tree.h"

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#define BTREE_INITIAL_SIZE 64

#define BTREE_LOW_SPACE_EFFICIENCY 10

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
    new_tree->_elems = (bin_tree_leaf_t**) calloc((size_t) size, sizeof(bin_tree_leaf_t*));

    return new_tree;
}

simple_bin_tree_t* bin_tree_create()
{
    return create_sized_tree(BTREE_INITIAL_SIZE);
}

static void free_leaf(simple_bin_tree_t *tree, int leaf_idx)
{
    if (leaf_idx >= tree->_size)
        return;

    bin_tree_leaf_t* leaf = tree->_elems[leaf_idx];
    if (leaf == NULL)
        return;

    free_leaf(tree, leaf_idx * 2 + 1);
    free_leaf(tree, leaf_idx * 2 + 2);
    free(leaf);
}

void bin_tree_free(simple_bin_tree_t *tree)
{
    free_leaf(tree, 0);
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

    return new_leaf;
}

static void deep_array_copy(simple_bin_tree_t* tree, int leaf_idx, bin_tree_leaf_t** arr, int* count)
{
    if (leaf_idx >= tree->_size)
        return; 

    bin_tree_leaf_t* leaf = tree->_elems[leaf_idx];
    if (leaf == NULL)
        return;

    deep_array_copy(tree, 2 * leaf_idx + 1, arr, count);
    if (!leaf->_dirty)
    {
        arr[(*count)] = create_leaf(leaf->_key, leaf->_value);
        (*count)++;
    }
    deep_array_copy(tree, 2 * leaf_idx + 2, arr, count);
}

static bin_tree_leaf_t** copy_to_sorted_array(simple_bin_tree_t* tree)
{
    bin_tree_leaf_t** sorted_leafs = (bin_tree_leaf_t**) malloc(sizeof(bin_tree_leaf_t*) * tree->_count);
    int count = 0;
    deep_array_copy(tree, 0, sorted_leafs, &count);

    return sorted_leafs;
}

static void populate_balanced_tree(bin_tree_leaf_t** sorted_arr, simple_bin_tree_t* tree, int leaf_idx, int start, int end)
{
    if (start > end)
        return;

    if (leaf_idx >= tree->_size)
        return;

    int m = (start + end) / 2;
    bin_tree_leaf_t * leaf = sorted_arr[m];
    tree->_elems[leaf_idx] = leaf;
    tree->_count++;
    
    populate_balanced_tree(sorted_arr, tree, leaf_idx * 2 + 1, start, m - 1);
    populate_balanced_tree(sorted_arr, tree, leaf_idx * 2 + 2, m + 1, end);
}

static void rebalance_tree(simple_bin_tree_t* tree)
{
    bin_tree_leaf_t** sorted_leafs = copy_to_sorted_array(tree);

    simple_bin_tree_t* temp_tree = create_sized_tree(tree->_size);
    populate_balanced_tree(sorted_leafs, temp_tree, 0, 0, tree->_count - 1);

    bin_tree_leaf_t** new_elems = temp_tree->_elems;
    temp_tree->_elems = tree->_elems;
    temp_tree->_size = tree->_size;

    tree->_elems = new_elems;

    bin_tree_free(temp_tree);
    free(sorted_leafs);
}

static void resize_up(simple_bin_tree_t* tree)
{
    int new_size = tree->_size * 2;
    bin_tree_leaf_t** new_elems = (bin_tree_leaf_t**) calloc((size_t) new_size, sizeof(bin_tree_leaf_t*));
    memcpy(new_elems, tree->_elems, tree->_size * sizeof(bin_tree_leaf_t*));

    free(tree->_elems);

    tree->_elems = new_elems;
    tree->_size = new_size;
}

int bin_tree_put(simple_bin_tree_t* tree, int key, __BTREE_T value)
{
    int space_eff = tree->_count * 100 / tree->_size;
    if (tree->_count > 3 && space_eff < BTREE_LOW_SPACE_EFFICIENCY)
        rebalance_tree(tree);

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