#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIAL_ALLOCATION 10

typedef struct
{
    size_t element_size;                  // Generic implementation
    unsigned int num_allocated, num_used; // Keep track of the size
    void *array;                          // Using one-based indexing
    int (*comparator)(void *, void *);    // Returns -ve, 0, or +ve
    int type;                             // 0 for maxHeap, 1 for minHeap
} HEAP;

// swap elements at ith and jth index
static void _swap(HEAP *h, int i, int j)
{
    assert(i >= 0 && j >= 0 && i <= h->num_used && j <= h->num_used);
    void *arr = h->array;
    int size = h->element_size;

    void *buffer = malloc(size);
    char *ptr1 = (char *)arr + i * (h->element_size);
    char *ptr2 = (char *)arr + j * (h->element_size);
    memcpy(buffer, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buffer, size);
}

void initHeap(HEAP **hh, size_t elemSize,
              unsigned int num_allocated,
              int (*some_comparator)(void *, void *))
{
    *hh = malloc(sizeof(HEAP));
    HEAP *h = *hh;
    h->element_size = elemSize;
    h->num_used = 0;
    h->num_allocated = num_allocated;
    h->array = malloc((h->num_allocated + 1) * (h->element_size)); // 1 index heap
    assert(h->array != NULL);
    h->comparator = some_comparator;
}

// swap up element at index k to the top
void _swapUp(HEAP *h, int k)
{
    char *base = (char *)h->array;
    // error hote pare for char*
    while (k > 1 && h->comparator(base + k * (h->element_size), base + (k / 2) * (h->element_size)) > 0)
    {
        _swap(h, k, k / 2);
        k = k / 2;
    }
}

void insert(HEAP *h, void *n)
{
    // before insert allocate space
    if (h->num_allocated == h->num_used)
    {
        // dont care
        assert(0);
    }
    // insert element in its place

    // first copy the element to the very end

    //get the address of the last place to insert
    char *copy_addr = (char *)h->array + ((h->element_size) * (h->num_used + 1));
    memcpy((void *)copy_addr, n, h->element_size);
    h->num_used++;

    _swapUp(h, h->num_used);
}

void printAsInt(HEAP *h)
{
    int *arr = h->array;

    for (int i = 0; i < h->num_used; i++)
        printf("%d ", arr[i]);
}

void printAsString(HEAP *h)
{
    char *arr = h->array;

    for (int i = 1; i < h->num_used + 1; i++)
        printf("%s ", arr + i * h->element_size);

    printf("\n");
}
static char *_getElemAddr(HEAP *h, int index)
{
    assert(index <= h->num_used && index>0);
    char *base = h->array;
    return base + index * (h->element_size);
}
void _swapDown(HEAP *h, int index)
{
    int leftChild = -1;
    int rightChild = -1;
    if (2 * index <= h->num_used)
    {
        leftChild = 2 * index;
        if (2 * index + 1 <= h->num_used)
            rightChild = 2 * index + 1;
    }

    int maxIndex = index;
    if (leftChild != -1 && h->comparator(_getElemAddr(h,maxIndex), _getElemAddr(h,leftChild) )<0)
        maxIndex = leftChild;

    if (rightChild != -1 && h->comparator(_getElemAddr(h,maxIndex), _getElemAddr(h,rightChild))<0)
        maxIndex = rightChild;
    
    if(maxIndex != index)
    {
        // swap the two elements
        _swap(h,maxIndex,index);

        // now tree rooted at maxIndex may not satisfy heap property
        // so recursively swapdown
        _swapDown(h,maxIndex);
    }
}
// arrLen = length of the array containing heap
// no of heap elements would be arrLen - 1 as index 0 is 
void initHeapFromArray(HEAP **hh,size_t elemSize,
                        void* arr,
                        int arrLen,
                        int (*some_comparator)(void*, void*))
{
    *hh = malloc(sizeof(HEAP));
    HEAP *h = *hh;
    h->element_size = elemSize;
    h->num_used = arrLen-1;
    h->num_allocated = arrLen;
    h->array = arr; // 1 index heap
    assert(h->array != NULL);
    h->comparator = some_comparator;

    int i=0;
    for(i=((arrLen-1)/2); i>=1; i--)
        _swapDown(h,i);
}

void extract(HEAP *h, void *buffer)
{
    assert(h->num_used);
    memcpy(buffer, _getElemAddr(h,1), h->element_size);
    memcpy(_getElemAddr(h,1), _getElemAddr(h,h->num_used),h->element_size);
    h->num_used--;
    _swapDown(h, 1);
}

int main()
{
    HEAP *h = NULL;
    initHeap(&h, 5, 100, &strcmp);

    char *a = "aaaa";
    char *b = "bbbb";
    char *c = "cccc";
    char *d = "dddd";
    char *e = "eeee";
    char *f = "ffff";
    char *g = "gggg";

    insert(h, (void *)a);
    insert(h, (void *)b);
    insert(h, (void *)c);
    insert(h, (void *)d);
    insert(h, (void *)e);
    insert(h, (void *)f);
    insert(h, (void *)g);
    
    for(int i=0;i<7;i++)
    {
        printAsString(h);
        char buffer[5];
        extract(h,(void*)buffer);
        printf("\nExtractMax: %s\n",buffer);
    }

    return 0;
}
