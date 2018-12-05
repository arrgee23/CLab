/*
* Rahul Gautam
* CS 1835
* Leaky stack implementaion. after every L numbers of push and pop the last Items leaks out
* Broad description for problem: = https://www.isical.ac.in/~dfslab/2018/exams/lab-test2.pdf
*/

typedef struct {

	void *elements;
	int element_size, num_elements, max_elements;
    int l;
	int leakIndex;
} STACK;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


STACK* newStack(int element_size,int maxSize,int l)
{
	STACK* s = (STACK*)malloc(sizeof(STACK));
	if(s != NULL)
	{
		s->element_size = element_size;
		s->num_elements = 0;
		s->max_elements = maxSize;
		s->elements = malloc(s->max_elements*element_size);
        s->l = l;
		s->leakIndex = 0;
	}
	return s;
}

// dequeue
void leak(STACK* s)
{
	if(s->num_elements > 0)
	{
		//memcpy(eptr, s->elements, s->element_size);
		s->num_elements--;
		// shift all elements to the left
		memcpy((char*)s->elements,(char*)s->elements+s->element_size,s->num_elements*s->element_size);
		//s->elements = (char*)s->elements + s->element_size;
		//printf("[dequeue]address = %u num elm = %d\n",s->elements,s->num_elements );
	}
}


// pushes eptr to the top of stack
void push(STACK *s, const void *eptr)
{
	if(s->num_elements < s->max_elements) // check for full condition
	{
		char* stackElementAddress = (char*) s->elements + s->num_elements*s->element_size;
		memcpy(stackElementAddress, eptr, s->element_size);
		s->num_elements++;
		// check for leak condition

		//printf("[push]address = %u num elm = %d\n",stackElementAddress,s->num_elements );
	}
	if(s->l>0)
	{
		s->leakIndex++;

		if(s->leakIndex == s->l)
		{
			s->leakIndex = 0;
			leak(s);
		}
	}
}


void pop(STACK *s)
{
	if(s->num_elements > 0)
	{
		//char* stackElementAddress = (char*) s->elements + (s->num_elements-1)*s->element_size; 
		//memcpy(eptr, stackElementAddress, s->element_size);
		s->num_elements--;

		//printf("[pop]address = %u num elm = %d\n",stackElementAddress,s->num_elements );
	}
	if(s->l>0 )
	{
		s->leakIndex++;

		if(s->leakIndex == s->l)
		{
			s->leakIndex = 0;
			leak(s);
		}
	}

} 
void print(STACK* s)
{
	int* arr = (int*)s->elements;

	for(int i=s->num_elements-1;i>=0;i--)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int main()
{
    int stackSize = 0; 
    int leak = 0;

    scanf("%d %d ",&stackSize,&leak);

	if(stackSize>0)
	{
		STACK* ss = newStack(sizeof(int),stackSize,leak);

		char symbol = 0;
		int value = 0;

		//printf("elmSize=%d l=%d stackSize = %d elemNum=%d\n",ss->element_size,ss->l,ss->max_elements,ss->num_elements);
		while(1)
		{
			scanf("%c",&symbol);
			
			// c is the termination element
			if(symbol == 'c')
				break;
			if(symbol == '+') // pushing in the stack
			{
				scanf("%d",&value);
				push(ss,(void*)&value);
				print(ss);
				//fflush(stdin);
				//printf("%d\n",value);
			}
			else if(symbol == '-')
			{
				pop(ss);
				print(ss);
				//printf("* \n",value);
			}
		}
	}else
	{
		printf("StackSize<=0 no operation possible.. terminating..\n");
	}
	return 0;
}
