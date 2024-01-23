#include <stdio.h>
#include <stdlib.h>

int add(int n){
    if(n==1)
        return 1;
    else
        return(1/n + add(n-1));


}

int main()
{
    int sayi;
    printf("Serinin toplamak istediginiz ilk n elemanini giriniz: ");
    scanf("%d",&sayi);
    printf("Sonuc: %f",add(sayi));

    return 0;
}
