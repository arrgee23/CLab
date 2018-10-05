/*
* Rahul Gautam
* Indian Statistical Institute
* 4-Oct-2018
* Implementation of generic linked list
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


typedef struct node
{
    void* data;
    struct node* next;
}Node;

typedef struct linkedList
{
    Node* head;
    size_t elemSize;
    int (*comparator)(const void*,const void*);
    int length;
}LinkedList;

Node* _makeNode(void* data,size_t size)
{
    Node* n = (Node*)malloc(sizeof(Node));
    if(n==NULL)
        assert(0);

    memcpy(n->data,data,size);
    n->next = NULL;
    
    return n;    
}

// Return empty Linked list
LinkedList* initLinkList(int (*comparator)(const void*,const void*), size_t elemSize)
{
    LinkedList* ll = (LinkedList*)malloc(sizeof(LinkedList));
    if(!ll)
        assert(0);
    
    ll->head = NULL;
    ll->elemSize = elemSize;
    ll->comparator = comparator;
    ll->length = 0;

    return ll;
}

void insert(LinkedList* ll, void* value)
{
    Node* n = _makeNode(value,ll->elemSize);
    n->next = ll->head;
    ll->head = n;
    ll->length++;
}
/*
void printIntList(LinkedList* ll)
{
    int i=0;
    Node* ptr = ll->head;

    while(ptr!=NULL)
    {
        printf("%d",*((int*)ptr->data));
        ptr = ptr->next;
    }
    printf("\n");
}
*/

int main()
{
    LinkedList* ll = initLinkList(NULL,sizeof(int));
    int a = 3;

    
    insert(ll,(void*)&a);
    a=5;
    insert(ll,(void*)&a);

    //printIntList(ll);
    
}
