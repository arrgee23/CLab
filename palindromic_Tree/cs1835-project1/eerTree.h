/*
* Rahul Gautam
* Indian Statistical Institute
* Planidromic Tree Header
* 29-Nov-2018
*/
#ifndef EERTREE_H
#define EERTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define ALPHABET_SIZE 26 // a-z
#define MAX_NODES 10000000
#define NULL_NODE_INDEX 1
#define IMAGINARY_NODE_INDEX 0

#undef DEBUG
typedef struct Node
{
    int* start; // start index of all strings start[i] is -1 if no such string 
    int length;
    int sEdge;                // index of suffix edge node
    int iEdge[ALPHABET_SIZE]; // insertion edge node

    int* occAsMax;
    int* occ;
    // boolean array of k elements for k strings should be here for joint arrtree

} node;

typedef struct PalindromicTree
{
    //char* string; // string for which the tree is built
    node nodeArray[MAX_NODES];
    int ptr; // points to the last created node. longest palindrome
    int size; // total no of nodes
    int noOfStrings;
} eerTree;

void initNode(node *n, int len,int nos);

void calculateOCC(eerTree* t,int strNo);
void initTree(eerTree *t, int nos);

void addString(eerTree* at, char* str,int index);
// add I th char of the j th string to the eertrree
void add(eerTree *t, char *string, int i,int j);


void printStrings(eerTree *t,char** stringArray);

#endif