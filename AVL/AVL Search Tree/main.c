#include <stdio.h>
#include <stdlib.h>
#define LH +1
#define EH 0
#define RH -1

typedef struct node{   //teker teker agactaki dugumlerin hepsi
    void* dataPtr;
    struct node* left;
    int bal; //denge faktoru
    struct node* right;
}NODE;

typedef struct{       //Agacin tamami
    int count;
    int (*compare)(void* argu1,void* argu2);
    NODE* root;
}AVL_TREE;

                /* PROTOTIP TANIMLARI*/
AVL_TREE* AVL_Create(int (*compare)(void* argu1,void* argu2));
AVL_TREE* AVL_Destroy(AVL_TREE* tree);

bool AVL_Insert(AVL_TREE* tree, void* dataInPtr); //eklemek
bool AVL_Delete(AVL_TREE* tree, void* dltKey);    //silmek
void* AVL_Retrieve(AVL_TREE* tree, void* keyPtr);   //gerialmak
void AVL_Traverse(AVL_TREE* tree, void(*process)(void* dataPtr));
int AVL_Count(AVL_TREE* tree);
bool AVL_Empty(AVL_TREE* tree);
bool AVL_Full(AVL_TREE* tree);

NODE* _insert(AVL_TREE* tree, NODE* root, NODE* newPtr, bool* taller );
NODE* _delete(AVL_TREE* tree, NODE* root, void* dltKey, bool* shorter, bool* success);
void* _retrieve(AVL_TREE* tree, void* keyPtr, NODE* root);
void _traversal(NODE* root,void(*process)(void* dataPtr));
void _destroy(NODE* root);

NODE* rotateLeft(NODE* root);
NODE* rotateRightt(NODE* root);
NODE* insLeftBal(NODE* root, bool* taller);
NODE* insRightBal(NODE* root, bool* taller);
NODE* dltLeftBal(NODE* root, bool* shorter);
NODE* dltRightBal(NODE* root, bool* shorter);

AVL_TREE* AVL_Create(int (*compare)(void* argu1,void* argu2)){ //Agac olusturma
    AVL_TREE* tree;

    tree=(AVL_TREE*)malloc(sizeof(AVL_TREE));
    if(tree){
        tree->root=NULL;
        tree->count=0;
        tree->compare=compare;
    }
    return tree;
}

bool AVL_Insert(AVL_TREE* tree, void* dataInPtr){  //Agac ekleme
    NODE* newPtr;
    bool forTaller; //eklenebilir mi

    newPtr = (NODE*)malloc(sizeof(NODE));
    if(!newPtr)
        return false;

    newPtr->bal=EH;
    newPtr->right=NULL;
    newPtr->left=NULL;
    newPtr->dataPtr=dataInPtr;

    tree->root = _insert(tree,tree->root,newPtr,&forTaller); //Agaca eleman ekleme
    (tree->count)++;
    return true;
}

NODE* _insert(AVL_TREE* tree, NODE* root, NODE* newPtr, bool* taller ){  //Bu iþlev AVL aðacýndaki bir yaprak düðüme yeni verileri eklemek için özyinelemeyi kullanýr.
    if(!root){ //koke ekleme yani agac bossa
        root = newPtr;
        *taller=true;
        return root;
    }
    if(tree->compare(newPtr->dataPtr,root->dataPtr)<0){ //eklenen kokten kucukse sola eklenir
        root->left=_insert(tree, root->left,newPtr,taller);

        if(*taller) //sol alt agac daha uzun yani ekledikten sonra denge bozulduysa
           switch(root->bal){
               case LH:   // Yüksek birakildi -- dondur
                   root=insLeftBal(root,taller);
                   break;
               case EH:   // Dengelendi--þimdi LH
                   root->bal= LH;
                   break;
               case RH:    // Yuksekti zaten dengelendi EH oldu
                   root->bal= EH;
                   *taller= false;
                   break;
           }
           return root;

    }
    else{ //eklenen kokten  buyuk ise saga eklenir
        root->right=_insert(tree, root->right,newPtr,taller);

        if(*taller) //sag alt aðaç daha uzun
           switch(root->bal){
               case LH:   // Yüksek býrakýldý -- þimdi EH
                   root->bal=EH;
                   *taller->false;
                   break;
               case EH:   // Dengelendi--þimdi LH
                   root->bal= RH;
                   break;
               case RH:    // Tam yüksekti -- þimdi EH
                   root=insRightBal(root,taller);
                   break;
           }
           return root;
    }
    return root;
}

