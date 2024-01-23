#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct n{
    int no;
    char ad[20];
    char soyad[20];
    char bolum[30];
    int sinif;
    struct n* next;
    struct n* prev;
};
typedef struct n node;

void ListeyiGoster(node* r){
    if(r==NULL)
        printf("Gosterilecek ogrenci bulunmamaktadir...");
    while(r!=NULL){
        printf("%d numarali ogrencinin;\n ",r->no);
        printf("\t Adi: %s\n",r->ad);
        printf("\t Soyadi: %s\n",r->soyad);
        printf("\t Bolumu: %s\n",r->bolum);
        printf("\t Sinifi: %d\n",r->sinif);

        r=r->next;
    }
}

void ListedeGezin(node* r,int n){
    node* iter =r;
    if(iter->no!=n)
        printf("Aradiginiz ogrenci bulunmamaktadir...");
    while(iter->no!=n){
        iter = iter->next;
    }
    printf("Aranan ogrencinin;\n");
    printf("\t Adi: %s\n",iter->ad);
    printf("\t Soyadi: %s\n",iter->soyad);
    printf("\t Bolumu: %s\n",iter->bolum);
    printf("\t Sinifi: %d\n",iter->sinif);
}

node*SiraliEkle(node*r, int n, char* a, char* so, char* b, int s){
    if(r==NULL){ //linklist bossa
        r=(node*)malloc(sizeof(node));
        r->no=n;
        strcpy(r->ad,a);
        strcpy(r->soyad,so);
        strcpy(r->bolum,b);
        r->sinif=s;
        r->next=NULL;
        r->prev=NULL;
        return r;
    }
    if(r->no > n){  //eklenecek ilk elemansa
        node* temp=(node*)malloc(sizeof(node));
        temp->no=n;
        strcpy(temp->ad,a);
        strcpy(temp->soyad,so);
        strcpy(temp->bolum,b);
        temp->sinif=s;
        temp->next=r;
        r->prev=temp;
        temp->prev=NULL;
        return temp;
    }
    node* iter=r;
    while(iter->next!=NULL && iter->next->no < n){  //bir sonraki dugum null olana kadar veya bir sonraki dugum benden buyuk olana kadar devam et
        iter=iter->next;
    }
    node* temp=(node*)malloc(sizeof(node));
    temp->no=n;
    strcpy(temp->ad,a);
    strcpy(temp->soyad,so);
    strcpy(temp->bolum,b);
    temp->sinif=s;
    temp->next=iter->next;
    iter->next=temp;
    temp->prev=iter;
    if(temp->next!=NULL){
            temp->next->prev=temp;
    }
    return r;
}

node*Sil(node*r, int n){
    node* temp;  //free  etmek icin gerekli
    node*iter = r; //gezinmesi icin gerekli
    if(r->no==n){  //silinecek dugum basta ise
        temp=r;
        r=r->next;
        free(temp);
        return r;
    }
    while(iter->next != NULL && iter->next->no != n){
            iter=iter->next;
    }
    if(iter->next==NULL){
        printf("%d numarali ögrenci bulunamadi",n);
        return r;
    }
    temp=iter->next;
    iter->next=iter->next->next;
    if(iter->next!=NULL){
        iter->next->prev=iter;
    }
    free(temp);
    return r;
}

int main()
{
    node* root;
    root = NULL;
    int secim,no,sinif;
    char ad[20],soyad[20],bolum[30];

    while(1){
        printf("\n------OGRENCI OTOMASYONU------ \n");
        printf("1-- Ogrenci Ekle \n");
        printf("2-- Ogrenci Sil \n");
        printf("3-- Ogrenci Ara \n");
        printf("4-- Ogrenci Listesini Goster \n");
        printf("0-- Cikis \n");
        printf("Lutfen yapmak istediginiz islemi tuslayiniz -> ");
        scanf("%d",&secim);
        printf("\n");

        switch(secim)
        {
           case 1:
                printf("Ogrencinin Numarasini Giriniz                  : ");
                scanf("%d",&no);
                printf("Ogrencinin Adini Giriniz                       : ");
                scanf("%s",ad);
                printf("Ogrencinin Soyadini Giriniz                    : ");
                scanf("%s",soyad);
                printf("Ogrencinin Bolumunu Giriniz(bosluksuz giriniz) : ");
                scanf("%s",bolum);
                printf("Ogrencinin Sinifini Giriniz                    : ");
                scanf("%d",&sinif);
                root=SiraliEkle(root,no,ad,soyad,bolum,sinif);

                break;

            case 2:
                printf("Silinecek Ogrencinin Numarasini Giriniz : ");
                scanf("%d",&no);
                root=Sil(root,no);
                printf("Ogrenci basariyla silindi...");
                break;

             case 3:
                 printf("Bilgilerine Ulasmak Istediginiz Ogrencinin Numarasini Giriniz: ");
                 scanf("%d",&no);
                 ListedeGezin(root,no);
                 break;

             case 4:
                 ListeyiGoster(root);
                 break;

             case 0:
                 return 0;

             default:
                 printf("Yanlis tuslama yaptiniz \n");
        }
    }
    return 0;
}
