#include<stdio.h>
#include<strings.h>

/*
Tree input format
// no of nodes
 // val lc rc 
4 
1 3 4
2 5 -1
3 -1 -1 
4 -1 -1


6
2 1 2
3 3 4
5 -1 5
7 -1 -1
11 -1 -1
13 -1 -1

*/

#define DATA 0
#define LEFT 1
#define RIGHT 2

void preorder(int tree[][3], int rootIndex)
{
    // print root
    if(rootIndex != -1)
    {
        printf("%d ",tree[rootIndex][DATA]);
        // do traversal on leftchild
        preorder(tree,tree[rootIndex][LEFT]);
        // do traversal on rightchild
        preorder(tree,tree[rootIndex][RIGHT]);
    }
}

// given a value search for that value in the tree
// return 1 if found else 0

int searchInTree(int tree[][3], int value,int rootIndex)
{
    if(rootIndex != -1){
        if(rootIndex){

        }
    }
}

int main(int argc, char *argv[])
{ 
    int n;
    scanf("%d",&n);

    int tree[n][3];
   // tree[i][j] = *(tree+3i+j)
    int i;
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d",&tree[i][DATA],&tree[i][LEFT],&tree[i][RIGHT]);
    }
    preorder(tree,0);
    return 0;
}
