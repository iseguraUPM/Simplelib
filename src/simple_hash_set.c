#include "../include/simplelib/simple_hash_set.h"

#include <stdlib.h>
#include <stdio.h>

#include "../include/simplelib/simple_hash_table.h"

typedef struct simple_hset_t
{
    int _size;
    simple_htable_t * _htable;
} simple_hset_t;

simple_hset_t * hset_create()
{
    simple_hset_t* new_hset = (simple_hset_t*) malloc(sizeof(simple_hset_t));

    new_hset->_size = 0;
    new_hset->_htable = htable_create();

    return new_hset;
}

void hset_free(simple_hset_t* hset)
{
    htable_free(hset->_htable);
    free(hset);
}

int hset_get_size(simple_hset_t* hset)
{
    return hset->_size;
}

int hset_is_empty(simple_hset_t* hset)
{
    return hset->_size == 0;
}

static char * generate_key(__HSET_T e)
{
    char * key = (char*) malloc(sizeof(char) * 10);

    sprintf(key, "%d", e);

    return key;
}

int hset_contains(simple_hset_t * hset, __HSET_T e)
{
    char * key = generate_key(e);
    int found = htable_find(hset->_htable, key) != NULL;

    free(key);
    return found;
}

int hset_add(simple_hset_t * hset, __HSET_T e)
{
    char * key = generate_key(e);
    if (htable_insert(hset->_htable, key, e))
        hset->_size++;
}

int hset_remove(simple_hset_t * hset, __HSET_T e)
{
    char * key = generate_key(e);
    if (htable_remove(hset->_htable, key))
    {
        hset->_size--;
        free(key);
        return 1;
    }

    free(key);
    return 0;
}
