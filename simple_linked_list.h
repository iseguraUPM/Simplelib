#ifndef SIMPLELIB_SIMPLE_LINKED_LIST
#define SIMPLELIB_SIMPLE_LINKED_LIST

#define __DLIST_T int

typedef struct simple_dlist simple_dlist_t;

simple_dlist_t* create_dlist();

void free_dlist(simple_dlist_t* list);

int get_dlist_size(simple_dlist_t* list);

int is_dlist_empty(simple_dlist_t* list);

__DLIST_T* first_dlist(simple_dlist_t* list);

__DLIST_T* last_dlist(simple_dlist_t* list);

__DLIST_T* at_dlist(simple_dlist_t* list, int idx);

void add_dlist(simple_dlist_t* list, __DLIST_T e);

void remove_dlist(simple_dlist_t* list, int idx);

#endif // SIMPLELIB_SIMPLE_LINKED_LIST