NODE* insLeftBal(NODE* root, bool* taller){  //Soldaki aðaç dengesiz. Bu fonksiyon sol taraf fazlaysa dengelemek icin gereklidir.
    NODE* rightTree;
    NODE* leftTree;

    leftTree=root->left;
    switch(leftTree->bal){
        case LH: //Sol Yüksek Saða Döndür //LEFT OF LEFT
            root->bal = EH;
            leftTree->bal=EH;

            //SAGA DONDURME
            root = rotateRight(root);
            *taller=false;
            break;

        case EH: // This is an error
             printf ("\n\aError in insLeftBal\n");
             exit (100);
        case RH:  // Sağ Yüksek Çift döndürme gerektirir: önce sola, sonra sağa //RIGHT OF LEFT
             rightTree = leftTree->right;
             switch(rightTree->bal){
                 case LH:
                     root->bal=RH;
                     leftTree->bal=EH;
                     break;
                 case EH:
                    root->bal=EH;
                    leftTree->bal=LH;
                    break;
                 case RH:
                    root->bal=EH;
                    leftTree->bal=LH;
                    break;
             }
             rightTree->bal = EH;

             root->left = rotateLeft(leftTree);  //Sola Dondurme

             root=rotateRightt(root);            //Saga Dondurme
             *taller=false;
    }
    return root;
}

NODE* rotateLeft(NODE* root){
    NODE* tempPtr;

    tempPtr = root->right;
    root->right = tempPtr->left;
    tempPtr->left=root;             //sola dondurme
    return tempPtr;
}

NODE* rotateRightt(NODE* root){
    NODE* tempPtr;

    tempPtr = root->left;
    root->left = tempPtr->right;
    tempPtr->right = root;      //saga dondurme
    return tempPtr;
}

bool AVL_Delete(AVL_TREE* tree, void* dltKey){  //Kullanicidan gelen parametreleri kabul eder ve delete fonksiyonuna gonderir.Delete ten gelen cevaba gore rootu yeniler
    bool shorter;
    bool success;  //silebilirse true dondurur
    NODE* newRoot;

    newRoot = _delete(tree,tree->root,dltKey,shorter,success);   //dltKey, silinecek anahtarın işaretçisidir
    if(success){
        tree->root=newRoot;
       (tree->count)--;
       return true;
    }
    else
        return false;
}

NODE* _delete(AVL_TREE* tree, NODE* root, void* dltKey, bool* shorter, bool* success){  //Düğümü ağaçtan siler ve yeniden dengeler gerekirse ağaç
    NODE* dltPtr;
    NODE* exchPtr;
    NODE* newRoot;

    if(!root){
        *shorter=false;
        *success=false;
        return NULL;
    }
    if(tree->compare(dltKey, root->dataPtr)<0) {  //silinecek eleman kökten kücükse yani sol tarafta ise
        root->left=_delete(tree,root->left,dltKey,shorter,success);
        if(*shorter) //daha az ise
            root = dltRightBal(root,shorter);
    }
    else if (tree->compare(dltKey, root->dataPtr)>0){
        root->right=_delete(tree,root->right,dltKey,shorter,success);
        if(*shorter) //daha buyukse
            root = dltLeftBal(root,shorter);
}
    else{             //esit dugum bulundu
        dltPtr = root;
        if(!root->right){  //Sadece sol alt ağaç
            newRoot = root->left;
            *success = true;
            *shorter = true;
            free(dltPtr);
            return newRoot;
        }
        else
        if(!root->left){
            newRoot = root->right;
            *success = true;
            *shorter = true;
            free(dltPtr);
            return newRoot;
        }
        else{  //Silme Düğümünün iki alt ağacı vardır
            exchPtr = root->left;
            while(exchPtr->right)
                exchPtr = exchPtr->right;
            root->dataPtr = exchPtr->dataPtr;
            root->left = (tree, root->left, exchPtr->dataPtr,shorter, success);
            if(*shorter)
                root=dltRightBal(root,shorter);
        }
    }
    return root;
    /*Özyinelemeli eklemede gördüğümüz gibi, fonksiyonun ilk kısmı silinecek düğümü arar..Silinecek düğümü bulmadan önce bir yaprağa ulaşırsa, başarı bayrağını yanlış olarak ayarlar ve
boş gösterici döndürür. Bu, üç temel durumdan ilkidir.




*/

}








int main()
{

    return 0;
}
