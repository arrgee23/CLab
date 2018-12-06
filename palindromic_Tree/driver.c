#include "eerTree.h"

int main()
{
    char str[2000];
    strcpy(str, "ABBA");
    eerTree* at = malloc(sizeof(eerTree));
    initTree(at,2);
    /*
    for(int i=0;i<strlen(str);i++)
    {
        add(at,str,i,0);
    }

   
    at->ptr = NULL_NODE_INDEX;
    */
    addString(at,str,0);
    int t = at->size;
    char str2[2000];
    strcpy(str2, "ABAA");
    /*for(int i=0;i<strlen(str2);i++)
    {
        add(at,str2,i,1);
    }
    */
   addString(at,str2,1);
   char* strArray[] = {str,str2};
   printStrings(at,strArray);
   /*
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
    }*/
    return 0;
}