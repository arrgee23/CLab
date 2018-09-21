#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    as there are 60*24 = 14400 possible values of n 
    so checking how many cars are there in the time wont
    consume much time.


*/

#define MINUTES_IN_DAY 24*60

typedef struct {

	int start;
    int end;
}Interval;

int clockToAbsolute(int n)
{
    return (n/100)*60 + n%100;
} 

void absoluteToclock(int n)
{
    //return (n/60)*100+n%60;

    if(n/60 < 10)
        printf("0");   
    printf("%d",n/60);


    if(n%60<10) // 1 digit
        printf("0");   
    printf("%d",n%60);
}

int isInInterval(int n,Interval* i)
{
    return n>=i->start && n<=i->end ;
}

// counts cabs at nth minute
int countCabsAt(int n,Interval* arr,int len)
{
    int i=0;
    int sum = 0;
    for(int i=0;i<len;i++)
    {
        if(arr[i].start<= n && arr[i].end>= n)
            sum++;
    }
    return sum;
}

int main()
{
    int n=0;
    scanf("%d",&n);
    //printf("%d\n",n);
    if(n<=0)
    {
        printf("number of intervals should be greater than 0\n");
        return 2;
    }
        
    Interval* arr = (Interval*)malloc(n*sizeof(Interval));

    int i=0;
    long unsigned int sz = 10;
    char* buffer = (char*)malloc(sz*sizeof(char));
    for(i=0;i<n;i++)
    {
        /*
        getline(&buffer,&sz,stdin);
        arr[i].start = parseLine(buffer,1);
        arr[i].end = parseLine(buffer,2);
        */
        scanf("%d",&arr[i].start);
        scanf("%d",&arr[i].end);
        if(arr[i].start>arr[i].end)
        {
            printf("Start time should not be greater than end\n");
            return 1;
        }

        arr[i].start = clockToAbsolute(arr[i].start);
        arr[i].end = clockToAbsolute(arr[i].end);

        //arr[i].start = absoluteToclock(arr[i].start);
        //arr[i].end = absoluteToclock(arr[i].end);
        //printf("%d %d \n",arr[i].start,arr[i].end);

    }
    
    /*
    for(i=0;i<n;i++)
        printf("%d %d \n",arr[i].start,arr[i].end);
    */
    

   // for every moment check how many cars are within that interval
   // if its greater than max
   // check for how much time it is in

   int max = 0;
   i =0;
   int start = 0;
   int end  = 0;
   while(i<MINUTES_IN_DAY)
   {
       int count = countCabsAt(i,arr,n);
       if(count>max) // ith moment we have max cabs
       {
           // count till which time interval max cabs are available
            max = count;
            start = i;
            
            while(i<MINUTES_IN_DAY && max == countCabsAt(i,arr,n))
            {
                i++;
            }
            if(i>start)
                end = i-1;
            else
                end = start;

       }
       else // move to the next minute
       {
           i++;
       }
   }
    absoluteToclock(start);
    printf(" ");
    absoluteToclock(end);
    printf(" %d \n",max);

    /*
    printf("******");
    absoluteToclock(0);
    printf("\n");
    absoluteToclock(1);
    printf("\n");
    absoluteToclock(59);
    printf("\n");
    absoluteToclock(60);
    printf("\n");
    absoluteToclock(61);
    printf("\n");
    absoluteToclock(555);
    */

}