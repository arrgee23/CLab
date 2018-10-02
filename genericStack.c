/*
* Rahul Gautam
* CS 1835
* Implementation of ageneric stack
* And also queue. Because why not?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

	void *elements;
	int element_size, num_elements, max_elements;
} STACK;


#define SIZE 255

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

int main()
{
	STACK* ss = newStack(sizeof(int),100);
	float a = 3;
	float b = 5;

	float dummy = 0;

	push(ss,(void*)&a);
	push(ss,(void*)&b);

	dequeue(ss,(void*)&dummy);
	printf("%f\n",dummy);

	dequeue(ss,(void*)&dummy);
	printf("%f\n",dummy);

	return 0;
}
