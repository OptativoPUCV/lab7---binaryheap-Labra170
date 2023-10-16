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
  if (pq == NULL || pq->size == 0) // Si el heap está vacío o el tamaño es 0
  {
    return NULL; // Entonces, no hay datos.
  }
  
  return pq->heapArray[0].data; // Se regresa la "raíz" del montículo
}

void heap_push(Heap* pq, void* data, int priority)
{
  if (pq == NULL) // Si el montículo no existe
  {
    return; // Se regresa
  }

  if (pq->size == pq->capac) // Si el montículo está a máxima capacidad
  {
    pq->capac = pq->capac * 2 + 1; // Se extiende con el doble más uno
    pq->heapArray = (heapElem*)realloc(pq->heapArray, sizeof(heapElem) * pq->capac); // Se reasigna la memoria

    if (pq->heapArray == NULL) // Si no se pudo reasignar
    {
      exit(EXIT_FAILURE); // Finaliza fallidamente
    }
  }

  heapElem nuevoElemento; // El nuevo elemento a agregar al heap
  nuevoElemento.data = data; // Se asigna la data
  nuevoElemento.priority = priority; // Y la prioridad

  int i = pq->size; // Se establece un indexador del tamaño de size
  pq->heapArray[i] = nuevoElemento;  // El nuevo elemento se agrega a esa posición
  pq->size++; // Se aumenta el size del heap

  while (i > 0 && pq->heapArray[i].priority > pq->heapArray[(i-1)/2].priority)
    // Mientras no estemos en la raíz y la prioridad del actual sea mayor a la del padre
    {
      heapElem aux = pq->heapArray[i]; // Un auxiliar al elemento actual
      pq->heapArray[i] = pq->heapArray[(i-1)/2]; // Se reemplaza con el padre
      pq->heapArray[(i-1)/2] = aux; // Se actualiza el valor
      i = (i-1) / 2; // Se va al padre
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
  Heap *heap = (Heap*)malloc(sizeof(Heap)); // Asignación de memoria

  if (heap == NULL) // Si no se pudo asignar
  {
    exit(EXIT_FAILURE); // Finaliza fallidamente
  }

  heap->size = 0; // Tamaño del heap
  heap->capac = 3; // Capacidad mínima
  heap->heapArray = (heapElem*)malloc(sizeof(heapElem)*heap->capac); // Asignación de memoria para el arreglo

  if (heap->heapArray == NULL) // Si no se pudo asignar memoria para el arreglo
  {
    free(heap); // Se libera el heap
    exit(EXIT_FAILURE); // Finaliza fallidamente
  }
  
  return heap; // Se retorna.
}
