/*
* Rahul Gautam
* Indian Statitical Institute
* Implementation of a generic stack
* And also queue. Because why not?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE 255
typedef struct {
	void *elements;
	int element_size, num_elements, max_elements;
	int queueFront,queueRear; // only used when making queue
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

STACK* newQueue(int element_size,int maxSize)
{
	STACK* s = (STACK*)malloc(sizeof(STACK));
	if(s != NULL)
	{
		s->element_size = element_size;
		s->num_elements = 0;
		s->max_elements = maxSize;
		s->elements = malloc(s->max_elements*element_size);
		s->queueFront = 0;
		s->queueRear = s->max_elements - 1;
	}
	return s;
}

int isFull(STACK* s)
{
	if(s!=NULL)
	{
		return s->max_elements == s->num_elements ? 1:0;
	}
	else
		assert(0);
}

int isEmpty(STACK* s)
{
	if(s!=NULL)
	{
		return 0 == s->num_elements ? 1:0;
	}
	else
		assert(0);
}

// pushes eptr to the top of stack conceptually
// actually puts to end
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

// enqueue
void enqueue(STACK *s, const void *eptr)
{
	if(!isFull(s)) // check for full condition
	{
		//printf("rear = %d max = %d\n",s->queueRear,s->max_elements);
		s->queueRear = (s->queueRear + 1)%s->max_elements;
		//printf("insert at = %d\n",s->queueRear);
		char* stackElementAddress = (char*) s->elements + s->queueRear*s->element_size;
		memcpy(stackElementAddress, eptr, s->element_size);
		s->num_elements++;

		//printf("[enqueue]address = %u num elm = %d\n",stackElementAddress,s->num_elements );
	}	
}

// dequeue
void dequeue(STACK* s,void *eptr)
{
	if(!isEmpty(s))
	{
		char* stackElementAddress = (char*) s->elements + s->queueFront*s->element_size;
		//printf("Delete from = %d\n",s->queueFront);
		memcpy(eptr, stackElementAddress, s->element_size);
		s->queueFront = (s->queueFront + 1)%s->max_elements;
		s->num_elements--;
		//printf("[dequeue]address = %u num elm = %d\n",stackElementAddress,s->num_elements );
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

int main()
{
	STACK* ss = newQueue(sizeof(float),10);
	float a = 3;
	float b = 5;

	int dummy = 0;
	for(int i=0;i<10;i++)
	{
		enqueue(ss,(void*)&i);

		dequeue(ss,(void*)&dummy);
		printf("%d\n",dummy);
	}

	for(int i=0;i<6;i++)
		enqueue(ss,(void*)&i);
	for(int i=0;i<6;i++)
	{
		dequeue(ss,(void*)&dummy);
		printf("%d\n",dummy);
	}
	return 0;
}
