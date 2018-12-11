/*
Rahul Gautam
Indian Statistical Institute
CS1835
09-Dec-2018
problem statement:

Let S 1 , S 2 , . . . , S M be M stacks, with capacities k 1 , k 2 , . . . , k M , respectively. Suppose that, initially,
all stacks are full, and no further push operations can be done. The objective is to obtain a non-
empty subset (not necessarily proper) of the stacks such that all stacks in the subset have the same
number of elements. In order to achieve this objective, you may use as many pop operations as you
like. Write a program that selects a subset such that the total number of elements in this subset is
the maximum possible. If the total number of elements in multiple such subsets is the same, you
should choose the subset that has fewer stacks.

Input format:
The capacities k 1 , k 2 , . . . , k M will be provided as command-line arguments in order.

Output format: The indices of the stacks that are included in the selected subset, and the number
of elements per stack in this subset. Note that stacks are indexed starting from 1.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair
{
    int value;
    int index;
} Pair;

int comparePair(const void *p1, const void *p2)
{
    Pair *p11 = (Pair *)p1;
    Pair *p22 = (Pair *)p2;

    return p11->value - p22->value;
}

int main(int argc, char **argv)
{
    int size = argc - 1;
    Pair *arr = (Pair *)malloc(size * sizeof(Pair));

    int i;
    for (i = 0; i < size; i++)
    {
        arr[i].index = i;
        arr[i].value = atoi(argv[i + 1]);
    }
    // sort the values
    qsort((void *)arr, size, sizeof(Pair), comparePair);

    int max = -99999;
    int indexStart = -1;
    int lastValue = -1; // to avoid equal height stacks
    for (i = 0; i < size; i++)
    {

        //printf("%d %d, ",arr[i].index,arr[i].value);
        int value = arr[i].value;
        if (value != lastValue)
        {
            // as the elements are sorted from left to right
            // we can choose a left element and make all the stacks to the right equal to that
            // maxWithThisValue represents the value with all possible(stacks having less than the number of elements would be 0) stacks 
            //having value number of items
            lastValue = value;
            int maxWithThisValue = value * (size-i);
            if(maxWithThisValue>=max) // equal to sign is added so that we choose a smaller size subset
            {
                max = maxWithThisValue;
                indexStart = i; // we take all the elements after ith including ith
            }
        }
        else
        {
            // simply skip the element
        }
    }
    // now we have done all required computaiton
    // output the value
    int stackHeight = max/(size-indexStart);
    for(i=indexStart;i<size;i++)
    {
        printf("%d ",arr[i].index+1);
    }
    printf("%d\n",stackHeight);
    return 0;
}