#include "eerTree.h"

int main()
{
    char str[2000];
    strcpy(str, "ABBA");
    eerTree *at = malloc(sizeof(eerTree));
    initTree(at, 2);

    addString(at, str, 0);
    int t = at->size;
    char str2[2000];
    strcpy(str2, "TAT");

    addString(at, str2, 1);
    char *strArray[] = {str, str2};
    printStrings(at, strArray);

    return 0;
}