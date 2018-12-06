#include "eerTree.h"

int main()
{
    char str[2000];
    strcpy(str, "abba");
    arrTree* at = malloc(sizeof(arrTree));
    initTree(at);
    for(int i=0;i<strlen(str);i++)
    {
        add(at,str,i,0);
    }

    int t = at->size;
    at->ptr = NULL_NODE_INDEX;
    char str2[2000];
    strcpy(str2, "aba");
    for(int i=0;i<strlen(str2);i++)
    {
        add(at,str2,i,1);
    }

    for(int i=2;i<at->size;i++)
    {
        int start;
        
        if(i<t)
        {
            start=at->nodeArray[i].start[0];
        }
        else
        {
            start=at->nodeArray[i].start[1];
        }
        for(int k=start;k<start+at->nodeArray[i].length;k++)
        {
            if(i<t)
            {

                printf("%c",str[k]);
            }
            else 
                printf("%c",str2[k]);
        }
        puts("");
    }
    return 0;
}