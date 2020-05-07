#ifndef SIMPLELIB_SIMPLE_STACK
#define SIMPLELIB_SIMPLE_STACK

#define __STACK_T int

typedef struct simple_stack simple_stack_t;

simple_stack_t* stack_create();

void stack_free(simple_stack_t* s);

/**
 * @param s 
 * @return the number of elements in the stack
 */
int stack_get_size(simple_stack_t* s);

/**
 * @param s
 * @return 1 if the stack is empty or 0 if is not
 */
int stack_is_empty(simple_stack_t* s);

/**
 * @param s
 * @return the last element of the stack
 */
__STACK_T stack_peek(simple_stack_t* s);

/**
 * Add an element at the top of the stack
 * @param s
 */
void stack_push(simple_stack_t* s, __STACK_T e);

/**
 * Remove the element at the top of the stack
 * @param s
 * @return the element removed
 */
__STACK_T stack_pop(simple_stack_t* s);

#endif /* SIMPLELIB_SIMPLE_STACK */