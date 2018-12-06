#include "eerTree.h"
/*
(a) Finding the number of subpalindromes, common to all k given strings.
(b) Finding the longest subpalindrome contained in all k given strings.
(c) For the strings S and T, finding the number of palindromes P having more occurrences
in S than in T.
(d) For the strings S and T, finding the number of equal palindromes, i.e., of triples (i, j, k)
such that S[i..i + k] = T[j..j + k] is a palindrome.
*/
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

void findCommonSubplalindromes()
{
    // traverse through the built tree and increase count for all the nodes where every start bit != -1
}
int main(int argc, char **argv)
{
    int noOfStrings = argc-1;
    char** stringArray = NULL;
    stringArray = readAndParse(argc,argv,stringArray);
    
    /*
    for(int i=0;i<noOfStrings;i++)
    {
        printf("%s\n",stringArray[i]);
    }*/
    
    return 0;
}