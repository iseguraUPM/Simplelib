#include "../include/simplelib/simple_queue.h"

#include <stdlib.h>

typedef struct queue_elem_t
{
    __QUEUE_T _elem;
    struct queue_elem_t* _next;
} queue_elem_t;

typedef struct simple_queue_t
{   
    int _len;
    queue_elem_t* _first;
    queue_elem_t* _last;
} simple_queue_t;

simple_queue_t* queue_create()
{
    simple_queue_t* new_s = (simple_queue_t*) malloc(sizeof(simple_queue_t));
    new_s->_first = NULL;
    new_s->_last = NULL;
    new_s->_len = 0;

    return new_s;
}

static void free_elems(queue_elem_t* e)
{
    if (e != NULL)
    {
        free_elems(e->_next);
        free(e);
    }
}

void queue_free(simple_queue_t* q)
{
    if (q != NULL)
    {
        free_elems(q->_first);
        free(q);
    }
}

int queue_get_size(simple_queue_t* q)
{
    return q->_len;
}

int queue_is_empty(simple_queue_t* q)
{
    return q->_first == NULL;
}

__QUEUE_T queue_peek(simple_queue_t* q)
{
    return q->_first->_elem;
}

static queue_elem_t* create_elem()
{
    return (queue_elem_t*) malloc(sizeof(queue_elem_t));
}

void queue_push(simple_queue_t* q, __QUEUE_T e)
{
    queue_elem_t* new_e = create_elem();
    new_e->_elem = e;
    new_e->_next = NULL;

    if (q->_last != NULL)
    {
        q->_last->_next = new_e;
        q->_last = new_e;
    }
    else
    {
        q->_first = new_e;
        q->_last = new_e;
    }

    q->_len++;
}

__QUEUE_T queue_pop(simple_queue_t* q)
{
    queue_elem_t* first_e = q->_first;

    if (first_e->_next != NULL)
    {
        q->_first = first_e->_next;
    }
    else
    {
        q->_first = NULL;
        q->_last = NULL;
    }
    
    int e = first_e->_elem;
    free(first_e);

    q->_len--;
    return e;
}