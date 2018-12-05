/*
* Rahul Gautam
* Indian Statistial Institute M.Tech(CS)
* Iterative inorder,Preorder and postorder traversals of tree
* Postorder and inorder uses O(n) extra space
* Broad description for problem: = https://www.isical.ac.in/~dfslab/2018/exams/lab-test2.pdf
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {

	void *elements;
	int element_size, num_elements, max_elements;
} STACK;



STACK* newStack(int element_size,int maxSize)
{
	STACK* s = (STACK*)malloc(sizeof(STACK));
	if(s != NULL)
	{
		s->element_size = element_size;
		s->num_elements = 0;
		s->max_elements = maxSize;
		s->elements = malloc(s->max_elements*element_size);
	}
	return s;
}

// pushes eptr to the top of stack
void push(STACK *s, const void *eptr)
{
	if(s->num_elements < s->max_elements) // check for full condition
	{
		char* stackElementAddress = (char*) s->elements + s->num_elements*s->element_size;
		memcpy(stackElementAddress, eptr, s->element_size);
		s->num_elements++;

		//printf("[push]address = %u num elm = %d\n",stackElementAddress,s->num_elements );
	}
		
}

// dequeue
void dequeue(STACK* s,void *eptr)
{
	if(s->num_elements > 0)
	{
		memcpy(eptr, s->elements, s->element_size);
		s->num_elements--;
		s->elements = (char*)s->elements + s->element_size;
		//printf("[dequeue]address = %u num elm = %d\n",s->elements,s->num_elements );
	}
}

void pop(STACK *s, void *eptr)
{
	if(s->num_elements > 0)
	{
		char* stackElementAddress = (char*) s->elements + (s->num_elements-1)*s->element_size; 
		memcpy(eptr, stackElementAddress, s->element_size);
		s->num_elements--;

		//printf("[pop]address = %u num elm = %d\n",stackElementAddress,s->num_elements );
	}

} 

typedef struct 
{
    int n;
    int l;
    int r;
}TreeNode;

void preorder(TreeNode* tree,int n)
{
    if(n>0)
    {
        STACK* s = newStack(sizeof(int),n);
        int root = 0;
        push(s,(void*)&root);// push root

        while(s->num_elements != 0)
        {
            //pop the top element from stack and print its value
            int topIndex;
            pop(s,(void*)&topIndex);
            printf("%d ",tree[topIndex].n);
            // if right child is not null push its index to the stack
            if(tree[topIndex].r != -1)
                push(s,(void*)&(tree[topIndex].r));
            // do the same for leftchild
            if(tree[topIndex].l != -1)
                push(s,(void*)&(tree[topIndex].l));
        }
    }
    printf("\n");
}

typedef struct{
    int index;
    int processed;
}Pair;
void inOrder(TreeNode* tree,int n)
{
    if(n>0)
    {
        STACK* s = newStack(sizeof(Pair),n);
        Pair root;
        root.index = 0;
        root.processed = 0;
        push(s,(void*)&root);// push root

        while(s->num_elements != 0)
        {
            Pair topIndex;
            pop(s,(void*)&topIndex);

            if(topIndex.processed) // push its right children
            {
                printf("%d ",tree[topIndex.index].n);

                // if right child is not null push its index to the stack
                if(tree[topIndex.index].r != -1)
                {
                    Pair p;
                    p.index = tree[topIndex.index].r;
                    p.processed = 0;
                    push(s,(void*)&(p));

                }
            
            }
            else
            {
                topIndex.processed = 1;
                push(s,(void*)&(topIndex));
                
                // push its left child
                if(tree[topIndex.index].l != -1)
                {
                    Pair p;
                    p.index = tree[topIndex.index].l;
                    p.processed = 0;
                    push(s,(void*)&(p));
                
                }

            }
        }
    }
    printf("\n");
}
void postOrder(TreeNode* tree,int n)
{
    if(n>0)
    {
        STACK* s = newStack(sizeof(Pair),n);
        Pair root;
        root.index = 0;
        root.processed = 0;
        
        push(s,(void*)&root);// push root

        while(s->num_elements != 0)
        {
            //pop the top element from stack 
            // if its not already processd mark it as processed and push back and also push its right and left children
            // if its already processed print its value
            Pair topIndex;
            pop(s,(void*)&topIndex);
            if(topIndex.processed)
                printf("%d ",tree[topIndex.index].n);
            else
            {
                topIndex.processed = 1;
                push(s,(void*)&(topIndex));
                // if right child is not null push its index to the stack
                if(tree[topIndex.index].r != -1)
                {
                    Pair p;
                    p.index = tree[topIndex.index].r;
                    p.processed = 0;
                    push(s,(void*)&(p));

                }
                // do the same for leftchild
                if(tree[topIndex.index].l != -1)
                {
                    Pair p;
                    p.index = tree[topIndex.index].l;
                    p.processed = 0;
                    push(s,(void*)&(p));
                
                }

            }
        }
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d",&n);

    TreeNode* tree = malloc(n*sizeof(TreeNode));

    for(int i=0;i<n;i++)
    {
        int val,l,r;

        scanf("%d%d%d",&val,&l,&r);
        tree[i].n = val;
        if(l!= -1)
            tree[i].l = l-2;
        else
            tree[i].l = -1;

        if(r!= -1)    
            tree[i].r = r-2;
        else
            tree[i].r = -1;

        //printf("**%d %d %d\n",tree[i].n,tree[i].l,tree[i].r);
    }

    preorder(tree,n);
    inOrder(tree,n);
    postOrder(tree,n);

    return 0;
}