#ifndef SIMPLELIB_SIMPLE_LINKED_LIST
#define SIMPLELIB_SIMPLE_LINKED_LIST

#define __DLIST_T int

typedef struct simple_dlist_iterator_t simple_dlist_iterator_t;

typedef struct simple_dlist_t simple_dlist_t;

simple_dlist_t* dlist_create();

void dlist_free(simple_dlist_t* list);

/**
 * @param list
 * @return the number of elements contained in the list
 */
int dlist_get_size(simple_dlist_t* list);

/**
 * @param list
 * @return 1 if the list is empty or 0 if is not
 */
int dlist_is_empty(simple_dlist_t* list);

/**
 * @param list
 * @return the first element of the list
 */
__DLIST_T* dlist_first(simple_dlist_t* list);

/**
 * @param list
 * @return the last element of the list
 */
__DLIST_T* dlist_last(simple_dlist_t* list);

/**
 * @param list
 * @param idx the index starting from 0
 * @return the element at the selected index or NULL if there is no such element
 */
__DLIST_T* dlist_at(simple_dlist_t* list, int idx);

/**
 * Add an element at the end of the list
 * @param list
 * @param e the element to add
 */
void dlist_add(simple_dlist_t* list, __DLIST_T e);

/**
 * Remove an element in a specific position in the list
 * @param list
 * @param idx the index starting from 0
 */
void dlist_remove(simple_dlist_t* list, int idx);

/**
 * @param list
 * @param forward iteration if 1 or backward if 0
 * @return the iterator to ciclye throught the elements of the list
 */
simple_dlist_iterator_t* dlist_get_iterator(simple_dlist_t* list, int forward);

void dlist_free_iterator(simple_dlist_iterator_t* iterator);

/**
 * @param iterator
 * @return the next element in the iterator or NULL if no such element exists
 */
__DLIST_T* dlist_next(simple_dlist_iterator_t* iterator);

#endif /* SIMPLELIB_SIMPLE_LINKED_LIST */