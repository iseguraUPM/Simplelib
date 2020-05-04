#include "../include/simplelib/simple_queue.h"

#include <stdlib.h>

typedef struct queue_elem
{
    __T _elem;
    struct queue_elem* _next;
} queue_elem_t;

typedef struct simple_queue
{   
    int _len;
    queue_elem_t* _first;
    queue_elem_t* _last;
} simple_queue_t;

simple_queue_t* create_queue()
{
    simple_queue_t* new_s = (simple_queue_t*) malloc(sizeof(simple_queue_t));
    new_s->_first = NULL;
    new_s->_last = NULL;
    new_s->_len = 0;

    return new_s;
}

void free_queue_elems(queue_elem_t* e)
{
    if (e != NULL)
    {
        free_queue_elems(e->_next);
        free(e);
    }
}

void free_queue(simple_queue_t* q)
{
    if (q != NULL)
    {
        free_queue_elems(q->_first);
        free(q);
    }
}

int get_queue_size(simple_queue_t* q)
{
    return q->_len;
}

int is_queue_empty(simple_queue_t* q)
{
    return q->_first == NULL;
}

__T peek_queue(simple_queue_t* q)
{
    return q->_first->_elem;
}

queue_elem_t* create_queue_elem()
{
    return (queue_elem_t*) malloc(sizeof(queue_elem_t));
}

void push_queue(simple_queue_t* q, __T e)
{
    queue_elem_t* new_e = create_queue_elem();
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

__T deque(simple_queue_t* q)
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