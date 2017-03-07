#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "memcheck.h"

node *
quickSort(node *list)
{
    node *aside = NULL;
    node *smaller_list = NULL;
    node *greater_list = NULL;
    node *item = NULL;
    node *final_list = NULL;
    node *half_list;

    if (list == NULL || list->next == NULL)
    {
        final_list = copy_list(list);
        return final_list;
    }

    aside = create_node(list->data, aside);
    list = list->next;

    for (item = list; item != NULL; item = item->next)
    {
        if (item->data >= aside->data)
        {
            greater_list = create_node(item->data, greater_list);
        }
        else
        {
            smaller_list = create_node(item->data, smaller_list);
        }
    }
    greater_list = quickSort(greater_list);
    smaller_list = quickSort(smaller_list);
    half_list = append_lists(aside, greater_list);
    final_list = append_lists(smaller_list, half_list);

    assert(is_sorted(final_list));
    
    /* free_list(aside); */
    /* free_list(greater_list); */
    /* free_list(smaller_list); */
    return final_list;
}

int main(int argc, char *argv[])
{
    int i;
    int quiet;
    int argCounter = 0;
    node *list;
    node *result;
    list = NULL;

    for (i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-q") == 0)
        {
            quiet = 1;
        }
        else
        {
            list = create_node(atoi(argv[i]), list);
            argCounter++;
        }
    }

    if (argCounter == 0)
    {
        fprintf(stderr, "usage: %s [-q] number1 number2 ...", argv[0]);
        exit(1);
    }
    if (quiet == 1)
    {
        return 0;
    }
    else
    {
        result = quickSort(list);
        /* free_list(list); */
    }

    print_list(result);
    
    /* free_list(result); */
    print_memory_leaks();
    return 0;
}
