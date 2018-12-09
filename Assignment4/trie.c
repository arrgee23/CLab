#include "trie.h"
#include <stdio.h>

void initTrieNode(TrieNode *tn)
{
#ifdef ASSIGNMENT_4
    tn->wordsStartingWith = 0;
#endif

    tn->endMarker = 0;
    int i = 0;
    for (i = 0; i < NUM_SYMS; i++)
        tn->children[i] = NULL;
}

void insert(TrieNode *root, char *string)
{
    assert(root != NULL);

    int len = strlen(string);
    TrieNode *cursor = root;

    char c;
    int i;
    int index = -1;
    for (i = 0; i < len; i++)
    {
        c = string[i];
        if (isdigit(c))
        {
            index = c -'0';
        }
        else if (isalpha(c))
        {
            c = tolower(c);
            index = c - 'a';
        }
        else
        {
            fprintf(stderr, "Non alphanumeric character %c is being inserted in trie.\n", c);
            exit(1);
        }

        // allocate memoty if not there
        if (NULL == cursor->children[index])
        {
            cursor->children[index] = (TrieNode *)malloc(sizeof(TrieNode));
            initTrieNode(cursor->children[index]);
        }
        #ifdef ASSIGNMENT_4
        cursor->children[index]->wordsStartingWith++;
        #endif

        if (i == len - 1) // mark it end for last char
            cursor->children[index]->endMarker++; // increase the count for word inserted

        //printf("%c ws=%lld\n",c,cursor->children[index]->wordsStartingWith);
        // move the pointer
        cursor = cursor->children[index];
    }
}
int search(TrieNode *root, char *string)
{
    assert(root != NULL);

    int len = strlen(string);
    TrieNode *cursor = root;

    char c;
    int i;
    int index = -1;
    for (i = 0; i < len; i++)
    {
        c = string[i];
        if (isdigit(c))
        {
            index = c -'0';
        }
        else if (isalpha(c))
        {
            c = tolower(c);
            index = c - 'a';
        }
        else
        {
            return 0; // non alphanumeric character search
        }

        if(cursor->children[index]!=NULL)
            cursor = cursor->children[index];
        else
            return 0; // string not there
        
    }
    return cursor->endMarker;
}
#ifdef ASSIGNMENT_4
int wordBeginsWith(TrieNode *root, char *string)
{
    assert(root != NULL);

    int len = strlen(string);
    TrieNode *cursor = root;

    char c;
    int i;
    int index = -1;
    for (i = 0; i < len; i++)
    {
        c = string[i];
        if (isdigit(c))
        {
            index = c -'0';
        }
        else if (isalpha(c))
        {
            c = tolower(c);
            index = c - 'a';
        }
        else
        {
            return 0; // non alphanumeric character search
        }

        if(cursor->children[index]!=NULL)
            cursor = cursor->children[index];
        else
            return 0; // string not there
        
    }
    return cursor->wordsStartingWith;
}
#endif
/*
int main()
{
    TrieNode* root = (TrieNode*)malloc(sizeof(TrieNode));
    initTrieNode(root);
    char str1[100],str2[100],str3[100],str4[100];
    strcpy(str1,"cat");
    strcpy(str2,"can");
    strcpy(str3,"ca");
    strcpy(str4,"incom123fg");
    
    insert(root,str1);
    insert(root,str2);
    insert(root,str3);
    insert(root,str4);
    //insert(root,str2);
    
    //printf("%d\n",search(root,str2));
    printf("%d\n",search(root,str1));
    printf("%d\n",search(root,str2));
    printf("%d\n",search(root,str3));
    printf("%d\n",search(root,str4));
    printf("%d\n",search(root,"c"));

    //printf("%d\n",wordBeginsWith(root,"ca"));
}*/