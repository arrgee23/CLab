/*
* Rahul Gautam
* Indian Statistical Institute
* Planidromic Tree Implementation
* 29-Nov-2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 // a-z
#define MAX_NODES 100000
#define NULL_NODE_INDEX 1
#define IMAGINARY_NODE_INDEX 0

#define DEBUG
typedef struct Node
{
    int start;
    int end;
    int length;
    int sEdge;                // index of suffix edge node
    int iEdge[ALPHABET_SIZE]; // insertion edge node

    // boolean array of k elements for k strings should be here for joint arrtree

} node;

typedef struct PalindromicTree
{
    //char* string; // string for which the tree is built
    node nodeArray[MAX_NODES];
    int ptr; // points to the last created node. longest palindrome

} arrTree;

void initNode(node *n, int len)
{
    n->length = len;
    n->sEdge = -1;
    int i = 0;
    for (i = 0; i < ALPHABET_SIZE; i++)
        n->iEdge[i] = -1;
}
void initTree(arrTree *t)
{
    // nodearry 0 is the imaginary node  and 1st node is null string node

    // 0 th node is imaginary node
    initNode(&(t->nodeArray[IMAGINARY_NODE_INDEX]), -1);
    t->nodeArray[IMAGINARY_NODE_INDEX].sEdge = IMAGINARY_NODE_INDEX;

    // 1st node is null  string
    initNode(&(t->nodeArray[NULL_NODE_INDEX]), 0);
    t->nodeArray[NULL_NODE_INDEX].sEdge = IMAGINARY_NODE_INDEX;

    t->ptr = NULL_NODE_INDEX; // points to null node initialy
}
int size = 2;
// add I th char of the string to the arrtrree
void add(arrTree *t, char *string, int i)
{
    int cursor = t->ptr;

    // the parent of the node we are goona insert with insertion edge
    node *parent = NULL;

    // traverse through the suffix edge till you find
    // a node of the form X such that  string[i]+X+string[i] would make a new palindrome
    while (1)
    {
        parent = &(t->nodeArray[cursor]);
        int length = parent->length;

        #ifdef DEBUG
        printf("i=%d cursor=%d len=%d\n",i,cursor,length);
        #endif

        if (i - length >= 1 && string[i] == string[i - length - 1])
            break;
        cursor = parent->sEdge;
    }

    // now we have found X
    // add the character as an insertion edge if its not already there
    // setup its suffix link
    if (parent->iEdge[string[i] - 'a'] == -1)
    {
        size++;
        // make a new node
        t->ptr=size;
        //node *newNode = &(t->nodeArray[t->ptr]);
        node *newNode = &(t->nodeArray[size]);

        initNode(newNode, parent->length + 2);   // the length would be parent node +2
        parent->iEdge[string[i] - 'a'] = t->ptr; // add insertion edge

        // adjust start and end
        newNode->start = i - newNode->length + 1;
        newNode->end = i;

        #ifdef DEBUG
        printf("adding: ");
        for(int j=newNode->start;j<=i;j++)
        {
            printf("%c",string[j]);
        }
        puts("");
        #endif
        // Now we set the suffix edge

        cursor = t->nodeArray[cursor].sEdge;

        // if its 1 length then 0 length node is its suffix
        if (newNode->length == 1)
        {
            newNode->sEdge = NULL_NODE_INDEX;
        }
        else
        {
            while (1)
            {
                int length = t->nodeArray[cursor].length;
                if (i - length >= 1 && string[i] == string[i - length - 1])
                    break;
                cursor = t->nodeArray[cursor].sEdge;
            }

            // set the suffix edge
            newNode->sEdge = t->nodeArray[cursor].iEdge[string[i]-'a'];
        }
    }
    else
    {
        // just make the tree pointer point to the current node
        t->ptr = parent->iEdge[string[i] - 'a'];
    }
}

int main()
{
    char str[2000];
    strcpy(str, "abba");
    arrTree* at = malloc(sizeof(arrTree));
    initTree(at);
    for(int i=0;i<strlen(str);i++)
    {
        add(at,str,i);
    }

    int t = size;
    at->ptr = NULL_NODE_INDEX;
    char str2[2000];
    strcpy(str2, "tkt");
    for(int i=0;i<strlen(str2);i++)
    {
        add(at,str2,i);
    }

    for(int i=2;i<=size;i++)
    {
        int start,end;
        start = at->nodeArray[i].start;
        end = at->nodeArray[i].end;
        
        for(int j=start;j<=end;j++)
        {
            if(i<=t)
                printf("%c",str[j]);
            else 
                printf("%c",str2[j]);
        }
        puts("");
    }
    return 0;
}