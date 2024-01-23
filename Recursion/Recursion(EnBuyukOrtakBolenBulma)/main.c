#include <stdio.h>
#include <stdlib.h>

int ebob(int a,int b){
    if(a==0)
        return b;
    if(b==0)
        return a;
    return ebob(b,a%b);
}

int main()
{
    int sayi1,sayi2;
    printf("En buyuk ortak boleni bulunacak iki sayiyi giriniz: ");
    scanf("%d %d",&sayi1,&sayi2);
    printf("En buyuk ortak bolen: %d",ebob(sayi1,sayi2));
    return 0;
}
