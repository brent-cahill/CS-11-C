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
    srand(time(NULL));

    if (argc != 3 || atoi(argv[1]) < 3)
    {
        fprintf(stderr, "%s\n", "usage: [number of cells], "
            "[number of generations]");
        return 0;
    }

    ncells = atoi(argv[1]);
    ngens = atoi(argv[2]);

    numbers = (int *) calloc(ncells, sizeof(int));
    numbers2 = (int *) calloc(ncells, sizeof(int));

    /* Check that the calloc call succeeded. */
    if (numbers == NULL || numbers2 == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }
    numbers[0] = 0;
    for (i = 1; i < ncells - 1; i++)
    {
        ran = rand() % 2;
        numbers[i] = ran;
        numbers2[i] = ran;
    }
    numbers[ncells - 1] = 0;
    
    for (i = 0; i < ngens; i++)
    {
        num_print(numbers, ncells);
        update(numbers, numbers2, ncells);
    }

    free(numbers);
    free(numbers2);
    print_memory_leaks();
    return 0;
}

void update(int *array, int *change_array, int size)
{
    int *previous = change_array;
    int *current = change_array + 1;
    int *next = change_array + 2;
    int *comp = array + 1;
    int i;

    for (i = 1; i < size - 1; i++)
    {
        if ((*previous == 1 && *next == 0) && *current == 0)
        {
            *comp = 1;
        }
        else if ((*previous == 0 && *next == 1) && *current == 0)
        {
            *comp = 1;
        }
        else
        {
            *comp = 0;
        }
        previous++;
        current++;
        next++;
        comp++;
    }

    current = change_array;
    for (i = 0; i < size; i++)
    {
        *current = *array;
        array++;
        current++;
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
