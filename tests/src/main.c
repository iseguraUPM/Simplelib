#include <stdio.h>
#include <string.h>

#include <simplelib/simple_queue.h>
#include <simplelib/simple_stack.h>
#include <simplelib/simple_btree.h>
#include <simplelib/simple_linked_list.h>
#include <simplelib/transform.h>
#include <simplelib/simple_hash_set.h>

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

int dlist_add_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    simple_dlist_t* dlist = create_dlist();
    for (int i = 0; i < size; i++)
    {
        add_dlist(dlist, input[i]);
    }

    for (int i = 0; i < get_dlist_size(dlist); i++)
    {
        fprintf(stdout, "%d\n", *at_dlist(dlist, i));
    }

    return get_dlist_size(dlist) == size;
}

int btree_to_list_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    // Keys are values
    simple_btree_t* btree = create_btree();
    for (int i = 0; i < size; i++)
    {
        add_btree(btree, input[i], input[i]);
    }

    simple_dlist_t* dlist = to_sorted_list(btree);
    for (int i = 0; i < get_dlist_size(dlist); i++)
    {
        fprintf(stdout, "%d\n", *at_dlist(dlist, i));
    }

    return get_btree_size(btree) == get_dlist_size(dlist);
}

int btree_remove_root_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    // Keys are values
    simple_btree_t* btree = create_btree();
    for (int i = 0; i < size; i++)
    {
        add_btree(btree, input[i], input[i]);
    }

    // Remove root (first elem.)
    remove_btree(btree, input[0]);

    simple_dlist_t* dlist = to_sorted_list(btree);
    for (int i = 0; i < get_dlist_size(dlist); i++)
    {
        fprintf(stdout, "%d\n", *at_dlist(dlist, i));
    }

    return get_btree_size(btree) == size - 1;
}

int hset_contains_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    simple_hset_t* hset = create_hset();
    for (int i = 0; i < size; i++)
    {
        add_hset(hset, input[i]);
    }

    for (int i = 0; i < get_hset_size(hset); i++)
    {
        if (hset_contains(hset, input[i]))
            fprintf(stdout, "%d\n", input[i]);
    }

    return get_hset_size(hset) == size;
}

int hset_remove_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    simple_hset_t* hset = create_hset();
    for (int i = 0; i < size; i++)
    {
        add_hset(hset, input[i]);
    }

    for (int i = 0; i < size; i++)
    {
        remove_hset(hset, input[i]);
    }

    for (int i = 0; i < size; i++)
    {
        if (!hset_contains(hset, input[i]))
            fprintf(stdout, "%d\n", input[i]);
    }

    return get_hset_size(hset) == 0;
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
    else if (streq(test, "dlist-add-test"))
    {
        return dlist_add_test();
    }
    else if (streq(test, "btree-to-list"))
    {
        return btree_to_list_test();
    }
    else if (streq(test, "btree-remove-root"))
    {
        return btree_remove_root_test();
    }
    else if (streq(test, "hset-contains"))
    {
        return hset_contains_test();
    }
    else if (streq(test, "hset-remove"))
    {
        return hset_remove_test();
    }

    return -1;
}