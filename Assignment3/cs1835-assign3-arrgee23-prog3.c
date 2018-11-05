/*
* Rahul Gautam
* Indian Statistical Institute
* MIN-MAX heap
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define SIZE 10000

typedef struct MINMAX
{
    int *arr;
    int size;
    int capacity;
} MinMax;

void swap(MinMax *mm, int i, int j)
{
    int t = mm->arr[i];
    mm->arr[i] = mm->arr[j];
    mm->arr[j] = t;
}
int parent(MinMax *mm, int i)
{
    if (i <= 0)
        return -1;
    if (i >= mm->size)
        return -1;

    return (i - 1) / 2;
}

int leftChild(MinMax *mm, int i)
{
    if (i < 0)
        return -1;
    if (i >= mm->size)
        return -1;

    return 2 * i + 1 > mm->size - 1 ? -1 : 2 * i + 1;
}

int rightChild(MinMax *mm, int i)
{
    if (i < 0)
        return -1;
    if (i >= mm->size)
        return -1;

    return 2 * i + 2 > mm->size - 1 ? -1 : 2 * i + 2;
}

int smallestChildOrGrandChild(MinMax *mm, int n)
{
    int min = mm->arr[n];
    int index = n;

    int l = leftChild(mm, n);
    if (l != -1)
    {
        int ll = leftChild(mm, l);
        int lr = rightChild(mm, l);

        if (mm->arr[l] < min)
        {
            min = mm->arr[l];
            index = l;
        }

        if (ll != -1 && mm->arr[ll] < min)
        {
            min = mm->arr[ll];
            index = ll;
        }
        if (lr != -1 && mm->arr[lr] < min)
        {
            min = mm->arr[lr];
            index = lr;
        }
    }

    int r = rightChild(mm, n);
    if (r != -1)
    {
        int rl = leftChild(mm, r);
        int rr = rightChild(mm, r);

        if (mm->arr[r] < min)
        {
            min = mm->arr[r];
            index = r;
        }

        if (rl != -1 && mm->arr[rl] < min)
        {
            min = mm->arr[rl];
            index = rl;
        }
        if (rr != -1 && mm->arr[rr] < min)
        {
            min = mm->arr[rr];
            index = rr;
        }
    }

    return index;
}
int largestChildOrGrandChild(MinMax *mm, int n)
{
    int min = mm->arr[n];
    int index = n;

    int l = leftChild(mm, n);
    if (l != -1)
    {
        int ll = leftChild(mm, l);
        int lr = rightChild(mm, l);

        if (mm->arr[l] > min)
        {
            min = mm->arr[l];
            index = l;
        }

        if (ll != -1 && mm->arr[ll] > min)
        {
            min = mm->arr[ll];
            index = ll;
        }
        if (lr != -1 && mm->arr[lr] > min)
        {
            min = mm->arr[lr];
            index = lr;
        }
    }

    int r = rightChild(mm, n);
    if (r != -1)
    {
        int rl = leftChild(mm, r);
        int rr = rightChild(mm, r);

        if (mm->arr[r] > min)
        {
            min = mm->arr[r];
            index = r;
        }

        if (rl != -1 && mm->arr[rl] > min)
        {
            min = mm->arr[rl];
            index = rl;
        }
        if (rr != -1 && mm->arr[rr] > min)
        {
            min = mm->arr[rr];
            index = rr;
        }
    }

    return index;
}
int indexToLevel(int index)
{
    assert(index >= 0);
    return log(index + 1) / log(2);
}

void shiftDownMin(MinMax *mm, int i)
{
    int m = smallestChildOrGrandChild(mm, i);
    if (m != i) // i is not smallest among its childern and grandchildren
    {
        // if any of the children is smallest
        if (m == leftChild(mm, i) || m == rightChild(mm, i))
            swap(mm, i, m);
        else // smallest is one of the grandchildren
        {
            swap(mm, i, m);
            if (mm->arr[m] > mm->arr[parent(mm, m)])
                swap(mm, m, parent(mm, m));
            shiftDownMin(mm, m);
        }
    }
}
void shiftDownMax(MinMax *mm, int i)
{
    int m = largestChildOrGrandChild(mm, i);
    if (m != i) // i is not largest among its childern and grandchildren
    {
        // if any of the children is largest
        if (m == leftChild(mm, i) || m == rightChild(mm, i))
            swap(mm, i, m);
        else // largest is one of the grandchildren
        {
            swap(mm, i, m);
            if (mm->arr[m] < mm->arr[parent(mm, m)])
                swap(mm, m, parent(mm, m));
            shiftDownMax(mm, m);
        }
    }
}
void shiftDown(MinMax *mm, int i)
{
    //assert(i>=0 && i< mm->size);
    if (indexToLevel(i) % 2) // max node wala level
    {
        shiftDownMax(mm, i);
    }
    else
        shiftDownMin(mm, i);
}

void bubbleUpMin(MinMax *mm, int i)
{
    int g = parent(mm, parent(mm, i));
    if (g != -1 && mm->arr[i] < mm->arr[g])
    {
        swap(mm, i, g);
        bubbleUpMin(mm, g);
    }
}

void bubbleUpMax(MinMax *mm, int i)
{
    int g = parent(mm, parent(mm, i));
    if (g != -1 && mm->arr[i] > mm->arr[g])
    {
        swap(mm, i, g);
        bubbleUpMax(mm, g);
    }
}

void bubbleUp(MinMax *mm, int i)
{
    if (indexToLevel(i) % 2) // max level
    {
        if (parent(mm, i) != -1 &&
            mm->arr[i] < mm->arr[parent(mm, i)])
        {
            swap(mm, i, parent(mm, i));
            bubbleUpMin(mm, parent(mm, i));
        }
        else
            bubbleUpMax(mm, i);
    }
    else
    {
        if (parent(mm, i) != -1 &&
            mm->arr[i] > mm->arr[parent(mm, i)])
        {
            swap(mm, i, parent(mm, i));
            bubbleUpMax(mm, parent(mm, i));
        }
        else
            bubbleUpMin(mm, i);
    }
}

void insert(MinMax *mm, int n)
{
    
    assert(mm->size < mm->capacity);
    mm->arr[mm->size++] = n;
    bubbleUp(mm, mm->size - 1);
    //printf("inseert size: %d\n",mm->size);
}

int extractMin(MinMax *mm)
{
    assert(mm->size > 0);
    int ret = mm->arr[0];
    mm->arr[0] = mm->arr[mm->size - 1];
    mm->size--;
    shiftDown(mm, 0);
    return ret;
}
int findKthSmallest(MinMax* mm,int k)
{
    //printf("%d**\n",k);
    assert(k>0 && k<=mm->size);
    int* arr = (int*)malloc(k*sizeof(int));
    for(int i=0;i<k;i++)
        arr[i] = extractMin(mm);
    
    for(int i=0;i<k;i++)
        insert(mm,arr[i]);

    return arr[k-1]; 
}
int main(int argc, char const *argv[])
{

    MinMax mm;
    mm.capacity = SIZE;
    mm.size = 0;
    mm.arr = (int *)malloc(mm.capacity * sizeof(int));

    int t;
    char temp;
    do
    {
        scanf("%d", &t);
        insert(&mm, t);
    } while (getchar() != 10);
    
    for (int i = 1; i < argc; i++)
    {
        int k;
        sscanf(argv[i],"%d",&k);
        //printf("%d",k);
        if(k>0)
            printf("%d ",findKthSmallest(&mm,mm.size-k+1));
        else
            printf("%d ",findKthSmallest(&mm,-k));

    }
    return 0;
}
