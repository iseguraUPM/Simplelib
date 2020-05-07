#include "../include/simplelib/simple_linked_list.h"

#include <stdlib.h>

typedef struct dlist_elem_t {
    __DLIST_T _elem;
    struct dlist_elem_t* _next;
    struct dlist_elem_t* _prev;
} dlist_elem_t;

typedef struct simple_dlist_t {
    int _len;
    dlist_elem_t* _first;
    dlist_elem_t* _last;
} simple_dlist_t;

typedef struct simple_dlist_iterator_t
{
    simple_dlist_t* _list;
    dlist_elem_t* _current_elem;
    int _forward;
} simple_dlist_iterator_t;

simple_dlist_t* dlist_create()
{
    simple_dlist_t* new_dlist = (simple_dlist_t*) malloc(sizeof(simple_dlist_t));
    new_dlist->_first = NULL;
    new_dlist->_last = NULL;
    new_dlist->_len = 0;

    return new_dlist;
}

static void free_elems(dlist_elem_t* e)
{
    if (e != NULL)
    {
        free_elems(e->_next);
        free(e);
    }
}

void dlist_free(simple_dlist_t* list)
{
    free_elems(list->_first);
    free(list);
}

int dlist_get_size(simple_dlist_t* list)
{
    return list->_len;
}

int dlist_is_empty(simple_dlist_t* list)
{
    return list->_first == NULL;
}

__DLIST_T* dlist_first(simple_dlist_t* list)
{
    if (list->_first == NULL)
        return NULL;

    return &list->_first->_elem;
}

__DLIST_T* dlist_last(simple_dlist_t* list)
{
    if (list->_last == NULL)
        return NULL;

    return &list->_last->_elem;
}

static dlist_elem_t* elem_at(simple_dlist_t* list, int idx)
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

__DLIST_T* dlist_at(simple_dlist_t* list, int idx)
{
    dlist_elem_t* e = elem_at(list, idx);
    if (e == NULL)
        return NULL;

    return &e->_elem;
}

static dlist_elem_t* create_elem()
{
    dlist_elem_t* new_elem = (dlist_elem_t*) malloc(sizeof(dlist_elem_t));
    new_elem->_next = NULL;
    new_elem->_prev = NULL;
    return new_elem;
}

void dlist_add(simple_dlist_t* list, __DLIST_T e)
{
    if (dlist_is_empty(list))
    {
        list->_first = create_elem();
        list->_first->_elem = e;
        list->_last = list->_first;
    }
    else
    {
        dlist_elem_t* new_elem = create_elem();
        new_elem->_elem = e;
        new_elem->_prev = list->_last;
        list->_last->_next = new_elem;
        list->_last = new_elem;
    }

    list->_len++;
}

void dlist_remove(simple_dlist_t* list, int idx)
{
    dlist_elem_t* found_elem = elem_at(list, idx);
    if (found_elem != NULL)
    {
        if (found_elem->_prev != NULL)
            found_elem->_prev->_next = found_elem->_next;
        if (found_elem->_next != NULL)
            found_elem->_next->_prev = found_elem->_prev;
        
        free(found_elem);
    }
}

simple_dlist_iterator_t* dlist_get_iterator(simple_dlist_t* list, int forward)
{
    simple_dlist_iterator_t* it = (simple_dlist_iterator_t*) malloc(sizeof(simple_dlist_iterator_t));
    it->_list = list;
    it->_forward = forward;
    if (forward)
    {
        it->_current_elem = it->_list->_first;
    }
    else
    {
        it->_current_elem = it->_list->_last;
    }
}

void dlist_free_iterator(simple_dlist_iterator_t* iterator)
{
    free(iterator);
}

__DLIST_T* dlist_next(simple_dlist_iterator_t* iterator)
{
    if (iterator->_list == NULL || iterator->_current_elem == NULL)
        return NULL;
        
    __DLIST_T* value = &iterator->_current_elem->_elem;

    if (iterator->_forward)
        iterator->_current_elem = iterator->_current_elem->_next;
    else
        iterator->_current_elem = iterator->_current_elem->_prev;

    return value;
}