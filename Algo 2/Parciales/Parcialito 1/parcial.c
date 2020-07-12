#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void** pila_multifondo(pila_t* pila, size_t k){
	void** arr = calloc(sizeof(void*) * k);
	pila_t* pila_aux = pila_crear();
	if(pila_aux == NULL) return NULL; 
	//Invierto la pila
	for(int i = 0; !pila_esta_vacia(pila); i++){
		void* dato = pila_desapilar(pila);
		if(!pila_apilar(pila_aux, dato)){
			pila_destruir(pila_aux);
			free(arr);
			pila_apilar(pila, dato);
			return NULL
		}
	}
	//Me fijo los primeros k valores y paso cada elemento de nuevo a la pila orginal, dejandolo en su estado original
	for(int i = 0; !pila_esta_vacia(pila_aux) ; i++){
		void* dato = pila_desapilar(pila_aux);
		if (i<k){
			arr[i] = dato;
		}
		if(!pila_apilar(pila, dato)){
			pila_destruir(pila);
			free(arr);
			return NULL
		}
	}
	
	free(pila_aux);
	return arr;
}





int ejercicio_7(int* arr, size_t inicio, size_t fin, int k){
	if(inicio == fin) return arr[inicio];
	
	size_t medio = (fin + inicio) / 2;
	int izq = ejercicio_7(arr, inicio, medio);
	int der = ejercicio_7(arr, medio + 1, fin);
	dist = izq - der;
	if(dist != k) return arr[inicio] < arr[fin] ? arr[inicio] + k ; arr[inicio] - k;
	return izq;
	
}

/*	EJERCICIO 8
 * 
 * 
 * 
 * A) Depende. Hay que tener en cuenta que nuestro rango (k) es bastante grande, puede existir una diferencia de 20.000 o hasta 30.000 entre alumnos (de hecho, en las planillas de asignacion
 * de ejercicios hay alguien con padron 85.445 y yo por ejemplo tengo 105.493). Entonces si vamos a ordenar una lista mucho mas chica que ese rango, como la planilla, no conviene usar CountingSort 
 * ya que el orden no va a tender a O(n) debido a que k no estaria acotado con respecto a n (el orden de CountingSort es O(n + k)).
 * Pero si se ordena por ejemplo, todos los estudiantes que estan cursando ahora mismo la facultad, en ese caso CountingSort tendria sentido, ya que el valor de k estaria acotado en aproximadamente
 * 25/30 mil y estariamos viendo a miles de alumnos.  Y ahi el orden si seria O(n).
 * 
 * 
 * B)Serviria si la muestra es suficientemente grande para que countingsort sirva.
 * El orden de radixSort es O(d *(n + k)), en este caso (n + k) es el orden del algoritmo interno, y si usamos countingsort con 7 digitos quedaria O(7*n), que es O(n).
 * 
 * C) No podriamos usar BucketSort ya que no conocemos la distribucion de los datos, la podriamos asumir pero no sabemos con certeza. Tampoco sabemos si los datos estan uniformemente distribuidos, lo cual
 * asumiria que no porque tendriamos mucha gente de los ultimos anios (padrones de 102-xxx a 105-xxx) y mucha menos gente con padrones mas bajos
 * 
 * 
 * 
 * 
 * 
 * */
