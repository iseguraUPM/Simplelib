#include <stdio.h>
#include <string.h>

#include <simplelib/simple_queue.h>
#include <simplelib/simple_stack.h>

#define streq(a, b) strcmp(a, b) == 0

int stack_push_pop_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    simple_stack_t* stack = create_stack();
    for (int i = 0; i < size; i++)
    {
        push_stack(stack, input[i]);
    }
    
    for (int i = 0; i < size; i++)
    {
        fprintf(stdout, "%d\n", pop(stack));
    }

    return is_stack_empty(stack);
}

int queue_push_pop_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    simple_queue_t* queue = create_queue();
    for (int i = 0; i < size; i++)
    {
        push_queue(queue, input[i]);
    }
    
    for (int i = 0; i < size; i++)
    {
        fprintf(stdout, "%d\n", deque(queue));
    }

    return is_stack_empty(queue);
}

int main(int argc, char** argv)
{
    char test[32];
    fscanf(stdin, "%s\n", test);

    if (streq(test, "stack-push-pop"))
    {
        return stack_push_pop_test();
    }
    else if (streq(test, "queue-push-deque"))
    {
        return queue_push_pop_test();
    }

    return 1;
}