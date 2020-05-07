#include "../include/simplelib/simple_hash_set.h"

#include <stdlib.h>

#include "../include/simplelib/simple_hash_table.h"

typedef struct simple_hset
{
    int _size;
    simple_htable_t * _htable;
} simple_hset_t;

simple_hset_t * create_hset()
{
    simple_hset_t* new_hset = (simple_hset_t*) malloc(sizeof(simple_hset_t));

    new_hset->_size = 0;
    new_hset->_htable = create_htable();

    return new_hset;
}

void free_hset(simple_hset_t* hset)
{
    free_htable(hset->_htable);
    free(hset);
}

int get_hset_size(simple_hset_t* hset)
{
    return hset->_size;
}

int is_hset_empty(simple_hset_t* hset)
{
    return hset->_size == 0;
}

static char * generate_key(_HSET_T e)
{
    char * key = (char*) malloc(sizeof(char) * 10);

    sprintf(key, "%d", e);

    return key;
}

int hset_contains(simple_hset_t * hset, _HSET_T e)
{
    char * key = generate_key(e);
    int found = find_htable(hset->_htable, key) != NULL;

    free(key);
    return found;
}

int add_hset(simple_hset_t * hset, _HSET_T e)
{
    char * key = generate_key(e);
    if (insert_htable(hset->_htable, key, e))
        hset->_size++;
}

int remove_hset(simple_hset_t * hset, _HSET_T e)
{
    char * key = generate_key(e);
    if (remove_htable(hset->_htable, key))
    {
        hset->_size--;
        free(key);
        return 1;
    }

    free(key);
    return 0;
}
