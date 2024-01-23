#include <stdio.h>
#include <stdlib.h>
struct n{
    int x;
    struct n * next;
};
typedef struct n node;

int main()
{
    node* root; //ilk kutucugu point ediyor
    root = (node*)malloc(sizeof(node)); //ilk kutucuk icin yer aldik malloc ile
    root -> x = 10; // Kutucugun veri kismina erisip 10 degerini atadi
    root -> next = (node*)malloc(sizeof(node)); //ikinci kutucuk icin yer aldik malloc ile
    root -> next -> x = 20;
    root -> next -> next = (node*)malloc(sizeof(node));
    root -> next ->next -> x =30;
    root -> next -> next -> next = NULL; //null diye belirtmezsem random deger atar null olmus olmaz orasi

    node* iter; //kutucuklari dolassin diye olusturduk.Kutucuk sayisi artinca yukaridakini yapmak cok uzun surer
    iter = root; //roota esitledik cunku ilk kutucktan basliyor isaret etmeye sonra istedigimiz kutucuga goturuyoruz
    printf("%d\n",iter->x);
    iter = iter ->next; //Bir sonraki kutucugu isaret etsin dedik. Bir sonrakisi icin yine ayni kodu yazariz boykece yukaridaki gibi (root -> next ->next) uzamiyor.
    printf("%d",iter->x);

    iter=root;
    int i=0;
    while(iter->next != NULL) { // iter!=NULL yani null gorene kadar kutucuklari tara demememizin sebebi null a gittikten sonra artýk sonuna bir kutucuk daha ekleyemem cunku iter null gösteriyor bu yuzden nexti null olana kadar git dedigimizde son kutucugu kastetmis oluyoruz
        i++;
        printf("%dinci eleman : %d\n",i,iter->x);
        iter = iter->next;
    }



    return 0;
}
