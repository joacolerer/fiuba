#define _POSIX_C_SOURCE 200809L
#include "heap.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define CAP 16
#define COEF_REDIM 2


/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);

//Estructura del Heap
struct heap{
	void** datos;
	size_t cap;
	size_t cant;
	cmp_func_t cmp;
};

/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/

void swap (void **x, void **y) {
	void* aux = *x;
	*x = *y;
	*y=aux;

}

//Redimension
bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad) {
	void* nuevos_datos = realloc(heap->datos, nueva_capacidad*sizeof(void*));
	if (nuevos_datos == NULL) return false;
	heap->datos = nuevos_datos;
	heap->cap = nueva_capacidad;
	return true;
}

size_t calcular_pos_padre(size_t pos){
	return (pos -1) / 2;
}

size_t calcular_maximo(void** arreglo,cmp_func_t cmp, size_t padre, size_t izq, size_t der){
	if(cmp(arreglo[padre], arreglo[izq]) > 0 && cmp(arreglo[padre], arreglo[der]) > 0){
		return padre;
	}
	return cmp(arreglo[izq], arreglo[der]) > 0 ? izq : der;
}

//DownHeap
void downheap(void** arreglo, size_t tam, size_t padre, cmp_func_t cmp){
	if (padre >= tam) return;
	size_t izq = 2 * padre + 1;
	size_t der = 2 * padre + 2;

	size_t max = calcular_maximo(arreglo, cmp, padre, izq, der);

	if(max != padre){
		swap(arreglo[max], arreglo[padre]);
		downheap(arreglo, tam, max,cmp);
	}

}

//UpHeap

void upheap(void** arreglo, size_t hijo, cmp_func_t cmp){
	if(hijo == 0) return;
	size_t padre = calcular_pos_padre(hijo);
	if(cmp(arreglo[padre], arreglo[hijo]) < 0 ){
		swap(arreglo[padre],arreglo[hijo]);
		upheap(arreglo, padre,cmp);
	}
}

//Swap


/* ******************************************************************
 *                       PRIMITIVAS DEl ABB
 * *****************************************************************/


/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	heap->datos = malloc(CAP*sizeof(void*));
	if (heap->datos == NULL){
		free(heap);
		return NULL;
	}
	heap->cmp = cmp;
	heap->cap = CAP;
	heap->cant = 0;
	return heap;
}


/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
//Esta funcion es para hacer heapify
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp);


/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
	if (destruir_elemento != NULL){
		for (int i = 0 ; i < heap->cant ; i++) destruir_elemento(heap->datos[i]);
	}
	free(heap->datos);
	free(heap);
};


/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){
	//Si esta lleno hay que redimensionar
	if (heap->cant == heap->cap){
		bool redimension = heap_redimensionar(heap,COEF_REDIM * heap->cap);
		if (redimension == false) return false;
	}
	heap->datos[heap->cant] = elem;
	upheap(heap->datos,heap->cant,heap->cmp);
	heap->cant++;
	return true;
}

/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	if  (heap->cant * (2*COEF_REDIM) <= heap->cap && heap->cap > CAP){
		heap_redimensionar(heap,heap->cap / COEF_REDIM);
	}
	void* elem = heap->datos[0];
	heap->cant--;
	if(!heap_esta_vacio(heap)){
		swap(heap->datos[0], heap->datos[heap->cant]);
		downheap(heap->datos, heap->cant, 0, heap->cmp);
	}
	return elem;
}