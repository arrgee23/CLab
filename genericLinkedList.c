/*
* Rahul Gautam
* Indian Statistical Institute
* 4-Oct-2018
* Implementation of generic linked list
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

static Node* _makeNode(void *data, size_t size)
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
int findValue(LinkedList* ll,void* value)
{
    if(ll->length)
        return 0;
    // search for the value
    int count =0;
    Node* temp = ll->head;

    while(temp!=NULL )
    {
        if(ll->comparator(temp->data,value)== 0)
            count++;
        temp = temp->next;
    }
    return count;

}
// deletes the 1st occurance of value, returns 1 if successful, else 0
int deleteValue(LinkedList* ll,void* value)
{
    if(!ll->length)
        return 0;

    // search for the value
    int found = 0;
    Node* temp = ll->head;
    Node* prev = NULL;
    while(temp!=NULL )
    {
        if(ll->comparator(temp->data,value)== 0)
        {
            found = 1;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    if(found)
    {
        if(prev == NULL) // data found at head
            ll->head = ll->head->next;
        else{
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
    {                         // linked list has one or zero node
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

Node* nodeAtIndex(LinkedList *ll, int i)
{
    assert(i >= 0 && i <= ll->length - 1);
    Node *temp = ll->head;
    int cnt = 0;
    while(cnt<i)
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
        Node* prev = nodeAtIndex(ll,i-1);
        temp = prev->next;
        
        prev->next = temp->next;
    }
    ll->length--;
    free(temp);
}

int main()
{
    LinkedList *ll = initLinkList(compareInt, sizeof(int));
    //printIntList(ll);

    int a = 3;
    prepend(ll, (void *)&a);
    //printIntList(ll);
    a = 5;
    prepend(ll, (void *)&a);
    ///printIntList(ll);
    a = 7;
    prepend(ll, (void *)&a);

    /*
    printIntList(ll);
    deleteAtIndex(ll,1);
    printIntList(ll);
    deleteAtIndex(ll,1);
    printIntList(ll);
    deleteAtIndex(ll,0);
    printIntList(ll);
    */

    printIntList(ll);
    int j = 5;
    deleteValue(ll,(void*)&j);
    printIntList(ll);
    
    j = 5;
    deleteValue(ll,(void*)&j);
    printIntList(ll);
    
    j = 7;
    deleteValue(ll,(void*)&j);
    printIntList(ll);
    j = 3;
    deleteValue(ll,(void*)&j);
    printIntList(ll);

    
    //int k = 7;
    //printf("\n%d\n", find(ll, (void *)&k));
}
