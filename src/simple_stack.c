#include "../include/simplelib/simple_stack.h"

#include <stdlib.h>

typedef struct stack_elem
{
    __STACK_T _elem;
    struct stack_elem* _prev;
} stack_elem_t;

typedef struct simple_stack
{   
    int _len;
    stack_elem_t* _last;
} simple_stack_t;

simple_stack_t* create_stack()
{
    simple_stack_t* new_s = (simple_stack_t*) malloc(sizeof(simple_stack_t));
    new_s->_last = NULL;
    new_s->_len = 0;

    return new_s;
}

static void free_stack_elems(stack_elem_t* e)
{
    if (e != NULL)
    {
        free_stack_elems(e->_prev);
        free(e);
    }
}

void free_stack(simple_stack_t* s)
{
    if (s != NULL)
    {
        free_stack_elems(s->_last);
        free(s);
    }
}

int get_stack_size(simple_stack_t* q)
{
    return q->_len;
}

int is_stack_empty(simple_stack_t* s)
{
    return s->_last == NULL;
}

__STACK_T peek_stack(simple_stack_t* s)
{
    return s->_last->_elem;
}

static stack_elem_t* create_stack_elem()
{
    return (stack_elem_t*) malloc(sizeof(stack_elem_t));
}

void push_stack(simple_stack_t* s, __STACK_T e)
{
    stack_elem_t* new_e = create_stack_elem();
    new_e->_elem = e;
    
    if (s->_last != NULL)
    {
        new_e->_prev = s->_last;
        s->_last = new_e;
    }
    else
    {
        new_e->_prev = NULL;
        s->_last = new_e;
    }

    s->_len++;
}

__STACK_T pop(simple_stack_t* s)
{
    stack_elem_t* last_e = s->_last;

    if (last_e->_prev != NULL)
    {
        s->_last = last_e->_prev;
    }
    else
    {
        s->_last = NULL;
    }
    
    int e = last_e->_elem;
    free(last_e);

    s->_len--;
    return e;
}