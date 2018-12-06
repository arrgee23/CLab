/*
* Rahul Gautam
* Indian Statistical Institute
* Planidromic Tree Implementation
* 29-Nov-2018
*/

#include "eerTree.h"

void initNode(node *n, int len)
{
    n->length = len;
    n->sEdge = -1;
    int i = 0;
    for (i = 0; i < ALPHABET_SIZE; i++)
        n->iEdge[i] = -1;
    for (i = 0; i < MAX_NO_OF_STRINGS; i++)
        n->start[i] = -1;
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
    t->size = 2;
}

// add I th char of the j th string to the eertrree
void add(arrTree *t, char *string, int i,int j)
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
    if (parent->iEdge[string[i] - 'A'] == -1)
    {
        // make a new node
        t->ptr=t->size;
        //node *newNode = &(t->nodeArray[t->ptr]);
        node *newNode = &(t->nodeArray[t->size++]);

        initNode(newNode, parent->length + 2);   // the length would be parent node +2
        parent->iEdge[string[i] - 'A'] = t->ptr; // add insertion edge

        // adjust start and end
        newNode->start[j] = i - newNode->length + 1;

        #ifdef DEBUG
        printf("adding: ");
        for(int k=newNode->start[j];k<newNode->start[j]+newNode->length;k++)
        {
            printf("%c",string[k]);
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
            newNode->sEdge = t->nodeArray[cursor].iEdge[string[i]-'A'];
        }
    }
    else
    {
        // just make the tree pointer point to the current node
        t->ptr = parent->iEdge[string[i] - 'A'];
    }
}