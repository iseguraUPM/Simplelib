#include <stdio.h>
#include <string.h>

#include <simplelib/simple_queue.h>
#include <simplelib/simple_stack.h>
#include <simplelib/simple_bin_tree.h>
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

    simple_stack_t* stack = stack_create();
    for (int i = 0; i < size; i++)
    {
        stack_push(stack, input[i]);
    }
    
    for (int i = 0; i < size; i++)
    {
        fprintf(stdout, "%d\n", stack_pop(stack));
    }

    return stack_is_empty(stack);
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

    simple_queue_t* queue = queue_create();
    for (int i = 0; i < size; i++)
    {
        queue_push(queue, input[i]);
    }
    
    for (int i = 0; i < size; i++)
    {
        fprintf(stdout, "%d\n", queue_pop(queue));
    }

    return queue_is_empty(queue);
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

    simple_dlist_t* dlist = dlist_create();
    for (int i = 0; i < size; i++)
    {
        dlist_add(dlist, input[i]);
    }

    for (int i = 0; i < dlist_get_size(dlist); i++)
    {
        fprintf(stdout, "%d\n", *dlist_at(dlist, i));
    }

    return dlist_get_size(dlist) == size;
}

int bin_tree_to_list_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    // Keys are values
    simple_bin_tree_t* tree = bin_tree_create();
    for (int i = 0; i < size; i++)
    {
        bin_tree_put(tree, input[i], input[i]);
    }

    simple_dlist_t* dlist = bin_tree_to_sorted_list(tree);
    for (int i = 0; i < dlist_get_size(dlist); i++)
    {
        fprintf(stdout, "%d\n", *dlist_at(dlist, i));
    }

    return bin_tree_get_size(tree) == dlist_get_size(dlist);
}

int bin_tree_remove_root_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    // Keys are values
    simple_bin_tree_t* tree = bin_tree_create();
    for (int i = 0; i < size; i++)
    {
        bin_tree_put(tree, input[i], input[i]);
    }

    // Remove root (first elem.)
    bin_tree_remove(tree, input[0]);

    simple_dlist_t* dlist = bin_tree_to_sorted_list(tree);
    for (int i = 0; i < dlist_get_size(dlist); i++)
    {
        fprintf(stdout, "%d\n", *dlist_at(dlist, i));
    }

    return bin_tree_get_size(tree) == size - 1;
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

    simple_hset_t* hset = hset_create();
    for (int i = 0; i < size; i++)
    {
        hset_add(hset, input[i]);
    }

    for (int i = 0; i < hset_get_size(hset); i++)
    {
        if (hset_contains(hset, input[i]))
            fprintf(stdout, "%d\n", input[i]);
    }

    return hset_get_size(hset) == size;
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

    simple_hset_t* hset = hset_create();
    for (int i = 0; i < size; i++)
    {
        hset_add(hset, input[i]);
    }

    for (int i = 0; i < size; i++)
    {
        hset_remove(hset, input[i]);
    }

    for (int i = 0; i < size; i++)
    {
        if (!hset_contains(hset, input[i]))
            fprintf(stdout, "%d\n", input[i]);
    }

    return hset_get_size(hset) == 0;
}

int hset_large_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    simple_hset_t* hset = hset_create();
    for (int i = 0; i < size; i++)
    {
        hset_add(hset, input[i]);
    }

    for (int i = 0; i < size; i++)
    {
        if (hset_contains(hset, input[i]))
            fprintf(stdout, "%d\n", input[i]);
    }

    return hset_get_size(hset) == size;
}

int dlist_iterator_test()
{
    int size;
    fscanf(stdin, "%d\n", &size);

    int input[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(stdin, "%d\n", input + i);
    }

    simple_dlist_t* dlist = dlist_create();
    for (int i = 0; i < size; i++)
    {
        dlist_add(dlist, input[i]);
    }

    simple_dlist_iterator_t* it = dlist_get_iterator(dlist, 1);
    int *e = dlist_next(it);
    while (e != NULL)
    {
        fprintf(stdout, "%d\n", *e);
        e = dlist_next(it);
    }

    return dlist_get_size(dlist) == size;
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
    else if (streq(test, "bintree-to-list"))
    {
        return bin_tree_to_list_test();
    }
    else if (streq(test, "bintree-remove-root"))
    {
        return bin_tree_remove_root_test();
    }
    else if (streq(test, "hset-contains"))
    {
        return hset_contains_test();
    }
    else if (streq(test, "hset-remove"))
    {
        return hset_remove_test();
    }
    else if (streq(test, "hset-large"))
    {
        return hset_large_test();
    }
    else if (streq(test, "dlist-iterator"))
    {
        return dlist_iterator_test();
    }

    return -1;
}