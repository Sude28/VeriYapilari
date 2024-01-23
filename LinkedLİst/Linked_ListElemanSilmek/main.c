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
    printf("\n");
}

node* ekleSirali(node* r,int x){  //sirali yani kucukten buyuge
    if(r==NULL){     //linked list bos ise
            r=(node*)malloc(sizeof(node));
            r->next = NULL;
            r->x = x;
            return r;
    }
    if(r->x > x){ //ilk elemandan kucuk durumu //root degisiyor benim ekledigim ilk eleman oluyor cunku
            node * temp = (node*)malloc(sizeof(node)); //kutucuk olusturduk
            temp -> x = x; //veri kismini doldurduk
            temp -> next = r; //
            return temp;
    }
    node* iter = r;
    while(iter->next!=NULL && iter->next->x < x){
        iter=iter->next;
    }
    node* temp = (node*)malloc(sizeof(node));
    temp->x =x;
    temp->next = iter->next ;
    iter->next = temp;

    return r;
}

node* sil(node* r,int x){   //silinecek dugum bastaki dugum olabilir bu nedenle root u kaybetmemek icin node* dondururuz.
       node* temp;   //free yapmak icin gerekli
       node* iter=r;   //silinecekten bir oncekini gostermek icin gerekli. Silinecekten sonraki ile baglantiyi saglamak icin gerekli.

       if(r->x == x){ //silinecek dugum basta ise
               temp = r; //free edebilmek icin temp onu tutsun dedik
               r=r->next; //root artik bir sonrakini gosteriyor
               free(temp); //free ediyoruz ilkini
               return r;

       }

       while(iter->next != NULL && iter->next->x != x){
            iter=iter->next;
       }

       if(iter->next==NULL){
           printf("Sayi bulunamadi\n");
           return r;
       }
       temp=iter->next;
       iter->next=iter->next->next;
       free(temp);
       return r;

}


int main()
{
    node* root;
    root = NULL;
    root = ekleSirali(root,400); //ilk basta root 400'u gosteriyor ama 40 ondan kucuk basa o gecince onu gosteriyor sonra 4 geciyor gibi boylece root degisiyor hep bu nedenle return ediyoruz
    root = ekleSirali(root,40);
    root = ekleSirali(root,4);
    root = ekleSirali(root,450);
    root = ekleSirali(root,50);
    bastir(root);
    root = sil(root,50);
    bastir(root);
    root = sil(root,999);
    bastir(root);
    root = sil(root,4);
    bastir(root);
    root = sil(root,450);
    bastir(root);

    return 0;
}
