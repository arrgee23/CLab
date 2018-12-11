/*
* Rahul Gautam
* Indian Statistical Institute
* CS1835
* 09-Dec-2018
* Implementation of Bloom Filter

* Build Instruction: 
gcc cs1835-assign4-prog3-jqq3m4e.c -o prog3

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define CHAR_SIZE 8

// allocates minimum size character array capable  to store m bits
// sets the value pointed by len as number of characters allocated
char *allocateMbit(int m, int *len)
{

    int k = m / CHAR_SIZE;
    char *buff = NULL;
    if (m % CHAR_SIZE)
    {
        buff = (char *)malloc((k + 1) * sizeof(char));
        *len = k + 1;
    }
    else
    {
        buff = (char *)malloc((k) * sizeof(char));
        *len = k;
    }
    int i;
    for (i = 0; i < *len; i++)
        buff[i] = 0;
    return buff;
}

// sets kth bit. returns 1 if it was previously set else o
int setKthBit(char *bitArray, int len, int k)
{
    int byteIndex = k / CHAR_SIZE;
    assert(byteIndex < len);
    int byteOffset = k % CHAR_SIZE;

    char mask[] = {1, 2, 4, 8, 16, 32, 64, 128};

    // check if that bit is set
    int ret = (bitArray[byteIndex] & mask[byteOffset])==0 ? 0:1;
    
    // set kth bit
    bitArray[byteIndex] = bitArray[byteIndex] | mask[byteOffset];

    return ret;
}

int isKthBitSet(char *bitArray, int len, int k)
{
    int byteIndex = k / CHAR_SIZE;
    assert(byteIndex < len);
    int byteOffset = k % CHAR_SIZE;

    char mask[] = {1, 2, 4, 8, 16, 32, 64, 128};

    return bitArray[byteIndex] & mask[byteOffset];
}

void printBits(char *bitArray, int len)
{
    char mask[] = {1, 2, 4, 8, 16, 32, 64, 128};
    int i, j;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (mask[j] & bitArray[i])
                printf("1");
            else
                printf("0");
        }
        printf(" ");
    }
}

double doBloomFilterCalculation(int argc, char **argv)
{
    int m = atoi(argv[1]);
    int k = atoi(argv[2]);
    int i = 0,j=0,x=0;
  
     // allocate m bit array
    int len=0;
    char* bitArray = allocateMbit(m,&len);
    
    // allocate memeory for checking inserted or duplicate
    char* checkArray = malloc((argc-3)*sizeof(char));

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    
    for (i = 3; i < argc; i++)
    {
        
        x = atoi(argv[i]);
        checkArray[i-3] = 1;
        srand(x);
        for(j=0;j<k;j++)
        {
            if(setKthBit(bitArray,len,rand()%m)==0) // atleast 1 bit was not set
            {
                checkArray[i-3]=0; // mark it as inserted
            }
        }
        
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    for(i=0;i<argc-3;i++)
    {
        if(checkArray[i]==0)
            printf("INSERTED ");
        else
            printf("DUPLICATE ");
    }
    return cpu_time_used;
}

// An AVL tree node 
struct Node 
{ 
	int key; 
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 

// A utility function to get maximum of two integers 
int max(int a, int b); 

// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

/* Helper function that allocates a new node with the given key and 
	NULL left and right pointers. */
struct Node* newNode(int key) 
{ 
	struct Node* node = (struct Node*) 
						malloc(sizeof(struct Node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, int key,int* isInserted) 
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) 
    {
        *isInserted = 1; 
		return(newNode(key));
        
    }
	if (key < node->key) 
		node->left = insert(node->left, key,isInserted); 
	else if (key > node->key) 
		node->right = insert(node->right, key,isInserted); 
	else // Equal keys are not allowed in BST 
    {
        *isInserted = 0;
		return node; 
    }
	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	// Right Right Case 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the (unchanged) node pointer */
	return node; 
} 

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(struct Node *root) 
{ 
	if(root != NULL) 
	{ 
		printf("%d ", root->key); 
		preOrder(root->left); 
		preOrder(root->right); 
	} 
} 

double doAVLCalculation(int argc, char** argv,int* nodesUsed)
{
    struct Node *root = NULL; 
    int isInserted = -1;
    int insertCount = 0;
    int i;
    

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    for (i = 3; i < argc; i++)
    {
        isInserted = -1;
        // insert
        root = insert(root,atoi(argv[i]),&isInserted); 
        if(isInserted==1)
            insertCount++;
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    *nodesUsed = insertCount;
    preOrder(root);
    return cpu_time_used;
}

int main(int argc, char **argv)
{
    /*
    int len = 0;
    char *bitArray = allocateMbit(atoi(argv[1]),&len);
    setKthBit(bitArray,len,atoi(argv[2]));
    printBits(bitArray,len);
    printf("\n%d\n",isKthBitSet(bitArray,len,atoi(argv[3])));
    */
    double bloomTime = doBloomFilterCalculation(argc, argv);
    int nodeCount;
    double avlTime = doAVLCalculation(argc, argv,&nodeCount);
    
    printf("\n%lf\n",bloomTime);
    printf("\n%lf\n",avlTime);
    printf("%d\n",nodeCount);

    return 0;
}