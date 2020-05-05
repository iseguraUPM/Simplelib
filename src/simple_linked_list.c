#include "../include/simplelib/simple_linked_list.h"

#include <stdlib.h>

typedef struct dlist_elem {
    __DLIST_T _elem;
    struct dlist_elem* _next;
    struct dlist_elem* _prev;
} dlist_elem_t;

typedef struct simple_dlist {
    int _len;
    dlist_elem_t* _first;
    dlist_elem_t* _last;
} simple_dlist_t;

simple_dlist_t* create_dlist()
{
    simple_dlist_t* new_dlist = (simple_dlist_t*) malloc(sizeof(simple_dlist_t));
    new_dlist->_first = NULL;
    new_dlist->_last = NULL;
    new_dlist->_len = 0;

    return new_dlist;
}

static void free_dlist_elems(dlist_elem_t* e)
{
    if (e != NULL)
    {
        free_dlist_elems(e->_next);
        free(e);
    }
}

void free_dlist(simple_dlist_t* list)
{
    free_dlist_elems(list->_first);
    free(list);
}

int get_dlist_size(simple_dlist_t* list)
{
    return list->_len;
}

int is_dlist_empty(simple_dlist_t* list)
{
    return list->_first == NULL;
}

__DLIST_T* first_dlist(simple_dlist_t* list)
{
    if (list->_first == NULL)
        return NULL;

    return &list->_first->_elem;
}

__DLIST_T* last_dlist(simple_dlist_t* list)
{
    if (list->_last == NULL)
        return NULL;

    return &list->_last->_elem;
}

static dlist_elem_t* elem_at_dlist(simple_dlist_t* list, int idx)
{
    if (idx < 0 || idx >= list->_len)
        return NULL;

    dlist_elem_t* e = NULL;
    if (idx < list->_len - idx)
    {
        e = list->_first;
        for (int i = 0; i != idx; i++)
        {
            e = e->_next;
        }
    }
    else
    {
        e = list->_last;
        for (int i = list->_len - 1; i != idx; i--)
        {
            e = e->_prev;
        }
    }

    return e;
}

__DLIST_T* at_dlist(simple_dlist_t* list, int idx)
{
    dlist_elem_t* e = elem_at_dlist(list, idx);
    if (e == NULL)
        return NULL;

    return &e->_elem;
}

static dlist_elem_t* create_dlist_elem()
{
    dlist_elem_t* new_elem = (dlist_elem_t*) malloc(sizeof(dlist_elem_t));
    new_elem->_next = NULL;
    new_elem->_prev = NULL;
    return new_elem;
}

void add_dlist(simple_dlist_t* list, __DLIST_T e)
{
    if (is_dlist_empty(list))
    {
        list->_first = create_dlist_elem();
        list->_first->_elem = e;
        list->_last = list->_first;
    }
    else
    {
        dlist_elem_t* new_elem = create_dlist_elem();
        new_elem->_elem = e;
        new_elem->_prev = list->_last;
        list->_last->_next = new_elem;
        list->_last = new_elem;
    }

    list->_len++;
}

void remove_dlist(simple_dlist_t* list, int idx)
{
    dlist_elem_t* found_elem = elem_at_dlist(list, idx);
    if (found_elem != NULL)
    {
        if (found_elem->_prev != NULL)
            found_elem->_prev->_next = found_elem->_next;
        if (found_elem->_next != NULL)
            found_elem->_next->_prev = found_elem->_prev;
        
        free(found_elem);
    }
}