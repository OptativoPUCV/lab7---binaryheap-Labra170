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
    return NULL;
  }
  
  return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority)
{
  if (pq == NULL)
  {
    return;
  }

  if (pq->size == pq->capac)
  {
    pq->capac = pq->capac * 2 + 1;
    pq->heapArray = (heapElem*)realloc(pq->heapArray, sizeof(heapElem) * pq->capac);

    if (pq->heapArray == NULL)
    {
      exit(EXIT_FAILURE);
    }
  }

  heapElem nuevoElemento;
  nuevoElemento.data = data;
  nuevoElemento.priority = priority;

  int i = pq->size;
  pq->heapArray[i] = nuevoElemento;
  pq->size++;

  while (i > 0 && pq->heapArray[i].priority > pq->heapArray[(i-1)/2].priority)
    {
      heapElem aux = pq->heapArray[i];
      pq->heapArray[i] = pq->heapArray[(i-1)/2];
      pq->heapArray[(i-1)/2] = aux;
      i = (i-1) / 2;
    }
}


void heap_pop(Heap* pq)
{
  if (pq == NULL || pq->size == 0)
  {
    return;
  }

  pq->heapArray[0] = pq->heapArray[pq->size-1];
  pq->size--;

  int index = 0;
  while (1)
    {
      int izquierdo = 2 * index + 1;
      int derecho = 2 * index + 2;
      int mayor = index;

      if (izquierdo < pq->size && pq->heapArray[izquierdo].priority > pq->heapArray[mayor].priority)
      {
        mayor = izquierdo;
      }
      if (derecho < pq->size && pq->heapArray[derecho].priority > pq->heapArray[mayor].priority)
      {
        mayor = derecho;
      }

      if (mayor != index)
      {
        heapElem aux = pq->heapArray[index];
        pq->heapArray[index] = pq->heapArray[mayor];
        pq->heapArray[mayor] = aux;
        index = mayor;
      }
      else
      {
        break;
      }
    }
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
