#include <stdio.h>
#include <stdlib.h>

struct POINT{
    int x;
    float y;
};

int main()
{
    struct POINT *p;
    p=(struct POINT *)malloc(sizeof(struct POINT));

    p->x=2334;
    p->y=987;

    printf("x=%d\ny=%f",p->x,p->y);
    free(p);
    return 0;
}
