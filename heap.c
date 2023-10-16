#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq)
{
  if (pq == NULL || pq->size == 0)
  {
    exit(EXIT_FAILURE);
  }
  
  return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){

}


void heap_pop(Heap* pq){

}

Heap* createHeap()
{
  Heap *heap = (Heap*)malloc(sizeof(Heap));

  if (heap == NULL)
  {
    exit(EXIT_FAILURE);
  }

  heap->size = 0;
  heap->capac = 3;
  heap->heapArray = (heapElem*)malloc(sizeof(heapElem)*heap->capac);

  if (heap->heapArray == NULL)
  {
    free(heap);
    exit(EXIT_FAILURE);
  }
  
  return heap;
}
