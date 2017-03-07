#include <stdlib.h>
#include "memcheck.h"
#include <stdio.h>
#include <time.h>

/* Updates the 'array' according to the given rules */
void update(int *array, int *change_array, int size);

/* Prints the 'array' */
void num_print(int *numbers, int size);


int main(int argc, char const *argv[])
{
    int i;
    int ran;
    int *numbers;
    int *numbers2;
    int ncells;
    int ngens;
    srand(time(NULL)); /* Initializes the random number generator */

    /* 
     * Need exactly 3 command line arguments, and at least 3 cells,
     * since each end must be 0, otherwise, print a usage statement.
     */
    if (argc != 3 || atoi(argv[1]) < 3)
    {
        fprintf(stderr, "%s\n", "usage: [number of cells], " 
            "[number of generations]");
        return 0;
    }

    ncells = atoi(argv[1]);
    ngens = atoi(argv[2]);

    /* Dynamic memory allocation for the two "arrays" */
    numbers = (int *) calloc(ncells, sizeof(int));
    numbers2 = (int *) calloc(ncells, sizeof(int));

    /* Check that the calloc call succeeded. */
    if (numbers == NULL || numbers2 == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }

    numbers[0] = 0; /* Each end must be 0 */

    for (i = 1; i < ncells - 1; i++)
    {
        ran = rand() % 2;
        numbers[i] = ran;
        numbers2[i] = ran;
    }

    numbers[ncells - 1] = 0; /* Each end must be 0 */

    /* Prints and updates for every generation */
    for (i = 0; i < ngens; i++)
    {
        num_print(numbers, ncells);
        update(numbers, numbers2, ncells);
    }

    /* Frees the memory allocated for numbers and numbers2 */
    free(numbers);
    free(numbers2);

    /* Checks for memory leaks */
    print_memory_leaks();
    return 0;
}

void update(int *array, int *change_array, int size)
{
    int i;

    for (i = 1; i < size - 1; i++)
    {
        if ((change_array[i - 1] + change_array[i + 1] == 1)
            && change_array[i] == 0)
        {
            array[i] = 1;
        }
        else
        {
            array[i] = 0;
        }
    }

    for (i = 0; i < size; i++)
    {
        change_array[i] = array[i];
    }
}

void num_print(int array[], int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (array[i] == 0)
        {
            printf(".");
        }
        else
        {
            printf("*");
        }
    }
    printf("\n");
}
