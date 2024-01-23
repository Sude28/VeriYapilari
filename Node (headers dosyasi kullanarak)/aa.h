#ifndef AA_H_INCLUDED
#define AA_H_INCLUDED



#endif // AA_H_INCLUDED

typedef struct node{
    void* dataPtr;   //herhangi bir turdeki veriyi isaret ediyor
    struct node* link;//sonraki struct node'u isaret ediyor
}NODE;

NODE* createNode(void* itemPtr){
    NODE* nodePtr;
    nodePtr=(NODE*)malloc(sizeof(NODE));
    nodePtr->dataPtr=itemPtr;
    nodePtr->link=NULL;
    return nodePtr;
}
