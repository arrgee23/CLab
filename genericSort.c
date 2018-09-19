/*
* Rahul Gautam 
* Sep 19, 2018
* Indian Statistical Institute
* Implementation of a generic quick sort
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_SIZE 100

int compareInt(void* x,void* y)
{
    int* a = (int*)x;
    int* b = (int*)y;
    return *a-(*b);
}
void* getElemAddr(void* array,int i,int elementSize)
{
    return (char*)array + i*(elementSize);
}


// swap elements at ith and jth index
// TODO pass size to assert for longer length 
static void swap(void* arr,int i,int j,int elementSize)
{
    assert(i>=0 && j>=0 );
    
    void* buffer = malloc(elementSize);
    void* ptr1 = getElemAddr(arr,i,elementSize);//(char*)arr+i*(elementSize);
    void* ptr2 = getElemAddr(arr,j,elementSize);
    memcpy(buffer,ptr1,elementSize);
    memcpy(ptr1,ptr2,elementSize);
    memcpy(ptr2,buffer,elementSize);
}

/*
* Pivots the array according to last element
* both start and end inclusive
* 
*/
int pivot(void* arr,size_t elemSize,int startIndex,int endIndex,int (*comparator)(void*,void*))
{
  //  printArray((int*)arr,endIndex+1);
    void* pivotElem = getElemAddr(arr,endIndex,elemSize);
    int ll = *((int*)pivotElem);
   // printf("%d",*((int*)pivotElem));
    int i = startIndex;
    int j = endIndex-1;

    while(1){

        while(i<j && comparator(pivotElem,getElemAddr(arr,i,elemSize)) > 1) // pivot > elem
        {
            i++;
        }


        while(i<j && comparator(getElemAddr(arr,j,elemSize),pivotElem) > 1) // pivot < elem
        {
            j--;
        }
        if(i<j)
            swap(arr,i,j,elemSize);
        if(i>=j)

            break;
    }
    if(comparator( pivotElem,getElemAddr(arr,j,elemSize) ) > 0)
          // when all elements to the left of pivot is smaller than pivot no need to swap
    {       // pivot is ai its correct place
        return endIndex;
    }
    // swap high element with pivot
    swap(arr,endIndex,j,elemSize);
    return j;
}
void quickSort(void* arr,size_t elemSize,int startIndex,int endIndex,int (*comparator)(void*,void*))
{
    if(startIndex<endIndex)
    {
        int pivotIndex = pivot(arr,elemSize,startIndex,endIndex,comparator);
        quickSort(arr,elemSize,startIndex,pivotIndex-1,comparator);
        quickSort(arr,elemSize,pivotIndex+1,endIndex,comparator);
    }

}
void printArray(int* arr,int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    printf("\n");
}
int main()
{
    /*
    int* arr = (int*)malloc(7*sizeof(int));
    //{1, 2, 6, 7, 8, 9, 5};
    arr[0] = 17;
    arr[1] = 20;
    arr[2] = 6;
    arr[3] = -7;
    arr[4] = 84;
    arr[5] = 9;
    arr[6] = -5;   
    */
    int arr[] = {89,3,-2,6,7,2};
    int l = sizeof(arr)/sizeof(int);

    printf("%d**\n",l);

    printArray((int*)arr,l);
    quickSort((void*)arr,sizeof(int),0,l-1,&compareInt);

    printArray((int*)arr,l);

    //printf("pivot pos = %d",k);
    return 0;
}
