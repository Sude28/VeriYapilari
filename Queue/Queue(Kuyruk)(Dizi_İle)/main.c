#include <stdio.h>
#include <stdlib.h>

int* dizi=NULL;
int sira=0 , sirabasi=0,boyut=2;

int deque(){
    if(sira==sirabasi){
        printf("\nSira bos...");
        return -1;
    }
    if(sira-sirabasi<=boyut/4){    //boyutun 4'te birinden de az olduysa elemanlar(sira-sirabasi bize eleman sayisini verir)
        int * dizi2= (int*)malloc(sizeof(int)*boyut/2);
        for(int i=0;i<sira-sirabasi;i++){
            dizi2[i]=dizi[sirabasi+i];
        }
        sira-=sirabasi;
        sirabasi=0;
        free(dizi);
        boyut/=2;
        dizi=dizi2;

    }
    return dizi[sirabasi++];  //bastaki eleman dondurulup yana kayýlýyor
}

void toparla(){   //deque ettigimiz elemanlardan kalan yerleri silmek icin
    if(sirabasi==0) //silincek bir þey yok
        return ;
    for(int i=0;i<boyut;i++){
        dizi[i]=dizi[i+sirabasi]; //ilk giren ilk ciktigindan bastan eleman aliyoruz bu nedenle baslar bos kaliyor
    }
    sira -= sirabasi;
    sirabasi=0;
}

void enque(int a){
    if(dizi==NULL){
        dizi=(int*)malloc(sizeof(int)*2);
    }
    if(sira >= boyut){
            boyut *= 2; //dizi yetmediyse iki katina cikardik
            int *dizi2 = (int*)malloc(sizeof(int)*boyut);
            for(int i=0;i<boyut/2;i++){
                dizi2[i]=dizi[i];//yeni diziye elemanlari kopyaladik
            }
            free(dizi);
            dizi=dizi2; //sirabasi artik dizi2'yi gostersin

    }
    dizi[sira++]=a;
}

int main()
{
    for(int i=0;i<20;i++){ //0 10 20 ... boyle 200'e kadar koyuyorum
        enque(i*10);
    }
    printf("\ndurum: boyut: %d sira %d sirabasi %d",boyut,sira,sirabasi);
    printf("\n");
    for(int i=0;i<13;i++){  // bastan 10 tanesini cekiyorum ve onları da yazdiriyorum
        printf("%d ",deque());
    }
    //toparla();
    printf("\ndurum: boyut: %d sira %d sirabasi %d",boyut,sira,sirabasi);

    for(int i=0;i<20;i++){
        enque(i*10);
    }
     printf("\ndurum: boyut: %d sira %d sirabasi %d",boyut,sira,sirabasi);
     printf("\n");
     for(int i=0;i<30;i++){
        printf("%d ",deque());
    }
     printf("\ndurum: boyut: %d sira %d sirabasi %d",boyut,sira,sirabasi);


    return 0;
}
