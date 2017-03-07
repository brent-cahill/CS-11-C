#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_INTS 32


void minSort(int numElements, int array[]);
void bubbleSort(int numElements, int array[]);

int main(int argc, char *argv[])
{
    int i;
    int j;
    int quiet = 0;
    int bubble = 0;
    int *sort;
    int argCounter = 0;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") == 0)
        {
            quiet = 1;
        }
        else
        {
            sort[argCounter] = atoi(argv[i]);
            argCounter++;
        }
    }

    if (argCounter == 0)
    {
        fprintf(stderr, "usage: sorter [-q] number1 number2 ... ");
        return 0;
    }

    if (quiet == 1)
    {
        return 0;
    }
    else
    {
        quickSort(argCounter, sort);
    }

    for (j = 0; j < argCounter; j++)
    {
        printf("%d\n", sort[j]);
    }
    return 0;
}

/* Sorts an array of numbers according to the selection/minimum sort
algorithm. */
void minSort(int numElements, int array[])
{
    int start = 0;
    int smallest;
    int first;
    int second;
    int i;
    while(start != numElements)
    {
        smallest = start;
        for (i = start + 1; i < numElements; i++)
        {
            if (array[i] < array[smallest])
            {
                smallest = i;
            }
        }
        first = array[start];
        second = array[smallest];
        array[smallest] = first;
        array[start] = second;
        start++;
    }
    for (i = 1; i < numElements; i++)
    {
        assert(array[i] >= array[i-1]);
    }
}

/* Sorts an array of numbers according to the bubblesort algorithm. */
void bubbleSort(int numElements, int array[])
{
    int i;
    int sortCheck = 0;
    int first;
    int second;
    int sorted = 0;
    while(sorted != 1)
    {
        sortCheck = 0;
        for (i = 0; i < numElements - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                first = array[i];
                second = array[i + 1];
                array[i] = second;
                array[i + 1] = first;
                sortCheck = 1;
            }
        }
        if (sortCheck == 0)
        {
            sorted = 1;
        }
    }
    for (i = 1; i < numElements; i++)
    {
        assert(array[i] >= array[i-1]);
    }
}
