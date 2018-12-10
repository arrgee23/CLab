/*
Rahul Gautam
Indian Statistical Institute
CS1835
09-Dec-2018
Given a text file and a file with strings, return the number of occurances of each string 
as prefix in the text file 

*/
#include "trie.h"

void insertStringsIntoTrie(TrieNode *root, char *inputFile)
{
    FILE *fp = fopen(inputFile, "r");
    char c;
    TrieNode *cursor = root;
    int index = -1;
    while ((c = fgetc(fp)) != EOF)
    {
        if (isalnum(c))
        {
            if (isdigit(c))
            {
                index = c - '0';
            }
            else
            {
                c = tolower(c);
                index = c - 'a';
            }
            // allocate memoty if not there
            if (NULL == cursor->children[index])
            {
                cursor->children[index] = (TrieNode *)malloc(sizeof(TrieNode));
                initTrieNode(cursor->children[index]);
            }
            cursor->children[index]->wordsStartingWith++;

            //printf("%c ws=%lld\n",c,cursor->children[index]->wordsStartingWith);
            // move the pointer
            cursor = cursor->children[index];
        }
        else // we have encountered a deliminator. end string, reset cursor
        {
            if (cursor != root)
            {
                cursor->endMarker++; // increase the count for word inserted
                cursor = root;
            }
        }
    }
}

void countWord(TrieNode *root, char *inputFile)
{
    FILE *fp = fopen(inputFile, "r");
    char c;
    TrieNode *cursor = root;
    int index = -1;

    int invalid = 0;
    char lastChar = 0;
    while ((c = fgetc(fp)) != EOF)
    {

        if (isalnum(c))
        {
            printf("%c", c);
            if (isdigit(c))
            {
                index = c - '0';
            }
            else
            {
                c = tolower(c);
                index = c - 'a';
            }

            //printf("%c ws=%lld\n",c,cursor->children[index]->wordsStartingWith);
            // move the pointer
            if (!invalid && cursor->children[index] != NULL)
                cursor = cursor->children[index];
            else
            {
                invalid = 1;
            }
        }
        else // we have encountered a '\n'
        {
            if (!invalid) // valid
            {
                printf(" %lld\n", cursor->wordsStartingWith);
            }
            else
            {
                printf(" 0\n");
            }
            if (cursor != root)
            {
                cursor = root;
            }
            invalid = 0;
        }
        lastChar = c;
    }
    // we have encountered EOF
    if (isalnum(lastChar)) // we didnot print output for the last line
    {
        if (!invalid) // valid
        {
            printf(" %lld\n", cursor->wordsStartingWith);
        }
        else
        {
            printf(" 0\n");
        }
    }
}

// read the text file into strings
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./<executable> <file1> <file2>");
        return 1;
    }
    char *inputFile = argv[1];
    char *stringFile = argv[2];

    TrieNode *root = (TrieNode *)malloc(sizeof(TrieNode));
    initTrieNode(root);

    insertStringsIntoTrie(root, inputFile);
    countWord(root, stringFile);
}