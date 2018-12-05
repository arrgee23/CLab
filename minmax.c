/*
* Rahul Gautam
* Indian Statistical Institute
* MIN-MAX heap
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 10000

typedef struct MINMAX{
    int* arr;
    int size;
    int capacity;
}MinMax;

int parent(MinMax* mm,int i)
{
    if(i <= 0)
        return -1;
    if(i >= mm->size)
        return -1;

    return (i-1)/2;
}

int leftChild(MinMax* mm,int i)
{
    if(i < 0)
        return -1;
    if(i >= mm->size)
        return -1;

    return 2*i+1>mm->size -1 ? -1:2*i+1; 
}

int rightChild(MinMax* mm,int i)
{
    if(i < 0)
        return -1;
    if(i >= mm->size)
        return -1;

    return 2*i+2>mm->size -1 ? -1:2*i+2;
}

int twoPower(int i)
{
    assert(i>=0);
    if(i==0)
        return 1;
    return 2*twoPower(i-1);
}

int indexToLevel(int index)
{
    assert(index>=0);
    int i=0;
    while(1)
    {
        if(twoPower(i)-1<= index && index<twoPower(i+1) - 1)
            return i;
        i++;
    }
}

void shiftDownMin(MinMax* mm, int i)
{
    if( !( leftChild(mm,i) == -1 && rightChild(mm,i) == -1) )
    {
        int min,minIndex;
        int l = leftChild(mm,i);
        int r = rightChild(mm,i);
        
        if(leftChild(mm,i) != -1)
        {

            min = 
        }
    }
}

void shiftDown(MinMax* mm, int i)
{
    assert(i<=0 && i< mm->size)
    if(indexToLevel(i)%2) // max node wala level
    {
        shiftDownMax(mm,i);
    }
    else
        shiftDownMin(mm,i);

}

void main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
