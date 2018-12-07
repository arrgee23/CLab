/*
* Rahul Gautam
* Indian Statistical Institute
* Planidromic Tree Implementation
* 29-Nov-2018
*/

#include "eerTree.h"

void initNode(node *n, int len,int nos)
{
    n->length = len;
    n->sEdge = -1;
    int i = 0;
    for (i = 0; i < ALPHABET_SIZE; i++)
        n->iEdge[i] = -1;
    n->start = (int*)malloc(nos*sizeof(int));
    n->occAsMax = (int*)malloc(nos*sizeof(int));
    n->occ = (int*)malloc(nos*sizeof(int));
    
    for (i = 0; i < nos; i++)
    {
        n->start[i] = -1;
        n->occAsMax[i] = 0;
        n->occ[i] = 0;
    }
}

void initTree(eerTree *t, int nos)
{
    t->noOfStrings = nos;
    // nodearry 0 is the imaginary node  and 1st node is null string node
    
    // 0 th node is imaginary node
    initNode(&(t->nodeArray[IMAGINARY_NODE_INDEX]), -1,t->noOfStrings);
    t->nodeArray[IMAGINARY_NODE_INDEX].sEdge = IMAGINARY_NODE_INDEX;

    // 1st node is null  string
    initNode(&(t->nodeArray[NULL_NODE_INDEX]), 0,t->noOfStrings);
    t->nodeArray[NULL_NODE_INDEX].sEdge = IMAGINARY_NODE_INDEX;

    t->ptr = NULL_NODE_INDEX; // points to null node initialy
    t->size = 2;
    
}

void calculateOCC(eerTree* t,int strNo)
{
    
    int i=0;
    for(i=t->size-1;i>=2;i--)
        t->nodeArray[i].occ[strNo] = t->nodeArray[i].occAsMax[strNo];
    
    for(i=t->size-1;i>=2;i--)
        t->nodeArray[t->nodeArray[i].sEdge].occ[strNo]+= t->nodeArray[i].occ[strNo];
    
}

void addString(eerTree* at, char* str,int index)
{
    for(int i=0;i<strlen(str);i++)
    {
        add(at,str,i,index);
    }
    at->ptr = NULL_NODE_INDEX;
}

// add I th char of the j th string to the eertrree
void add(eerTree *t, char *string, int i,int j)
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

        initNode(newNode, parent->length + 2,t->noOfStrings);   // the length would be parent node +2
        parent->iEdge[string[i] - 'A'] = t->ptr; // add insertion edge

        // adjust start and end
        newNode->start[j] = i - newNode->length + 1;
        newNode->occAsMax[j] = 1;
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
        t->nodeArray[t->ptr].start[j] = i - t->nodeArray[t->ptr].length + 1;
        t->nodeArray[t->ptr].occAsMax[j]++;
    }
}

void printStrings(eerTree *t,char** stringArray)
{
    int i=0;
    printf("Size=%d\n",t->size-2);
    //int* occ = calculateOCC(t);
    for(i=2;i<t->size;i++)
    {
        node n = t->nodeArray[i];
        int stringIndex = -1;
        int j=0;
        for(j=0;j<t->noOfStrings;j++)
        {
            if(n.start[j]!=-1)
            {
                stringIndex = j;
                break;
            }
        }

        int start = n.start[stringIndex];
        int len = n.length;
        #ifdef DEBUG
        printf("string: %d, start: %d len: %d\n",stringIndex,start,len);
        #endif
        for(j=0;j<len;j++)
        {
            printf("%c",stringArray[stringIndex][start+j]);
        }
        printf("\t[occ]");
        for(int l=0;l<t->noOfStrings;l++)
        {
            printf("\tstring[%d]: %d",l, t->nodeArray[i].occ[l]);
        }
        printf("\n");
    }
}