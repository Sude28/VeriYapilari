#include <stdio.h>
#include <stdlib.h>

struct n{
    int x;
    struct n* next;

};
typedef struct n node;

void bastir(node* r){
    node* iter =r;
    printf("%d ",iter->x); //ilk elemani elle bastiriyorum cunku iter = root oldugundan donguye girmez simdi iter 2. elemana gezti simdi girer donguye
    iter=iter->next;
    while( iter!=r ){ //iter roota esit olana kadar yani basa gelene kadar devam et
        printf("%d ",iter->x);
        iter=iter->next;
    }
    printf("\n");
}

void ekle(node* r , int x){
    node* iter = r;
    while(iter->next!=r){ //iter degil iterin nexti yani son kutu
        iter=iter->next;
    }
    iter->next = (node*)malloc(sizeof(node));
    iter->next->x=x;
    iter->next->next = r;
}

node* ekleSirali(node* r,int x){
    if(r==NULL){  //dairesel link list bossa
            r=(node*)malloc(sizeof(node));
            r->x = x;
            r->next = r;
            return r;
    }
    if(r->x > x){ //basa ekleme ekleyecegim rootun x inden kucuk ise
            node * temp = (node*)malloc(sizeof(node));
            temp -> x = x;
            temp -> next = r;
            node* iter= r;
            while(iter->next != r){ //bastan butun dairesel link listi dolastum ve iter->next i r yi gosterince durdum iter-> next yeni basa ekledigim tempi gostersin diyip daireyi tamamladim
                    iter=iter->next;
            }
            iter->next=temp;
            return temp;
    }

    node* iter = r;
    while(iter->next!=r && iter->next->x < x){
        iter=iter->next;
    }
    node* temp = (node*)malloc(sizeof(node));
    temp->x =x;
    temp->next = iter->next ;
    iter->next = temp;

    return r;
}

node* sil(node* r,int x){
       node* temp;
       node* iter=r;
       if(r->x == x){
           while(iter->next != r){
                iter=iter->next;
           }
           iter->next=r->next;
           free(r);
           return iter->next;

       }
       while(iter->next != r && iter->next->x != x){ //ilerle
            iter=iter->next;
       }

       if(iter->next==r){   //sona kadar geldim artýk son dugum bastakini gosteriyor
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
    root = ekleSirali(root,400);
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
