#include <stdio.h>
#include <stdlib.h>

int *dizi;
int boyut=2;
int tepe=0;
int pop(){   //stack icerisinden veri almak demek. 2 eleman varsa tepe 2'dir ama dizi oldugundan 0. ve 1. elemanlardýrlar bu nedenle üstekini almak icin de 1 azaltiriz.
    if(tepe<=boyut/4){ //iceriden veri alýnca dizi kuculýyýr ama yeri kalýyýr bu nedenle icerideki veri 4'te birine gelince yarýsý boyutlu dizi olusturup elemanlari ona kopyalariz.
        int* dizi2 = (int*)malloc(sizeof(int)*boyut/2);
        for(int i=0;i<tepe;i++)
                dizi2[i]=dizi[i];
        free(dizi);
        dizi=dizi2;
        boyut/=2;
    }
    return dizi[--tepe];
}
void push(int a){   //stack icerisine veri koymak demek. 1 veri koyunca tepe degeri 1 oluyýr ama o veri 0. eleman.
    if(tepe>=boyut){
        int* dizi2 = (int*)malloc(sizeof(int)*boyut*2); //boyutu 2 katýna cikarmak icin yeni bir dizi olusturuyoruz ama malloc ile cunku boyutu bilmiyoruz boyut*2 diyoruz bu nedenle normal dizi ile yapamayiz.
        for(int i=0;i<tepe;i++)
                dizi2[i]=dizi[i];  //elemanleri yeni diziye kopyaliyoruz
        free(dizi);   //diziyi ramde yer kaplamasin diye siliyoruz
        dizi=dizi2;   //dizi pointeri de yeni diziyi gosteriyor artik
        boyut*=2;

    }//bu if ne zaman dizi dolsa *2 boyutluk dizi ile degistiriyor.
    dizi[tepe++] = a;
}
void bastir(){
    printf("boyut : %d\n ",boyut);
    for(int i=0;i<tepe;i++){
        printf("%d ",dizi[i]);
    }
}

int main()
{
    dizi = (int*)malloc(sizeof(int)*2);
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    bastir();
    printf("\npopped %d\n",pop());
    printf("popped %d\n",pop());
    printf("popped %d\n",pop());
    printf("popped %d\n",pop());
    printf("popped %d\n",pop());
    bastir();
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    push(60);
    push(70);
    push(80);
    push(90);
    push(100);
    bastir();


    return 0;
}
