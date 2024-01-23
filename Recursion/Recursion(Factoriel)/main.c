#include <stdio.h>
#include <stdlib.h>

int factorielwithrecursion(int n){
    if(n==0)
        return 1;
    else
        return n*factorielwithrecursion(n-1);
}

int main()
{
    int sayi;
    printf("Faktoriyeli alinacak sayiyi giriniz: ");
    scanf("%d",&sayi);
    printf("Sonuc: %d",factorielwithrecursion(sayi));
    return 0;
}
