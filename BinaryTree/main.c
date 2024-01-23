#include <stdio.h>
#include <stdlib.h>


struct n{
    int data;
    struct n* sol;
    struct n* sag;
};
typedef struct n node;

node* ekle(node* agac, int x){
    if(agac==NULL){
        node* root = (node*)malloc(sizeof(node)); //ekleme son dugume yani cocugu olmayan dugume yapilir.
        root->sol=NULL;
        root->sag=NULL;
        root->data=x;
        return root;
    }
    if(x > agac->data){  //gelen sayi kökten buyuk ise saga eklenir
        agac->sag = ekle(agac->sag,x); //sagda daha dugum varsa hepsi icin ayni islem yapilir yani orasi da bir agac -> recursive fonksiyon .kısaca ilk önce köke bakıyırum elimdekinden kucuk mu diye kucukse onun sagini gonderiyorum kontrol etsin kucuk mu diye en son elimdeki kucukoluyır hepsinden bir sonraki null olunca ekliyorum
        return agac;
    }
    agac->sol = ekle(agac->sol,x);  // ***x kucukse sola gidilir  yeni agac karsilastirdigin dugum harici agac olur ekleyene kadar agac kucultulerek gonderilir ekleye ***
    return agac;
}

/*void dolas(node* agac){
    if(agac==NULL)
        return;
    dolas(agac->sol);    //ýnfix dolasmaya gore once sol sonra dugum en son sag dolasilir bu nedenle en sola kadar soldaki kalmayana kadar gidilir sonra dugum sonra sag yazilir sonra yine sol yazilir (tabi varsa) bu nedenle recursive
    printf("%d ",agac->data); //sol kalmayinca bir alt satir calisiyor yani yazdiriyor
    dolas(agac->sag);
}*/

void dolas(node* agac){
    if(agac==NULL)
        return;
    dolas(agac->sag);   //infix dolasmanin bir digeri once sag sonra dugum en son sol
    printf("%d ",agac->data);
    dolas(agac->sol);
    /*printf("%d ",agac->data);
     dolas(agac->sag);
     dolas(agac->sol);  --> Prefix*/

}

int bul(node* agac, int aranan){
    if(agac==NULL)
        return -1;
    if(agac->data==aranan)
        return 1;
    if(bul(agac->sag,aranan)==1) // ilk kisimda sagý ariyoruz bulana kadar her dugumun bir sagina bakiyoruz bu nedenle recursive .herhangi bir dugumde 1 geldiyse vardýr yani return 1

        return 1;
    if(bul(agac->sol,aranan)==1)
        return 1;
    return -1;
}

int max(node* agac){
    while(agac->sag!=NULL) //agactaki en buyuk ifade en sagda olandir bu nedenle onun sagý yok yani sagý null olana kadar gidilir
        agac=agac->sag;  //baktikca o dugumu atip agaci yeniliyorum
    return agac->data;
}
int min(node* agac){
    while(agac->sol!=NULL)
        agac=agac->sol;
    return agac->data;
}

node* sil(node* agac, int x){
    if(agac==NULL)
        return NULL;
    if(agac->data==x){ //Silecegim dugumu bulduysam
        if(agac->sol==NULL && agac->sag==NULL) //silecegimin hic cocugu yoksa direk sileriz
            return NULL;
        if(agac->sag!=NULL){ // ortadaki dugum yerine sagdaki en kucugu yazabiliriz cunku sag tarafi kendinden buyuk sol tarafi kendinden kucuk olmali
            agac->data = min(agac->sag); //sagin min degerine esitledik
            agac->sag=sil(agac->sag,min(agac->sag)); //burda da esitledigimize gore sagin min degerini siliyoruz
            return agac;
        }
        agac->data=max(agac->sol);  //sagi null ise agacin yani hic yaprak yoksa sola bakariz soldakilerin de en buyugunu alamiz lazim ki sagdakilerden buyuk olsun (agac kurali)
        agac->sol=sil(agac->sol,max(agac->sol));
        return agac;
    }
    if(agac->data < x){ //Silecegim dugumu daha bulmadım arıyorsam
        agac->sag = sil(agac->sag,x); //bulana kadar recursive bulunca ikinci if'e girer
        return agac;
    }
    agac->sol = sil(agac->sol,x); //Silecegim dugumu daha bulmadım arıyorsam
    return agac;

}

int main()
{
    node* agac=NULL;
    agac=ekle(agac,56);
    agac=ekle(agac,200);
    agac=ekle(agac,26);
    agac=ekle(agac,190);
    agac=ekle(agac,213);
    agac=ekle(agac,18);
    agac=ekle(agac,28);
    agac=ekle(agac,12);
    agac=ekle(agac,24);
    agac=ekle(agac,27);

    dolas(agac);

    printf("\nArama sonucu: %d",bul(agac,100));
    printf("\nArama sonucu: %d",bul(agac,24));

    printf("\nAgactaki en buyuk deger: %d",max(agac));
    printf("\nAgactaki en kucuk deger: %d",min(agac));
    printf("\n");

    agac=sil(agac,56);
    dolas(agac);

    return 0;
}
