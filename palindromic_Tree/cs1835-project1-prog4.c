/*
* Rahul Gautam
* CS1835
* Indian Statistical Institute
* Planidromic Tree Implementation
* 7-Dec-2018
* Description:
* For the strings S and T, finding the number of equal palindromes, i.e., of triples (i, j, k) such that S[i..i + k] = T[j..j + k] is a palindrome.
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
            char sub = 'X';
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
                            if(subFound==0 && (c=='A' || c=='G' || c=='C' || c=='T'))
                            {
                                sub = 'N';
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

void countPalinTriplet(char** stringArray,int size)
{
    eerTree *at = malloc(sizeof(eerTree));
    initTree(at, size);
    int i=0;
    for(i=0;i<size;i++)
    {
        addString(at, stringArray[i], i);
        calculateOCC(at,i); // calculate occurance of each palindromic substring for each string
    }
    //printStrings(at, stringArray);

   
    int count = 0;
    for (i = 2; i < at->size; i++)
    {
        count += at->nodeArray[i].occ[0] * at->nodeArray[i].occ[1];
    }
    printf("%d\n", count);
}

int main(int argc, char **argv)
{
    char** stringArray = NULL;
    stringArray = readAndParse(argc,argv,stringArray);
    
    countPalinTriplet(stringArray,argc-1);
       /*
    for(int i=0;i<noOfStrings;i++)
    {
        printf("%s\n",stringArray[i]);
    }*/
    
    return 0;
}