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

//Redimension
bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad) {
	void* nuevos_datos = realloc(heap->datos, nueva_capacidad*sizeof(void*));
	if (nuevos_datos == NULL) return false;
	heap->datos = nuevos_datos;
	heap->cap = nueva_capacidad;
	return true;
}

//DownHeap

//UpHeap

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
//Esta funcion es para hacer hipify
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
	return (heap->cant == 0);
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){
	//Si esta lleno hay que redimensionar
	if (heap->cant == heap->cap){
		size_t nueva_capacidad = COEF_REDIM * heap->cap;
		bool redimension = heap_redimensionar(heap,nueva_capacidad);
		if (redimension == false) return false;
	}
	heap->datos[heap->cant] = elem;
	heap->cant += 1;
	//Aca deberia hacer Upheap
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
		size_t nueva_capacidad = heap->cap / COEF_REDIM;
		heap_redimensionar(heap,nueva_capacidad);
	}
	void* elem = heap->datos[0];
	//Aca pongo el ultimo en la primer posicion y hago Downheap
	heap->cant-=1;
	return elem;
}
