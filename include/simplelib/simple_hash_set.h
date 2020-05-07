#ifndef SIMPLELIB_SIMPLE_HASH_SET_H
#define SIMPLELIB_SIMPLE_HASH_SET_H

#define _HSET_T int

typedef struct simple_hset simple_hset_t;

simple_hset_t * create_hset();

void free_hset(simple_hset_t* hset);

int get_hset_size(simple_hset_t* hset);

int is_hset_empty(simple_hset_t* hset);

/**
 * @param hset
 * @param e elem to test
 * @return 1 if the elem exist in the set or 0 if the elem does not exist in the set
 */
int hset_contains(simple_hset_t * hset, _HSET_T e);

/**
 * 
 * @param hset
 * @param e elem to store
 * @return 1 if the elem is new or 0 if the elem was already in the set
 */
int add_hset(simple_hset_t * hset, _HSET_T e);

/**
 * 
 * @param hset
 * @param e elem to remove
 * @return 1 if the elem was removed or 0 if the elem does not exist in the set
 */
int remove_hset(simple_hset_t * hset, _HSET_T e);

#endif // !SIMPLELIB_SIMPLE_HASH_SET_H