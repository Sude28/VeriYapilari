#include <stdio.h>
#include <stdlib.h>
#define boyut 10 //boyutu bilinen diziler varsa stack icin dizi kullanilabilir

struct stack{
    int top;
    int deger[boyut];
};
 struct stack s;

void push(struct stack *ps, int x){
    if(ps->top==9)
        printf("stack dolu");
    else
        ps->deger[(ps->top)++]=x;
}
void pop(struct stack *ps){
    if(ps->top==0)
        printf("stack bos");
    else
        ps->top--;
}

int main()
{
    int sayi=0;
    while(sayi!=4){
        printf("\nLutfen bir secim yapin: \n1 Ekleme Islemi \n2 Silme Islemi \n3 Listeleme Islemi \n4 Diger: Cikis\n");
        scanf("%d",&sayi);

        switch(sayi){
            case 1:
                printf("Eklemek istediginiz sayiyi girin:\n");
                int ekle;
                scanf("%d",&ekle);
                push(&s,ekle);
                break;
            case 2:
                pop(&s);
                break;
            case 3:
                if(s.top==0)
                    printf("Liste bos");
                else
                    printf("Listeniz: ");
                    for(int i=0;i<s.top;i++)
                        printf("%d ",&s.deger[i]);
                    break;

            default:
                printf("\n");
                break;




        }

    }
    return 0;
}
