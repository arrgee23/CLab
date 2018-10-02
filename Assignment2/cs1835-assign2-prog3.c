/*
* Rahul Gautam
* 02-Oct-2018
* Indian Statistical Institute
* Assignment 2 problem 3
* https://www.isical.ac.in/~pdslab/2018/assignments/assignment2.pdf
*/


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// given k steps returns the returns the no of points reachable
// in n dimensions 
long long int reachableCount(int n,int k)
{
    if(n==0)
        return 1;
    if(k==0)
        return 1;
    if(n==1)
        return 2*k + 1;
    
    long long int sum = 0;
    int i=0;

    // use i length rope in this (nth dimension), use rest (k-i) for other dimensions 
    for(i=0;i<=k;i++)
    {
        if(i!=0) // with non zero length rope you can go in two directions. Negative and positive
            sum += 2*reachableCount(n-1,k-i);
        else
            sum += reachableCount(n-1,k-i);
    }
        
    return sum;
}

int main(int argc,char** argv)
{
    if(argc != 3)
    {
        printf("Usage: ./<execfile> <n> <k>\n");
        return 1;

    }
    
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    //printf("%d %d",n,k );
    assert(n>=0 && n<=5);
    assert(k>=0 && k<=100);

    printf("%lld\n",reachableCount(n,k));
    return 0;
}