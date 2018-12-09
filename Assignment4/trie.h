#ifndef TRIE_H
#define TRIE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#include<ctype.h>

#define NUM_SYMS 26+10 // lowercase  alphanumeric
#define ASSIGNMENT_4

typedef struct trienode
{
    struct trienode* children[NUM_SYMS];
    #ifdef ASSIGNMENT_4
    long long wordsStartingWith; // count the number of strings with prefix in the path till this node
    #endif
    int endMarker; //  marks end of word, also counts no of same words inserted
}TrieNode;

void initTrieNode(TrieNode* tn);
void insert(TrieNode* root,char* string);
int search(TrieNode* root,char* string);

#endif // TRIE_H
