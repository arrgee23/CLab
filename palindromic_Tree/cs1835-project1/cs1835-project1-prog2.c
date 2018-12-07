/*
* Rahul Gautam
* CS1835
* Indian Statistical Institute
* Planidromic Tree Implementation
* 7-Dec-2018
* Description:
*  Finding the longest subpalindrome contained in all k given strings.
*/

#include "eerTree.h"
char** readAndParse(int argc, char **argv,char** stringArray)
{
    int filecount = argc - 1;

    char *buffer = 0;
    long length;

    stringArray = (char**)malloc(filecount*sizeof(char*));

    int n = 0;
    while (n < filecount)
    {
        FILE *f = fopen(argv[n+1], "rb");
        //printf("%s",argv[n+1]);
        if (f)
        {
            fseek(f, 0, SEEK_END);
            length = ftell(f);
            fseek(f, 0, SEEK_SET);
            buffer = malloc(length);
            if (buffer)
            {
                int k=fread(buffer, 1, length, f);
                if(k==0)
                {
                    printf("File Reading error\n");
                    exit(1);
                }
            }
            fclose(f);
        }

        if (buffer)
        {
            // start to process your data / extract strings here...
            stringArray[n] = malloc(length*sizeof(char));
            //printf("%s",buffer);

            int sp=0;
            int i=0;
            int firstLineRead = 0;
            char sub = 'N';
            int subFound = 0;
            
            for(i=0;i<length;i++)
            {
                // reject till the first '\n'
                if(firstLineRead==0)
                {
                    if(buffer[i]=='\n')
                        firstLineRead = 1;
                }
                else
                {
                    char c = buffer[i];
                    
                    // read uppercase letters into string
                    if(isalnum(c))
                    {
                        if(isalpha(c))
                        {
                             // covert lowercase in uppercase and reject others
                            c = toupper(c);
                            // in case of DNA
                            if(subFound==0 && (c!='A' && c!='G' && c!='C' && c!='T'))
                            {
                                sub = 'X';
                                subFound = 1;
                            }
                        }
                        stringArray[n][sp++] = c;
                    }
                    // add null character
                    stringArray[n][sp] = 0;

                    // replace numeric character by sub code
                    int j=0;
                    for(j=0;j<sp;j++)
                    {
                        char c = stringArray[n][j];
                        if(isdigit(c))
                        {
                            stringArray[n][j] = sub;
                        }
                    }
                }
            }
        }
        n++;
    }
    /*
    for(int i=0;i<filecount;i++)
    {
        printf("%s\n",stringArray[i]);
    }*/
    return stringArray;
}

int isCommonInAll(node* n,int size)
{
    int i=0;
    //printf("size = %d length=%d\n",size,n->length);
    for(i=0;i<size;i++)
    {
        //printf("starti =%d",n->start[i]);
        if(n->start[i]== -1)
            return 0;
    }
    //printf("\n\n");
    return 1;
}
void printSubStr(char* str,int i,int j)
{
    int k;
    for(k=i;k<j;k++)
        printf("%c",str[k]);
    printf("\n");
}
void findLongestCommonSubplalindrome(char** stringArray,int size)
{
    // traverse through the built tree and increase count for all the nodes where every start bit != -1
    eerTree *at = malloc(sizeof(eerTree));
    initTree(at, size);
    int i=0;
    for(i=0;i<size;i++)
        addString(at, stringArray[i], i);

    //printStrings(at, stringArray);
    int longest=0;
    int li = -1;
    for(i=2;i<at->size;i++)
    {
        if(isCommonInAll(&(at->nodeArray[i]),at->noOfStrings))
        {
            #ifdef DEBUG
            //printf("common\n");
            char* str = stringArray[0];
            int start = at->nodeArray[i].start[0];
            int len = at->nodeArray[i].length;

            printSubStr(str,start,start+len);
            #endif
            if(at->nodeArray[i].length>longest)
            {
                longest = at->nodeArray[i].length;
                li = i;
            }
        }
    }
    
    printf("\nLength of longest palindrome: %d\n",longest);
    if(longest != 0)
    {

        char* str = stringArray[0];
        int start = at->nodeArray[li].start[0];
        int len = at->nodeArray[li].length;
        printf("Longest palindrome is: ");
        printSubStr(str,start,start+len);
        printf("\n");
    }
}
int main(int argc, char **argv)
{
    char** stringArray = NULL;
    stringArray = readAndParse(argc,argv,stringArray);
    
    findLongestCommonSubplalindrome(stringArray,argc-1);
       /*
    for(int i=0;i<noOfStrings;i++)
    {
        printf("%s\n",stringArray[i]);
    }*/
    
    return 0;
}