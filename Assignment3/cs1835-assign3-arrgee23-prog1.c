#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define MAX_LEN_STRING 10000
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
	}
}

int findAKey(trie_t *pTrie,char* buffer)
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
			int index=0;
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

int main()
{
	char keys[][8] = {"she", "sells", "sea", "shore", "the", "by", "sheer"};
	trie_t trie;

	initialize(&trie);

	for (int i = 0; i < ARRAY_SIZE(keys); i++)
	{
		insert(&trie, keys[i]);
	}

	deleteKey(&trie, keys[0]);

	//printf("%s %s\n", "she", search(&trie, "she") ? "Present in trie" : "Not present in trie");

	char* s = (char *)malloc(MAX_LEN_STRING * sizeof(char));
	
	//while(1)
	{
		if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		}
		if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		}
		if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		}
		if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		}
		if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		}if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		}if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		} if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		} 
		if(findAKey(&trie,s))
		{
			printf("%s ", s);
			deleteKey(&trie,s);
	
		} 
		else printf("oolala\n");
			//break;
	}
	return 0;
}
