#include <stdio.h>
#include <stdlib.h>

 struct n{
    int x;
    struct n* next;

};
typedef struct n node;

void bastir(node* r){
    while(r!=NULL){
        printf("%d ",r->x);
        r=r->next;
    }
}

void ekle(node* r , int x){
    while(r->next!=NULL){
        r=r->next;
    }
    r->next = (node*)malloc(sizeof(node));
    r->next->x=x;
    r->next->next = NULL;
}


int main()
{
    node* root;
    root = (node*)malloc(sizeof(node));
    root->next = NULL;
    root -> x = 500;
    int i=0;

    for(i=0;i<5;i++){
            ekle(root,i*10);

    }
    bastir(root);

    node* iter = root; //500 0 10 20 30 *20ile30'un arasina ekliycez bu nedenle 3 tane ileri gittik
    for(i=0;i<3;i++)
        iter = iter->next;

    node* temp = (node*)malloc(sizeof(node)); //20 ile 30'un arasindaki nodeyu olusturduk ve temp isaretciini atadik
    temp->next = iter->next; //iter 20'deki pointer iterin nexti 30'daki ponter olur onu tempin nextine esitledik ki temp20 ile 30'un arasinda olsun
    iter->next=temp;
    temp->x=100;
    bastir(root);

    return 0;
}
