#include <stdio.h>
#include <stdlib.h>

struct POINT{
    char dizi1[20];
    char dizi2[20];
    int id;
};

int main()
{
    struct POINT *p;
    p=(struct POINT*)malloc(sizeof(struct POINT));

    strcpy(p->dizi1,"Bilgisayar");
    strcpy(p->dizi2,"Programlama");
    p->id=13;

    printf("%d %s %s\n",p->id,p->dizi1,p->dizi2);
    free(p);

    return 0;
}
