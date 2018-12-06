#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define ALPHABET_SIZE 26 // a-z
#define MAX_NODES 100000
#define NULL_NODE_INDEX 1
#define IMAGINARY_NODE_INDEX 0
#define MAX_NO_OF_STRINGS 100

#define DEBUG
typedef struct Node
{
    int start[MAX_NO_OF_STRINGS]; // start index of all strings start[i] is -1 if no such string 
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
    int size; // total no of nodes
    int capacity;
} arrTree;

void initNode(node *n, int len);

void initTree(arrTree *t);

// add I th char of the j th string to the eertrree
void add(arrTree *t, char *string, int i,int j);