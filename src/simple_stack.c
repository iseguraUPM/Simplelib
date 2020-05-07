#include "../include/simplelib/simple_stack.h"

#include <stdlib.h>

typedef struct stack_elem_t
{
    __STACK_T _elem;
    struct stack_elem_t* _prev;
} stack_elem_t;

typedef struct simple_stack_t
{   
    int _len;
    stack_elem_t* _last;
} simple_stack_t;

simple_stack_t* stack_create()
{
    simple_stack_t* new_s = (simple_stack_t*) malloc(sizeof(simple_stack_t));
    new_s->_last = NULL;
    new_s->_len = 0;

    return new_s;
}

static void free_elems(stack_elem_t* e)
{
    if (e != NULL)
    {
        free_elems(e->_prev);
        free(e);
    }
}

void stack_free(simple_stack_t* s)
{
    if (s != NULL)
    {
        free_elems(s->_last);
        free(s);
    }
}

int stack_get_size(simple_stack_t* s)
{
    return s->_len;
}

int stack_is_empty(simple_stack_t* s)
{
    return s->_last == NULL;
}

__STACK_T stack_peek(simple_stack_t* s)
{
    return s->_last->_elem;
}

static stack_elem_t* create_elem()
{
    return (stack_elem_t*) malloc(sizeof(stack_elem_t));
}

void stack_push(simple_stack_t* s, __STACK_T e)
{
    stack_elem_t* new_e = create_elem();
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

__STACK_T stack_pop(simple_stack_t* s)
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