#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    void ** heapAry;
    int last;
    int size;
    int (*compare)(void* argu1,void* argu2);
    int maxSize;
} HEAP;

          /*PROTOT�P TANIMLARI*/
HEAP* heapCreate(int maxSize, int (*compare)(void* arg1,void* arg2));  //heap olusturmak
bool heapInsert(HEAP* heap, void* dataPtr);                            //eklemek
bool heapDelete(HEAP* heap, void** dataOutPtr);                        //silmek
int  heapCount(HEAP* heap);                                             //saymak
bool heapFull(HEAP* heap);                                             //full m�
bool heapEmpty(HEAP* heap);                                            //bos mu
void heapDestroy(HEAP* heap);                                          //tahrip etmek

void ReheapUP(HEAP* heap, int childLoc); //yeni dugum eklenince max heap olucak sekilde heapi duzenler.
void ReheapDown(HEAP* heap,int root);    //kok dugum silinince max heap olucak sekilde heapi duzenler.

HEAP* heapCreate(int maxSize, int (*compare)(void* argu1,void* argu2)){
    HEAP* heap;
    heap=(HEAP*)malloc(sizeof(HEAP));

    if(!heap)
        return NULL;

    heap->last=-1;
    heap->compare = compare;
    heap->maxSize = (int)pow(2,ceil(log2(maxSize)))-1;
    heap->heapAry= (void*)calloc(heap->maxSize,sizeof(void*));
    return heap;
}

bool heapInsert (HEAP* heap,void* dataPtr){  //last, son eleman i�in dizine i�aret eden i�aret�idir.
    if(heap->size ==0){ //bossa
        heap->size=1;
        heap->last=0;
        heap->heapAry[heap->last]=dataPtr;
        return true;  //basar�l� olursa true doluysa false dondurur
    }
    if(heap->last == heap->maxSize-1) //dolu demek yani ekleme yapamayiz.
        return false;
    ++(heap->last);
    ++(heap->size);
    heap->heapAry[heap->last]=dataPtr;
    ReheapUP(heap,heap->last);
    return true;
}

void ReheapUP(HEAP* heap, int childLoc){
    int parent;
    void** heapAry;
    void* hold; //swap icin

    //y���n�n k�k�nde de�ilse --index 0
    if(childLoc){
        heapAry=heap->heapAry;
        parent=(childLoc-1)/2;
        if(heap->compare(heapAry[childLoc],heapAry[parent]) > 0) {  //�ocuk ebeveynden daha b�y�kt�r --swap
            hold = heapAry[parent];
            heapAry[parent] = heapAry[childLoc];
            heapAry[childLoc] = hold;            //buyuk olan parent oldu
            ReheapUP(heap,parent); // yine cocuk atasindan buyukse cagrilir
        }
    }
    return;
}

bool heapDelete(HEAP* heap, void** dataOutPtr){ //Y���n k�k�n� siler ve verileri arayana geri iletir
    if(heap->size==0)
        return false;

    *dataOutPtr = heap->heapAry[0];
    heap->heapAry[0]=heap->heapAry[heap->last];
    (heap->last)--;
    (heap->size)--;
    ReheapDown(heap,0);
    return true;
}

void ReheapDown(HEAP* heap,int root){ //K�kteki verileri kendi konumuna ta��yarak y���n� yeniden olu�turur
    void* hold;
    void* leftData;
    void* rightData;
    int largeLoc;
    int last; //son eleman

    last = heap->last;
    if((root*2 + 1) <= last){   //sol alt a�a�
        //en az bir �ocuk var
        leftData = heap->heapAry[root*2 + 1];
        if((root*2 +2) <= last)  //sag alt agac
            rightData = heap->heapAry[root*2 + 2];
        else
            rightData = NULL;

        //Hangi �ocu�un daha b�y�k oldu�unu belirleyin
        if((!rightData) || heap->compare(leftData,rightData) > 0) {
            largeLoc = root*2 + 1;
        }
        else { // sa� tu� yoksa veya leftKey daha b�y�kse
            largeLoc = root*2 + 2;
        }

        // K�k > daha b�y�k alt a�a� olup olmad���n� test edin
        if(heap->compare(heap->heapAry[root],heap->heapAry[largeLoc]) < 0){
            // ebeveyn < �ocuklar
            hold = heap->heapAry[root];
            heap->heapAry[root] = heap->heapAry[largeLoc];
            heap->heapAry[largeLoc] = hold;
            ReheapDown(heap,largeLoc);
        }
    }
    return;
}

int main()
{

    return 0;
}
