/*
* Rahul Gautam
* Indian Statistical Institute
* 5-Nov-2018
* Assignment 3 prog 1
* 
* The Trie implementation is taken from geeksforgeeks trie example and used with minor modifications
* 
*/

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define MAX_STRING_LENGTH 10000
// Alphabet size (# of symbols)

#define ALPHABET_SIZE (26)
#define INDEX(c) ((int)c - (int)'a')

#define FREE(p) \
	free(p);    \
	p = NULL;

// forward declration
typedef struct trie_node trie_node_t;

// trie node
struct trie_node
{
	int value; // non zero if leaf
	trie_node_t *children[ALPHABET_SIZE];
};

// trie ADT
typedef struct trie trie_t;

struct trie
{
	trie_node_t *root;
	int count;
};

typedef struct node
{
	void *data;
	struct node *next;
} Node;

typedef struct linkedList
{
	Node *head;
	size_t elemSize;
	int (*comparator)(const void *, const void *);
	int length;
} LinkedList;

static Node *_makeNode(void *data, size_t size)
{
	Node *n = (Node *)malloc(sizeof(Node));
	if (n == NULL)
		assert(0);

	n->data = malloc(size);
	if (!n->data)
		assert(0);
	memcpy(n->data, data, size);
	n->next = NULL;

	return n;
}

// Return empty Linked list. all initialized
LinkedList *initLinkList(int (*comparator)(const void *, const void *), size_t elemSize)
{
	LinkedList *ll = (LinkedList *)malloc(sizeof(LinkedList));
	if (!ll)
		assert(0);

	ll->head = NULL;
	ll->elemSize = elemSize;
	ll->comparator = comparator;
	ll->length = 0;

	return ll;
}

