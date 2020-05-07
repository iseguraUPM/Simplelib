#ifndef SIMPLELIB_SIMPLE_HASH_TABLE_H
#define SIMPLELIB_SIMPLE_HASH_TABLE_H

#define _HTABLE_T int

typedef struct simple_htable simple_htable_t;

simple_htable_t * create_htable();

void free_htable(simple_htable_t * htable);

/**
 * 
 * @param htable
 * @param key associated with the value
 * @param value to store
 * @return 1 if the key is new or 0 if the key replaced an existing value
 */
int insert_htable(simple_htable_t* htable, const char* key, _HTABLE_T value);

/**
 * @param htable
 * @param key to find the associated element
 * @return the element corresponding to the key or NULL if key does not exists
 */
_HTABLE_T * find_htable(simple_htable_t* htable, const char* key);

/**
 * @param htable
 * @param key to delete the associated value
 * @return 1 if the key was deleted or 0 if the key did not exist
 */
int remove_htable(simple_htable_t* htable, const char* key);

#endif // ! SIMPLELIB_SIMPLE_HASH_TABLE_H