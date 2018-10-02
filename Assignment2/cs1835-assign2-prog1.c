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
#include <assert.h>

#define SIZE 10000
#define NEG_INF -9999999

typedef struct Sequence
{
    char type;
    long sum;
    size_t size;
    size_t capacity;
    void *array;
} SEQUENCE;

// Error printing functions to print errors at ease
void printError(int i)
{
    switch (i)
    {
    case 1:
        printf("\n[Error] Invalid Input\n");
        break;

    case 2:
        printf("\n[Error] Invalid Item type\n");
        break;

    case 3:
        printf("\n[Error] malloc fail\n");
        break;
    }
}
// having passed a sequence, gets its return value back
static long getNumericValue(SEQUENCE *s, size_t i)
{
    assert(i< s->size);
    long ret = 0;
    float num = 0, diff1 = 0, diff2 = 0;
    int n = 0, nPlus1 = 0, k = 0;
    char *str = NULL;

    switch (s->type)
    {
    case 'i':
        ret = ((int *)s->array)[i];
        break;

    case 'f':
        num = ((float *)s->array)[i];
        n = (int)num; // floor of num
        nPlus1 = n + 1;

        diff1 = num - (float)n;
        diff2 = (float)nPlus1 - num;

        ret = diff1 < diff2 ? n : nPlus1;
        break;

    case 's':
        str = ((char **)s->array)[i];
        k = 0;
        while (str[k])
        {
            ret += str[k++];
        }
        break;
    default:
        printError(2);
        assert(0);
    }
    return ret;
}

// prints the value of ith element
void get_element(SEQUENCE s, size_t i)
{
    assert(i < s.size);
    printf("%ld", getNumericValue(&s, i));
}

// number of elements of s
size_t length(SEQUENCE s)
{
    return s.size;
}

// prints the sum
void summation(SEQUENCE s)
{
    printf("%ld\n",s.sum);
}

SEQUENCE *newSequence(char type, size_t size)
{
    SEQUENCE *s = NULL;
    s = (SEQUENCE *)malloc(sizeof(SEQUENCE));
    if (s != NULL)
    {
        s->type = type;
        s->capacity = size;
        s->size = 0;
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
            //printf("%d(%ld) ", arr[i], getNumericValue(s, i));
        }
    }
    else if (s->type == 'f')
    {
        float *arr = (float *)s->array;
        for (int i = 0; i < s->capacity; i++)
        {
            printf("%f ", arr[i]);
            //printf("%f(%ld) ", arr[i], getNumericValue(s, i));
        }
    }
    else if (s->type == 's')
    {
        char **arr = (char **)s->array;
        for (int i = 0; i < s->capacity; i++)
        {
            printf("%s ", arr[i]);
            //printf("%s(%ld) ", arr[i], getNumericValue(s, i));
        }
    }
    printf("\n");
}
// adds a value to a sequence
static void add(SEQUENCE *s, void *value)
{
    char* str=NULL;
    switch (s->type)
    {
    case 'i':
        ((int*)s->array)[s->size++] = *((int*)value);
        
        break;
    case 'f':
        ((float*)s->array)[s->size++] = *((float*)value);
        break;
    case 's':
        str = (char*)value;
        ((char**)s->array)[s->size++] = (char *)malloc((strlen(str) + 1) * sizeof(char)); // allocate space
        if(((char**)s->array)[s->size-1])
            strcpy(((char**)s->array)[s->size-1],str);
        else{
            printError(3);
            assert(0);
        }
        break;
    default:
        printError(2);
        assert(0);
    }
    s->sum += getNumericValue(s,s->size-1);
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
        //printf("**%c ",c);

        // size of array
        size_t s;
        scanf("%lu", &s);
        //printf(" %lu \n",s);
        seqArray[t] = newSequence(c, s);

        if (seqArray[t])
        {
            if (seqArray[t]->type == 'i')
            {
                //int *arr = (int *)seqArray[t]->array;
                int elem;
                for (int i = 0; i < s; i++)
                {
                    scanf("%d", &elem);
                    add(seqArray[t],(void*)(&elem));
                }
            }
            else if (seqArray[t]->type == 'f')
            {
                //float *arr = (float *)seqArray[t]->array;
                float elem;
                for (int i = 0; i < s; i++)
                {
                    //scanf("%f", &arr[i]);
                    scanf("%f", &elem);
                    add(seqArray[t],(void*)(&elem));
                }
            }
            else if (seqArray[t]->type == 's')
            {
               // char **arr = (char **)seqArray[t]->array;
                char buffer[SIZE];
               // int len = 0;
                for (int i = 0; i < s; i++)
                {
                    scanf("%s", buffer);
                    /*
                    len = strlen(buffer);
                    arr[i] = (char *)malloc((len + 1) * sizeof(char));
                    strcpy(arr[i], buffer);
                    */
                    add(seqArray[t],(void*)buffer);
                }
            }
            //printSeq(seqArray[t]);
        }
        else
        {
            printError(1);
            return 1;
        }
        t++;
    }

    int i=0;
    int max = seqArray[0]->sum;
    int maxIndex = 0;
    for(i=1;i<n;i++)
    {
        if(seqArray[i]->sum > max){
            max = seqArray[i]->sum;
            maxIndex = i;
        }
    }
    printSeq(seqArray[maxIndex]);

    return 0;
}