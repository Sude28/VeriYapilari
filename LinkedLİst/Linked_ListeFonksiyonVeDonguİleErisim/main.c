#include <stdio.h>
#include <stdlib.h>

struct n{
    int x;
    struct n* next;

};
typedef struct n node;

void bastir(node* r){
    while(r!=NULL){  //r nulla gidene kadar dedik cunku bir sey eklemiycez sonuna kadar yazdiricaz
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
    r->next->next = NULL; //while dongusune almadik cunku hepsinde bir sonrakini null yapiyoruz sonra ekleme varsa onun yerine ekleniyor. Whilenin icinde olsaydi donguden cikardi hep

}


int main()
{
    node* root;
    root = (node*)malloc(sizeof(node));
    root->next = NULL; //her rootun sonu Null I göstermeli
    root -> x = 500;
    int i=0;
    /*node* iter;
    iter=root;*/
    for(i=0;i<5;i++){
            ekle(root,i*10);
           /* iter->next = (node*)malloc(sizeof(node)); //boyle donguyle de fonksiyonla da yapabilirz
            iter=iter->next;
            iter->x = i*10;
            iter->next = NULL;*/
    }

    bastir(root);

    return 0;
}
