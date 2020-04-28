#ifndef SIMPLELIB_SIMPLE_QUEUE
#define SIMPLELIB_SIMPLE_QUEUE

#define __T int

typedef struct simple_queue simple_queue_t;

simple_queue_t* create_queue();

void free_queue(simple_queue_t* q);

int get_queue_size(simple_queue_t* q);

int is_queue_empty(simple_queue_t* q);

__T peek_queue(simple_queue_t* q);

void push_queue(simple_queue_t* q, __T e);

__T deque(simple_queue_t* q);

#endif // SIMPLELIB_SIMPLE_QUEUE