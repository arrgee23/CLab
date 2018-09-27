/*
* Rahul Gautam
* 28-Sep-2018
* Indian Statistical Institute
* Assignment 2 problem 1
* https://www.isical.ac.in/~pdslab/2018/assignments/assignment2.pdf
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5000

typedef struct Sequence
{
    char type;
    int sum;
    size_t capacity;
    void *array;

} SEQUENCE;

void printError(int i)
{
    switch (i)
    {
    case 1:
        printf("\n[Error] Invalid Input");
        break;

    case 2:

        break;
    }
}

// prints the value of ith element
void get_element(SEQUENCE s, size_t i)
{
}

// number of elements of s
size_t length(SEQUENCE s)
{
}

// prints the sum
void summation(SEQUENCE s)
{
}
SEQUENCE* newSequence(char type, size_t size)
{
    SEQUENCE *s = NULL;
    s = (SEQUENCE *)malloc(sizeof(SEQUENCE));
    if (s != NULL)
    {
        s->type = type;
        s->capacity = size;
        s->sum = 0;
        s->array = NULL;
        if (s->type == 'i')
        {
            s->array = malloc(size * sizeof(int));
        }
        else if (s->type == 'f')
        {
            s->array = malloc(size * sizeof(float));
        }
        else if (s->type == 's')
        {
            s->array = malloc(size * sizeof(char *));
        }
        else
        {

            free(s);
            return NULL;
        }
    }
    return s;
}

static void printSeq(SEQUENCE *s)
{
    if (s->type == 'i')
    {
        int *arr = (int *)s->array;
        for (int i = 0; i < s->capacity; i++)
        {
            printf("%d ", arr[i]);
        }
    }
    else if (s->type == 'f')
    {
        float *arr = (float *)s->array;
        for (int i = 0; i < s->capacity; i++)
        {
            printf("%f ", arr[i]);
        }
    }
    else if (s->type == 's')
    {
        char **arr = (char **)s->array;
        for (int i = 0; i < s->capacity; i++)
        {
            printf("%s ", arr[i]);
        }
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    SEQUENCE **seqArray = (SEQUENCE **)malloc(n * sizeof(SEQUENCE *));

    int t = 0;

    while (t < n)
    {
        // type of array
        char c;
        scanf(" %c", &c);
        printf("**%c ",c);

        // size of array
        size_t s;
        scanf("%lu", &s);
        printf(" %lu \n",s);
        seqArray[t] = newSequence(c, s);
        
        if (seqArray[t])
        {
            if (seqArray[t]->type == 'i')
            {
                int *arr = (int *)seqArray[t]->array;
                for (int i = 0; i < s; i++)
                {
                    scanf("%d", &arr[i]);
                }
            }
            else if (seqArray[t]->type == 'f')
            {
                float *arr = (float *)seqArray[t]->array;
                for (int i = 0; i < s; i++)
                {
                    scanf("%f", &arr[i]);
                }
            }
            else if (seqArray[t]->type == 's')
            {
                char **arr = (char **)seqArray[t]->array;
                char buffer[SIZE];
                int len = 0;
                for (int i = 0; i < s; i++)
                {
                    scanf("%s", buffer);
                    len = strlen(buffer);
                    arr[i] = (char*)malloc((len+1)*sizeof(char));
                    strcpy(arr[i],buffer);
                }
            }
            printSeq(seqArray[t]);
        }
        else
        {
            printError(1);
            return 1;
        }
        t++;
    }

    return 0;
}