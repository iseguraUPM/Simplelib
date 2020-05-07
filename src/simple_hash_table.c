#include "../include/simplelib/simple_hash_table.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include "../include/simplelib/simple_linked_list.h"

#define HTABLE_PRIME 163

#define HTABLE_INITIAL_SIZE 53

#define HTABLE_HI_LOAD 70
#define HTABLE_LO_LOAD 10

typedef struct htable_elem
{
    char* _key;
    _HTABLE_T _value;
    // Chain for collisions
    struct htable_elem* _next;
} htable_elem_t;

typedef struct simple_htable
{
    int _base_size;
    int _size;
    int _count;
    htable_elem_t **_elems;
} simple_htable_t;

/**
 * Return whether x is prime or not
 * @param x number to test
 * @returns 1 if prime, 0 if not prive, -1 if x < 2
 */
static int is_prime(const int x) {
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if ((x % 2) == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * @return the next prime after x or x if is prime
 */
static int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}

static simple_htable_t *  create_sized_htable(const int base_size) {
    simple_htable_t* new_htable = malloc(sizeof(simple_htable_t));
    new_htable->_base_size = base_size;

    new_htable->_size = next_prime(new_htable->_base_size);

    new_htable->_count = 0;
    new_htable->_elems = calloc((size_t) new_htable->_size, sizeof(htable_elem_t*));
    return new_htable;
}

simple_htable_t * create_htable()
{
    return create_sized_htable(HTABLE_INITIAL_SIZE);
}

static void free_htable_elem(htable_elem_t* e)
{
    free(e->_key);
    free(e);
}

void free_htable(simple_htable_t * htable)
{
    for (int i = 0; i < htable->_size; i++)
    {
        htable_elem_t* elem = htable->_elems[i];
        if (elem != NULL)
            free_htable_elem(elem);
    }

    free(htable->_elems);
    free(htable);
}

/**
 * @param s the string to hash
 * @param a prime number larger than the range of characters from s
 * @param m the size of the hash table
 * @return the hash code
 */
static int htable_hash(const char* s, const int m)
{
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++)
    {
        hash += (long) pow(HTABLE_PRIME, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }

    return (int) hash;
}

static htable_elem_t* create_htable_elem(const char* key, _HTABLE_T value)
{
    htable_elem_t* new_elem = (htable_elem_t*) malloc(sizeof(htable_elem_t));
    new_elem->_key = key;
    new_elem->_value = value;
    new_elem->_next = NULL;

    return new_elem;
}

static void resize_htable(simple_htable_t* htable, const int base_size) {
    if (base_size < HTABLE_INITIAL_SIZE) {
        return;
    }

    simple_htable_t* new_htable = create_sized_htable(base_size);
    for (int i = 0; i < htable->_size; i++) {
        htable_elem_t* elem = htable->_elems[i];
        while (elem != NULL) {
            char * key = (char *) malloc(sizeof(char) * strlen(elem->_key));
            strcpy(key, elem->_key);
            insert_htable(new_htable, key, elem->_value);
            elem = elem->_next;
        }
    }

    htable->_base_size = new_htable->_base_size;
    htable->_count = new_htable->_count;

    const int tmp_size = htable->_size;
    htable->_size = new_htable->_size;
    new_htable->_size = tmp_size;

    htable_elem_t** tmp_elems = htable->_elems;
    htable->_elems = new_htable->_elems;
    new_htable->_elems = tmp_elems;

    free_htable(new_htable);
}

static void resize_htable_up(simple_htable_t* htable) {
    const int new_size = htable->_base_size * 2;
    resize_htable(htable, new_size);
}


static void resize_htable_down(simple_htable_t* htable)  {
    const int new_size = htable->_base_size / 2;
    resize_htable(htable, new_size);
}

int insert_htable(simple_htable_t* htable, const char* key, _HTABLE_T value)
{
    const int load = htable->_count * 100 / htable->_size;
    if (load > 70)
        resize_htable_up(htable);

    htable_elem_t* new_elem = create_htable_elem(key, value);

    int index = htable_hash(new_elem->_key, htable->_size);
    htable_elem_t* prev_elem = NULL;
    htable_elem_t* found_elem = htable->_elems[index];
    while (found_elem != NULL)
    {
        if (strcmp(found_elem->_key, key) == 0)
        {
            new_elem->_next = found_elem->_next;
            free_htable_elem(found_elem);
            if (prev_elem == NULL)
                htable->_elems[index] = new_elem;
            else
                prev_elem->_next = new_elem;
            return 0;
        }

        prev_elem = found_elem;
        found_elem = found_elem->_next;
    }

    if (prev_elem == NULL)
        htable->_elems[index] = new_elem;
    else
        prev_elem->_next = new_elem;
    
    htable->_count++;
    return 1;
}

_HTABLE_T * find_htable(simple_htable_t* htable, const char* key)
{
    int index = htable_hash(key, htable->_size);
    htable_elem_t* found_elem = htable->_elems[index];
    while (found_elem != NULL)
    {
        if (strcmp(found_elem->_key, key) == 0)
            return &found_elem->_value;

        found_elem = found_elem->_next;
    }
    
    return NULL;
}

int remove_htable(simple_htable_t* htable, const char* key)
{
    const int load = htable->_count * 100 / htable->_size;
    if (load < 10)
        resize_htable_down(htable);

    int index = htable_hash(key, htable->_size);
    htable_elem_t* prev_elem = NULL;
    htable_elem_t* found_elem = htable->_elems[index];
    while (found_elem != NULL)
    {
        if (strcmp(found_elem->_key, key) == 0)
        {
            if (prev_elem == NULL)
                htable->_elems[index] = NULL;
            else
                prev_elem->_next = found_elem->_next;

            free_htable_elem(found_elem);
            htable->_count--;
            return 1;
        }
            
        prev_elem = found_elem;
        found_elem = found_elem->_next;
    }

    return 0;
}