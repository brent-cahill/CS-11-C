/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"
#define NSLOTS 128


/*** Hash function. ***/

int hash(char *s)
{
    int sum = 0;
    int i;

    for (i = 0; i < strlen(s); ++i)
    {
        sum += s[i];
    }
    return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *result = (node *)malloc(sizeof(node));

    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->key = key;  /* Fill in the new node with the given key. */
    result->value = value; /* Fill in the new node with the given value. */
    result->next = NULL; /* points to the next node */

    return result;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *n;     /* a single node of the list */


    while (list != NULL)
    {
        n = list;
        list = list->next;

        /*
         * 'n' now points to the first element of the list, while
         * 'list' now points to everything but the first element.
         * Since nothing points to 'n', it can be freed.
         */

        free(n);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    node *n = create_node(NULL, NULL);

    hash_table *result = (hash_table *)malloc(sizeof(hash_table));

    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->table[0] = NULL;

    return result;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i = 0;
    while(ht != NULL)
    {
        i = 0;
        while(table != NULL)
        {
            free_list(table[i])
            i++;
        }
        ht++;
    }
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    keyVal;

    keyVal = hash(key);

    while(ht != NULL)
    {
        if 
    }
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{

}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{

}


