#ifndef SIMPLELIB_SIMPLE_STACK
#define SIMPLELIB_SIMPLE_STACK

#define __STACK_T int

typedef struct simple_stack simple_stack_t;

simple_stack_t* create_stack();

void free_stack(simple_stack_t* q);

int get_stack_size(simple_stack_t* q);

int is_stack_empty(simple_stack_t* q);

__STACK_T peek_stack(simple_stack_t* q);

void push_stack(simple_stack_t* q, __STACK_T e);

__STACK_T pop(simple_stack_t* q);

#endif // SIMPLELIB_SIMPLE_STACK