// If ll has No node or single node then return NULL
// Else return prev to last Node
static Node *_findPrevToLastNode(LinkedList *ll)
{
	Node *ptr = ll->head;
	if (ptr == NULL)
		return NULL;
	while (ptr->next != NULL && ptr->next->next != NULL)
	{
		ptr = ptr->next;
	}
	return ptr->next == NULL ? NULL : ptr;
}
// finds the number of occurances of value, returns count if successful, else 0
int findValue(LinkedList *ll, void *value)
{
	if (ll->length)
		return 0;
	// search for the value
	int count = 0;
	Node *temp = ll->head;

	while (temp != NULL)
	{
		if (ll->comparator(temp->data, value) == 0)
			count++;
		temp = temp->next;
	}
	return count;
}
// deletes the 1st occurance of value, returns 1 if successful, else 0
int deleteValue(LinkedList *ll, void *value)
{
	if (!ll->length)
		return 0;

	// search for the value
	int found = 0;
	Node *temp = ll->head;
	Node *prev = NULL;
	while (temp != NULL)
	{
		if (ll->comparator(temp->data, value) == 0)
		{
			found = 1;
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	if (found)
	{
		if (prev == NULL) // data found at head
			ll->head = ll->head->next;
		else
		{
			prev->next = temp->next;
		}
		free(temp);
		return 1;
	}

	else
		return 0;
}

// insert value to the end of the list
void append(LinkedList *ll, void *value)
{
	Node *n = _makeNode(value, ll->elemSize);

	Node *ptr = _findPrevToLastNode(ll);
	if (ptr != NULL)
	{
		ptr->next->next = n;
	}
	else
	{						  // linked list has one or zero node
		if (ll->head == NULL) // has no node
		{
			ll->head = n;
		}
		else
		{ // has one node
			ll->head->next = n;
		}
	}
	ll->length++;
}

// insert value to the beginning of the list
void prepend(LinkedList *ll, void *value)
{
	Node *n = _makeNode(value, ll->elemSize);
	n->next = ll->head;
	ll->head = n;
	ll->length++;
}

void printIntList(LinkedList *ll)
{
	Node *ptr = ll->head;
	while (ptr != NULL)
	{
		printf("%d ", *((int *)ptr->data));
		ptr = ptr->next;
	}
	printf("\n");
}
// returns 1 if data is in the list, else 0
int find(LinkedList *ll, void *data)
{
	Node *ptr = ll->head;
	while (ptr != NULL)
	{
		if (ll->comparator(ptr->data, data) == 0)
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

int compareInt(const void *a, const void *b)
{
	return *((int *)a) - *((int *)b);
}

Node *nodeAtIndex(LinkedList *ll, int i)
{
	assert(i >= 0 && i <= ll->length - 1);
	Node *temp = ll->head;
	int cnt = 0;
	while (cnt < i)
	{
		temp = temp->next;
		cnt++;
	}
	return temp;
}

// deletes element at index i (0 indexed)
void deleteAtIndex(LinkedList *ll, int i)
{
	assert(i >= 0 && i <= ll->length - 1);

	Node *temp = ll->head;
	Node *prevTemp = NULL;
	if (i == 0)
	{
		ll->head = ll->head->next;
	}
	else
	{
		/*
        int cnt = 0;

        while (cnt < i)
        {
            prevTemp = temp;
            temp = temp->next;
            cnt++;
        }
        prevTemp->next = temp->next;
        */
		Node *prev = nodeAtIndex(ll, i - 1);
		temp = prev->next;

		prev->next = temp->next;
	}
	ll->length--;
	free(temp);
}

trie_node_t *getNode(void)
{
	trie_node_t *pNode = NULL;

	pNode = (trie_node_t *)malloc(sizeof(trie_node_t));

	if (pNode)
	{
		int i;

		pNode->value = 0;

		for (i = 0; i < ALPHABET_SIZE; i++)
		{
			pNode->children[i] = NULL;
		}
	}

	return pNode;
}

void initialize(trie_t *pTrie)
{
	pTrie->root = getNode();
	pTrie->count = 0;
}

void insert(trie_t *pTrie, char key[])
{
	int level;
	int length = strlen(key);
	int index;
	trie_node_t *pCrawl;

	pTrie->count++;
	pCrawl = pTrie->root;

	for (level = 0; level < length; level++)
	{
		index = INDEX(key[level]);

		if (pCrawl->children[index])
		{
			// Skip current node
			pCrawl = pCrawl->children[index];
		}
		else
		{
			// Add new node
			pCrawl->children[index] = getNode();
			pCrawl = pCrawl->children[index];
		}
	}

	// mark last node as leaf (non zero)
	pCrawl->value = pTrie->count;
}

int search(trie_t *pTrie, char key[])
{
	int level;
	int length = strlen(key);
	int index;
	trie_node_t *pCrawl;

	pCrawl = pTrie->root;

	for (level = 0; level < length; level++)
	{
		index = INDEX(key[level]);

		if (!pCrawl->children[index])
		{
			return 0;
		}

		pCrawl = pCrawl->children[index];
	}

	return (0 != pCrawl && pCrawl->value);
}

int leafNode(trie_node_t *pNode)
{
	return (pNode->value != 0);
}

int isItFreeNode(trie_node_t *pNode)
{
	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
	{
		if (pNode->children[i])
			return 0;
	}

	return 1;
}

bool deleteHelper(trie_node_t *pNode, char key[], int level, int len)
{
	if (pNode)
	{
		// Base case
		if (level == len)
		{
			if (pNode->value)
			{
				// Unmark leaf node
				pNode->value = 0;

				// If empty, node to be deleted
				if (isItFreeNode(pNode))
				{
					return true;
				}

				return false;
			}
		}
		else // Recursive case
		{
			int index = INDEX(key[level]);

			if (deleteHelper(pNode->children[index], key, level + 1, len))
			{
				// last node marked, delete it
				FREE(pNode->children[index]);

				// recursively climb up, and delete eligible nodes
				return (!leafNode(pNode) && isItFreeNode(pNode));
			}
		}
	}

	return false;
}

void deleteKey(trie_t *pTrie, char key[])
{
	int len = strlen(key);

	if (len > 0)
	{
		deleteHelper(pTrie->root, key, 0, len);
		pTrie->count--;
	}
}

int findAKey(trie_t *pTrie, char *buffer)
{
	//char *buffer = (char *)malloc(1000 * sizeof(char));
	trie_node_t *pCrawl;

	pCrawl = pTrie->root;
	int len = 0;
	if (pTrie->count != 0)
	{
		while (1)
		{
			int found = 0;
			int index = 0;
			for (int i = 0; i < 26; i++)
			{

				if (pCrawl->children[i])
				{
					buffer[len++] = 'a' + i;
					index = i;
					found = 1;
					break;
				}
			}
			if (found != 1) // stop search
			{
				buffer[len] = 0; // insert null char
				break;
			}
			else
			{
				pCrawl = pCrawl->children[index]; // go to next
			}
		}
	}
	else
		return 0;

	return 1;
}

typedef struct PAIR
{
	int llIndex;
	int trieIndex;
} Pair;

typedef struct TRIEPAIR
{
	trie_t trie[2];
} TriePair;

// given a trie prints all its values
// but deletes the values be careful
void printValues(trie_t *t)
{
	char buffer[MAX_STRING_LENGTH];
	while (1)
		if (findAKey(t, buffer))
		{
			printf("%s ", buffer);
			deleteKey(t,buffer);
		}
		else
			break;
	printf("\n");
}

// search function
// given a word
// returns a pair of index in the list and which trie of the pair
Pair searchInSet(LinkedList* ll, char* word)
{
	Node* ptr = ll->head;
	Pair p;
	p.llIndex = -1;
	int counter = 0;
	while(ptr != NULL)
	{
		TriePair* tp = (TriePair*)ptr->data;
		//printf("Searching for %s in ll: %d\n",word,counter);
		if(search(&(tp->trie[0]),word))
		{
			p.llIndex = counter;
			p.trieIndex = 0;
			return p;
		}
		else if(search(&(tp->trie[1]),word))
		{
			p.llIndex = counter;
			p.trieIndex = 1;
			return p;
		}
		counter++;
		ptr= ptr->next;
	}

	return p;
}

// merge function
// given 2 tries deletes words from trie 1 and merges into trie 2
void trieMerge(trie_t* t1, trie_t* t2)
{
	char buffer[MAX_STRING_LENGTH];
	while (1)
		if (findAKey(t1, buffer))
		{
			//printf("%s", buffer);
			insert(t2,buffer);
			deleteKey(t1,buffer);
		}
		else
			break;
}

void masterPrint(LinkedList* ll)
{
	Node* ptr = ll->head;
	Pair p;
	p.llIndex = -1;
	int counter = 0;
	while(ptr != NULL)
	{
		printf("Node: %d\n",counter);
		TriePair* tp = (TriePair*)ptr->data;
		printf("Trie 0\n");
		printValues(&(tp->trie[0]));
		
		printf("Trie 1\n");
		printValues(&(tp->trie[1]));
		
		counter++;
		ptr= ptr->next;
		printf("\n");
	}
}
void strlower(char* s)
{
	while(*s)
	{
		*s = tolower(*s);
		s++;
	}
}

void doTheSearchAndOtherStuff(LinkedList* ll,char* s1,char* s2)
{
	Pair p1 = searchInSet(ll,s1);
	Pair p2 = searchInSet(ll,s2);

	// any of the words is not present
	if(p1.llIndex == -1 || p2.llIndex == -1)
	{
		printf("Word not in dict\n");
	}else{
		//SYNONYM, ANTONYM or NEITHER
		if(p1.llIndex == p2.llIndex) // they belong to the same set
		{
			if(p1.trieIndex == p2.trieIndex)
				printf("SYNONYM\n");
			else	
				printf("ANTONYM\n");
		}else{ // different set
			printf("NEITHER\n");
		}
	}
}
int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		printf("invalid input\nformat: ./<progName> <dictionary_filename> <word1> <word2>");
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	//FILE *fp = fopen("dict", "r");
	//printf("%s",argv[1]);
	assert(fp != NULL);

	// init linkedlist of twotries
	LinkedList *ll = initLinkList(NULL, sizeof(TriePair));

	char c;
	char word1[MAX_STRING_LENGTH];
	char word2[MAX_STRING_LENGTH];
	char ch;
	while (fscanf(fp, "%c%s%s",&c,word1,word2) != EOF)
	{
		fscanf(fp,"%c",&ch);
		strlower(&word1);
		strlower(&word2);
		
		//printf("%c %s %s\n",c,word1,word2);
		
		// check for word1 in the synonym lists
		// p1.llIndex = index in linked list of word 1
		// p2.llIndex = ..
		Pair p1 = searchInSet(ll,word1);
		Pair p2 = searchInSet(ll,word2);
		if(c=='+') // synonym
		{
			// if both not found (i==-1 && j==-1)
			// add them as a new node
			if(p1.llIndex == -1 && p2.llIndex == -1)
			{
				TriePair* tp = (TriePair*)malloc(sizeof(TriePair));
				initialize(&(tp->trie[0]));
				initialize(&(tp->trie[1]));
				insert(&(tp->trie[0]),word1);
				insert(&(tp->trie[0]),word2);
				prepend(ll,(void*)tp);
			}
			// if both found in list i and j respectively
			// if i != j
			// extract word from j and put in i (both normal and opposite)
			else if(p1.llIndex != -1 && p2.llIndex != -1)
			{
				Node* n1 = nodeAtIndex(ll,p1.llIndex);
				Node* n2 = nodeAtIndex(ll,p2.llIndex);
				TriePair* tp1 = (TriePair*)n1->data;
				TriePair* tp2 = (TriePair*)n2->data;
				trieMerge(&(tp1->trie[p1.trieIndex]),&(tp2->trie[p2.trieIndex]));
				trieMerge(&(tp1->trie[1-p1.trieIndex]),&(tp2->trie[1-p2.trieIndex]));
				
				// delete the ll node
				deleteAtIndex(ll,p1.llIndex);
			}
			// if any of them is found
			// add the other into the list containing the found one
			else
			{
				int listIndex = -1;
				int trieIndex = -1;
				char* foundWord = NULL;
				char* absentWord = NULL;
				if(p1.llIndex != -1) // word 1 is found only
				{
					listIndex = p1.llIndex;
					trieIndex = p1.trieIndex;
					foundWord = word1;
					absentWord = word2;
				}
				else // only word 2 is found
				{
					listIndex = p2.llIndex;
					trieIndex = p2.trieIndex;
					foundWord = word2;
					absentWord = word1;
				}
				Node* n = nodeAtIndex(ll,listIndex);
				TriePair* tp = (TriePair*)n->data;
				insert(&(tp->trie[trieIndex]),absentWord);
			}
			
		}
		else
		{
			// find i,j like prev
			// both not found add a new one
			if(p1.llIndex == -1 && p2.llIndex == -1)
			{
				TriePair* tp = (TriePair*)malloc(sizeof(TriePair));
				initialize(&(tp->trie[0]));
				initialize(&(tp->trie[1]));
				insert(&(tp->trie[0]),word1);
				insert(&(tp->trie[1]),word2);
				prepend(ll,(void*)tp);
			}
			
			// both found
			// i != j
			// if found in linked list i and 0 th pair
			// j found in oth trie then merge i[0],j[1] and j[0],i[1]
			// then merge
			else if(p1.llIndex != -1 && p2.llIndex != -1)
			{
				Node* n1 = nodeAtIndex(ll,p1.llIndex);
				Node* n2 = nodeAtIndex(ll,p2.llIndex);
				TriePair* tp1 = (TriePair*)n1->data;
				TriePair* tp2 = (TriePair*)n2->data;
				trieMerge(&(tp1->trie[p1.trieIndex]),&(tp2->trie[p2.trieIndex]));
				trieMerge(&(tp1->trie[1-p1.trieIndex]),&(tp2->trie[1-p2.trieIndex]));
				
				// delete the ll node
				deleteAtIndex(ll,p1.llIndex);
			}
			// one found other not found
			// put the other in the reverse trie of one
			else
			{
				int listIndex = -1;
				int trieIndex = -1;
				char* foundWord = NULL;
				char* absentWord = NULL;
				if(p1.llIndex != -1) // word 1 is found only
				{
					listIndex = p1.llIndex;
					trieIndex = p1.trieIndex;
					foundWord = word1;
					absentWord = word2;
				}
				else // only word 2 is found
				{
					listIndex = p2.llIndex;
					trieIndex = p2.trieIndex;
					foundWord = word2;
					absentWord = word1;
				}
				Node* n = nodeAtIndex(ll,listIndex);
				TriePair* tp = (TriePair*)n->data;
				insert(&(tp->trie[1-trieIndex]),absentWord);
			}
		}
		
	}
	char s1[MAX_STRING_LENGTH];
	char s2[MAX_STRING_LENGTH]; 
	
	strcpy(s1,argv[2]);
	strcpy(s2,argv[3]);
	
	strlower(s1);
	strlower(s2);
	doTheSearchAndOtherStuff(ll,s1,s2);
	//masterPrint(ll);
	return 0;
}