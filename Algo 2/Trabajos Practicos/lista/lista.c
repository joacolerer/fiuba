#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct nodo{
	void* dato;
	struct nodo* sig;
} nodo_t;

struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

struct lista_iter{
	nodo_t* act;
	nodo_t* ant;
	lista_t* lista;
};


nodo_t* crear_nodo(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo) return NULL;
	nodo->dato = valor;
	return nodo;
}

lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* lista_iter = malloc(sizeof(lista_iter_t));
	if(!lista_iter) return NULL;
	lista_iter->act = lista->prim;
	lista_iter->ant = NULL;
	lista_iter->lista = lista;
	return lista_iter;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = crear_nodo(dato);
	if(!nodo) return false;
	
	//si la lista esta vacia el prim y ult apuntan al nodo creado
	if(lista_esta_vacia(lista)){
		lista->largo++;
		nodo->sig = NULL;
		lista->prim = nodo;
		lista->ult = nodo;
		return true;
	}
	lista->largo++;
	//si no esta vacia guardo un aux el que era primero asi cuando agrego al nuevo primero hago que apunte al que ahora es segundo
	nodo_t* nodo_aux = lista->prim;
	lista->prim = nodo;
	lista->prim->sig = nodo_aux;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo = crear_nodo(dato);
	if(!nodo) return false;
	nodo->sig = NULL;
	//si esta vacia el prim y ult apuntan al nodo creado
	if(lista_esta_vacia(lista)){
		lista->prim = nodo;
		lista->ult = nodo;
		lista->largo++;
		return true;
	}
	//si no apunto primero el sig del ultimo y despues cambio el ult
	lista->ult->sig = nodo;
	lista->ult = nodo;
	lista->largo++;
	return true;
}

void* lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	nodo_t* nodo_aux = lista->prim->sig;
	void* dato = lista->prim->dato;
	free(lista->prim);
	lista->prim = nodo_aux;
	lista->largo--;
	if(lista_esta_vacia(lista)){
		lista->ult = NULL;
	}
	return dato;
}

void* lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->prim->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	if(!destruir_dato){
		//Si no se pasa ninguna funcion elimino todos los nodos y lbero la lista
		while(!lista_esta_vacia(lista)){
			lista_borrar_primero(lista);
		}
		free(lista);
		return;
	}
	//Si se paso una funcion aplico la misma para cada dato
	while(!lista_esta_vacia(lista)){
		void* dato = lista_borrar_primero(lista);
		destruir_dato(dato);
	}
	free(lista);
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->act == NULL;
}


bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)){
		return false;
	}
	
	iter->ant = iter->act;
	iter->act = iter->ant->sig;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return NULL;
	return iter->act->dato;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	//Si el anterior es NULL significa que el iterador esta parado en el primer elemento e insertar aca es lo mismo que hacer lista_insertar_primero
	if(!iter->ant){
		if(!lista_insertar_primero(iter->lista, dato)) return false;
		iter->act = iter->lista->prim;
		return true;
	}
	//Si el actual es NULL significa que el iterador esta parado en el ultimo elemento e insertar aca es lo mismo que hacer lista_insertar_ultimo
	if(!iter->act){
		if(!lista_insertar_ultimo(iter->lista, dato)) return false;
		iter->act = iter->lista->ult;
		return true;
	}
	//Aca inserto entre el actual y el anterior
	
	nodo_t* nodo_aux = crear_nodo(dato);
	if(!nodo_aux) return false;
	//Actualizo el siguiente del anterior
	iter->ant->sig = nodo_aux;
	//Apunto el siguiente del nuevo nodo al actual
	nodo_aux->sig = iter->act;
	//Apunto el actual al nuevo nodo 
	iter->act = nodo_aux;
	iter->lista->largo++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_esta_vacia(iter->lista) || !iter->act){
		return NULL;
	}
	//Si el anterior es NULL significa que el iterador esta parado en el primer elemento y eliminar aca es lo mismo que hacer lista_borrar_primero
	if(!iter->ant){
		void* dato = lista_borrar_primero(iter->lista);
		iter->act = iter->lista->prim;
		return dato;
	}
	
	void* dato = iter->act->dato;
	iter->lista->largo--;
	
	//Si el iterador esta parado en el ultimo elemento, borrar tendria la logica de un "lista_borrar_ultimo". MOviendo el iterador al final de la lista cuando termina de borrar
	if(iter->act == iter->lista->ult){
		free(iter->act);
		//Actualizao el ult de la lista
		iter->lista->ult = iter->ant;
		//Actualizo el siguiente del ultimo a NULL asi se mantiene la lista correctamente
		iter->lista->ult->sig = NULL;
		//Muevo el actual del iterador al final de la lista
		iter->act = NULL;
		return dato;
	}
	//En este caso borro un elemento en el medio de la lista
	//Actualizo la referencia asi se sigue comportando como una lista correctanebte
	iter->ant->sig = iter->act->sig;
	free(iter->act);
	//Actualizo el actual del iterador
	iter->act = iter->ant->sig;
	return dato;
}

//ITERADOR INTERNO
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	nodo_t* actual = lista->prim;
	bool salida = true;
	void* dato;
	while(actual != NULL && salida){
		dato = actual->dato;
		salida = visitar(dato, extra);
		actual = actual->sig;
	}
}


