#ifndef SIMPLELIB_SIMPLE_HASH_SET_H
#define SIMPLELIB_SIMPLE_HASH_SET_H

#define __HSET_T int

typedef struct simple_hset_t simple_hset_t;

simple_hset_t * hset_create();

void hset_free(simple_hset_t* hset);

/**
 * @param hset
 * @return the number of elements contained in the set
 */
int hset_get_size(simple_hset_t* hset);

/**
 * @param hset
 * @return 1 if the set is empty or 0 if is not
 */
int hset_is_empty(simple_hset_t* hset);

/**
 * @param hset
 * @param e elem to test
 * @return 1 if the elem exist in the set or 0 if the elem does not exist in the set
 */
int hset_contains(simple_hset_t * hset, __HSET_T e);

/**
 * 
 * @param hset
 * @param e elem to store
 * @return 1 if the elem is new or 0 if the elem was already in the set
 */
int hset_add(simple_hset_t * hset, __HSET_T e);

/**
 * 
 * @param hset
 * @param e elem to remove
 * @return 1 if the elem was removed or 0 if the elem does not exist in the set
 */
int hset_remove(simple_hset_t * hset, __HSET_T e);

#endif /* SIMPLELIB_SIMPLE_HASH_SET_H */