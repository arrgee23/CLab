/*
* Rahul Gautam
* Indian Statistical Institute
* Assignment 3 problem 2
* Scheduling processes 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define QUANTUM_SMALL 6
#define QUANTUM_BIG 8
#define SCHEDULE_TOTAL 40
#define PROCESS_NAME_SIZE 256

typedef struct PROCESS
{
    int et;
    char id[PROCESS_NAME_SIZE];
} Process;

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

typedef struct PAIR
{
    int x;
    int y;
} Pair;

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

void printProcessList(LinkedList *ll)
{
    Node *ptr = ll->head;
    while (ptr != NULL)
    {
        Process *p = (Process *)ptr->data;
        printf("(%s %d)", p->id, p->et);
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
    while (cnt++ < i)
        temp = temp->next;

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
    free(temp->data);
    free(temp);
}

Pair execute(LinkedList **q, int startWith)
{
    int time = 0;
    int pExecuted[2]; // number of executed process for each queue
    pExecuted[0] = 0;
    pExecuted[1] = 0;
    int idleTime = 0;

    int i = 0;
    if (startWith == 1)
    {
        i = 1;
    }

    //printProcessList(q[0]);
    //printProcessList(q[1]);

    // while there is still time and process to execute
    int fLastCycle = 0;
    while (time < SCHEDULE_TOTAL && (q[i]->length > 0 || q[1 - i]->length > 0))
    {
        int fProcessExecuted = 0;
        int duration = QUANTUM_SMALL;
        if (pExecuted[1 - i] > pExecuted[i])
        {
            duration = QUANTUM_BIG;
        }
        /*
        if(duration >= SCHEDULE_TOTAL-time)
        {
            duration = SCHEDULE_TOTAL-time;
            fLastCycle = 1;
        }
        */

        // try to schedule process from ith queue
        if (q[i]->length > 0)
        {
            // schedule all the process that can be scheduled
            while (q[i]->length > 0)
            {
                // get the 1st process
                Node *head = nodeAtIndex(q[i], 0);
                Process *headProcess = (Process *)head->data;
                if (headProcess->et <= duration)
                {
                    duration -= headProcess->et;
                    time += headProcess->et;

                    if (time <= SCHEDULE_TOTAL)
                    {
                        //printf("time=%d %s(%d) executed[%d]=%d", time, headProcess->id, headProcess->et, i, pExecuted[i] + 1);
                        pExecuted[i]++;
                        fProcessExecuted = 1;
                    }
                    //printf("\n");
                    // delete process
                    deleteAtIndex(q[i], 0);
                    //printf("\nAfter deletion of front: ");
                    //printProcessList(q[i]);
                }
                else
                {
                    break;
                }
            }
            if (duration > 0 && q[i]->length > 1) // if still time remaining and the next process cant be scheduled,a nd atleast 2 process in the queue
            {
                Node *head = nodeAtIndex(q[i], 0);
                Process *headProcess = (Process *)head->data;
                Node *headNext = nodeAtIndex(q[i], 1);
                Process *process2nd = (Process *)headNext->data;

                /*
                    If the cumulative execution time of this process and its immediate successor in FCFS order
                    is more than 8 units, then out of the two processes, the one with higher execution time is
                    demoted to the end of the queue Q i . If both have equal execution time, the one with the
                    lower process id is demoted to the end of the queue.
                */
                if (headProcess->et + process2nd->et > QUANTUM_BIG)
                {
                    int demotionIndex = -1;
                    Node *demotionNode = NULL;

                    if (headProcess->et > process2nd->et)
                    {
                        demotionIndex = 0;
                        demotionNode = head;
                    }
                    else if (headProcess->et < process2nd->et)
                    {
                        demotionIndex = 1;
                        demotionNode = headNext;
                    }
                    else // both et is equal
                    {
                        if (strcmp(headProcess->id, process2nd->id) < 0)
                        {
                            demotionIndex = 0;
                            demotionNode = head;
                        }
                        else
                        {
                            demotionIndex = 1;
                            demotionNode = headNext;
                        }
                    }

                    assert(demotionIndex != -1 || demotionNode != NULL);

                    // demote the selected process to the end of the list
                    append(q[i], (void *)((Process *)demotionNode->data));
                    deleteAtIndex(q[i], demotionIndex);

                    //printf("\nafter reorder: ");
                    //printProcessList(q[i]);
                    //printf("\n");
                }
                // assuming after rescheduling we dont use the remaining time to schedule process in same queue
                if (time < SCHEDULE_TOTAL)
                    if (duration != 0)
                    {
                        time += duration;

                        if (fProcessExecuted )
                        {
                            
                            idleTime += duration;
                            if(time>SCHEDULE_TOTAL)
                                idleTime -= time-SCHEDULE_TOTAL; 
                            //printf("time=%d idle(%d)", time, duration);
                        }
                    }
                //printf(" \n");
            }
        }

        // if the other queue is not exhausted
        if (q[1 - i]->length > 0)
            i = 1 - i; // switch between processes
    }
    printf("%d %d\n", pExecuted[0] + pExecuted[1], idleTime);
    Pair p;
    p.x = pExecuted[0] + pExecuted[1];
    p.y = idleTime;
    return p;
}
int compareProcess(const void *p1, const void *p2)
{
    return 0;
}

int main()
{
    int n0, n1;

    scanf("%d%d", &n0, &n1);
    //Process q0[n0];
    //Process q1[n1];
    LinkedList *q[2];
    q[0] = initLinkList(compareProcess, sizeof(Process));
    q[1] = initLinkList(compareProcess, sizeof(Process));

    LinkedList *bkup[2];
    bkup[0] = initLinkList(compareProcess, sizeof(Process));
    bkup[1] = initLinkList(compareProcess, sizeof(Process));

    int i = 0;
    for (i = 0; i < n0; i++)
    {
        Process temp;
        scanf("%s%d", temp.id, &temp.et);
        append(q[0], (void *)&temp);
        append(bkup[0], (void *)&temp);
    }

    for (i = 0; i < n1; i++)
    {
        Process temp;
        scanf("%s%d", temp.id, &temp.et);
        append(q[1], (void *)&temp);
        append(bkup[1], (void *)&temp);
    }
    Pair idleTime0 = execute(q, 0);
    Pair idleTime1 = execute(bkup, 1);

    if (idleTime0.x > idleTime1.x)
        printf("Option 1 is better than Option 2\n");
    else if (idleTime0.x < idleTime1.x)
        printf("Option 2 is better than Option 1\n");
    else
    {
        if (idleTime0.y > idleTime1.y)
            printf("Option 2 is better than Option 1\n");
        else if (idleTime0.y < idleTime1.y)
            printf("Option 1 is better than Option 2\n");
        else
            printf("Both Option 1 and 2 are equally good\n");
    }
    return 0;
}
