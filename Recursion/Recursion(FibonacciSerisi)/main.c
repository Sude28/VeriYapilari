#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    if(n==0)
        return 0;
    else if(n==1)
        return 1;
    else
        return fibonacci(n-1)+fibonacci(n-2);

}

int main()
{
    int terim;
    printf("Fibonacci serisini kacinci terimine kadar gormek istersiniz: ");
    scanf("%d",&terim);
    for(int i=0;i<terim;i++){
        printf("%d\n",fibonacci(i));
    }

    return 0;
}
