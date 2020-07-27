#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* Se trata de una lista linkeada de punteros genéricos.  La lista en sí está definida en el .c.  */

struct lista;
struct lista_iter;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

/*
 * Primitivas de la lista
 * */

//Crea una lista
//Post: La lista fue creada, en caso de error el puntero devuelto sra NULL
lista_t* lista_crear(void);

//Devuelve true si la lista no tiene elementos enlistados. False en caso contrario
//Pre: La lista ue creada
bool lista_esta_vacia(const lista_t *lista);

//Agrega un nuevo nodo con el dato recibido al principio de la lista.
// Devuelve false en caso de fallo
//Pre: La lista fue creada
//Post: Se agrego un nuevo elemento al principio
bool lista_insertar_primero(lista_t *lista, void *dato);

//Agrega un nuevo nodo con el dato recibido al final de la lista.
// Devuelve false en caso de fallo
//Pre: La lista fue creada
//Post: Se agrego un nuevo elemento al final
bool lista_insertar_ultimo(lista_t *lista, void *dato);

//Elimina el primer nodo de la lista y devuelve el dato del nodo liberado.
//Si la lista esta vacia devuelve NULL
//Pre: La lista fue creada
//Post: Se devolvio el primer valor de la lista si hay elementos, si esta vacia
//se devolvio NULL
void* lista_borrar_primero(lista_t *lista);

//Devuelve el dato de la primera posicion de la lista. En caso de que este vacia
//se devuelve NULL
//Pre: La lista fue creada
//Post: Se devolvio el primer dato de la lista, si esta contiene elementos. 
//En caso contrario devuelve NULL
void* lista_ver_primero(const lista_t *lista);

//Devuelve el dato de la ultima posicion de la lista. En caso de que este vacia
//se devuelve NULL
//Pre: La lista fue creada
//Post: Se devolvio el ultimo dato de la lista, si esta contiene elementos. 
//En caso contrario devuelve NULL
void* lista_ver_ultimo(const lista_t* lista);

//Devuelve el largo de la lista
//Pre: la lista fue creada
//Post: Devuelve el largo de la lista
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe una función destruir_dato por parámetro,
// se llama a destruir_dato para cada elemento de la lista.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL si no se utiliza
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


/*
 * 	PRIMITIVAS DEL ITERADOR EXTERNO
 * */

// Crea el iterador
//Post: Se creo el iterador
lista_iter_t *lista_iter_crear(lista_t *lista);

//Avanza una posicion del iterador al siguiente elemento. 
//Pre: EL iterador fue creado
//Post: El actual del iterador se movio un elemento adelante. Devuelve false si ya estoy al final de la lista
bool lista_iter_avanzar(lista_iter_t *iter);//TENER EN CUENTA SI INTENTO AVANZAR CUANDO EL ITER APUNTA A NULL

//Devuelve el dato al que esta apuntando el iterador. Devuelve NULL si apunta a NULL. 
//Pre: El iterador fue creado
//Post: Devuelve el dato apuntado por le iterador.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Indica si el iterador llego al final de la lista (en este caso especifico). Deveulve true si esta al final o false si no.
//Pre: El iterador fue creado
//Post: Devuelve true si esta al final de la lista, false en caso contrario
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iterador
//Pre: El iterador fue creado
//Post: El iterador fue destruido
void lista_iter_destruir(lista_iter_t *iter);

//Inserta un nuevo nodo entre el actual nodo que este apuntando el iterador, y el anterior. Devuelve false en caso de fallo
//Pre: El iterador fue creado
//Post: Se agrego un elemento entre el actual y el anterior. EL actual del iterador apunta al nuevo nodo, el siguiente del nuevo nodo apunta al que antes era el actual 
// y el siguiente del anterior apunta al nuevo nodo. Devuelve false en caso de fallo
bool lista_iter_insertar(lista_iter_t *iter, void *dato);//TENER EN CUENTA AMBOS CASOS BORDE EN DONDE TENGO QUE CAMBIAR LOS PUNTEROS DE PRIM Y ULT DE LA LISTA

//Elimina el nodo actual que este apuntando el iterador y devuelve el dato que contenia ese nodo.
//Pre: El iterador fue creado
//Post: Se elimino el nodo que apuntaba el iterador y se devolvio el dato. Se actualiza el siguiente del anterior y se ueve el actual hacie el elemento que apuntaba el nodo eliminado. 
void *lista_iter_borrar(lista_iter_t *iter);

//ITERADOR INTERNO
//Permite recorrer la lista en su totalidad, aunque con el return de la funcion visitar, se puede hacer un corte de control para frenr el recorrido
//No se maneja paso a paso como el iterador externo, y tampoco se puede crear ni destruir
//Pre: La lista fue creada y la funcion visitar fue implementada con los parametros validos. El extra puede estar o no
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

#endif // LISTA_H
