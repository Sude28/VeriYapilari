#include <stdio.h>
#include <stdlib.h>
#include "aa.h"

int main()
{
    int* newData;
    int* nodeData;

    NODE* node;

    newData=(int*)malloc(sizeof(int));
    *newData=7;
    node=createNode(newData);
    nodeData=(int*)node->dataPtr;
    printf("Data from node: %d\n",*nodeData); //node icindeki veri kismi
    printf("Data from node: %d\n",&nodeData); //node icindeki link yani sonraki node'un adresi
    printf("Data from node: %d\n",nodeData);  //node'un kendi adresi

    return 0;
}
