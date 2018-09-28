#include <stdio.h>

long long int reachableCount(int n,int k)
{
    if(n==0)
        return 0;
    if(k==0)
        return 1;
    long long int sum = 0;
    int i=0;
    for(i=0;i<=k;i++)
    {
        sum+=(2*i+1)*reachableCount(n-1,k-1);
    }
        
    return sum;
}

int main()
{
    printf("%lld\n",reachableCount(3,1));
    return 0;
}