#ifndef SIMPLELIB_SIMPLE_QUEUE
#define SIMPLELIB_SIMPLE_QUEUE

#define __QUEUE_T int

typedef struct simple_queue_t simple_queue_t;

simple_queue_t* queue_create();

void queue_free(simple_queue_t* q);

/**
 * @param q
 * @return the number of elements in the queue
 */
int queue_get_size(simple_queue_t* q);

/**
 * @param s
 * @return 1 if the queue is empty or 0 if is not
 */
int queue_is_empty(simple_queue_t* q);

/**
 * @param s
 * @return the first element of the queue
 */
__QUEUE_T queue_peek(simple_queue_t* q);

/**
 * Add an element at the end of the queue
 * @param s
 */
void queue_push(simple_queue_t* q, __QUEUE_T e);

/**
 * Remove the first element of the queue
 * @param s
 * @return the element removed
 */
__QUEUE_T queue_pop(simple_queue_t* q);

#endif /* SIMPLELIB_SIMPLE_QUEUE */