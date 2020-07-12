#include "cola.h"
#include <stdlib.h>

typedef struct nodo{
	void* dato;
	struct nodo* sig;
} nodo_t;

struct cola{
	nodo_t* prim;
	nodo_t* ult;
};

nodo_t* crear_nodo(void* valor, nodo_t *nodo_sig){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo) return NULL;
	nodo->dato = valor;
	nodo->sig = nodo_sig;
	return nodo;
}

cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));
	if(!cola) return NULL;
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}

bool cola_esta_vacia(const cola_t *cola){
	if(!cola->prim) return true;
	return false;
}

//CASOS BORDE ENCOLAR CUANDO ESTA VACIA, Y DESPUES DE DESENCOLAR ASEGURAR QUE NO QUEDE APUNTANDO A NADA
bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nodo = crear_nodo(valor, NULL);
		if(!nodo) return false;
	if(cola_esta_vacia(cola)){
		//Caso borde encolar cuando la cola esta vacia
		cola->prim = nodo;
		cola->ult = nodo;
		return true;
	}
	cola->ult->sig = nodo;
	cola->ult = nodo;
	return true;
}


void* cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	nodo_t* aux = cola->prim->sig;
	void* dato = cola->prim->dato;
	free(cola->prim);
	cola->prim = aux;
	if(cola_esta_vacia(cola)){
		cola->ult = NULL;
	}
	return dato;
}

void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	return cola->prim->dato;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void*)){
	if(!destruir_dato){
		//Si no se pasa ninguna funcion elimino todos los nodos y lbero la cola
		while(!cola_esta_vacia(cola)){
			cola_desencolar(cola);
		}
		free(cola);
		return;
	}
	//Si se paso una funcion aplico la misma para cada dato
	while(!cola_esta_vacia(cola)){
		void* dato = cola_desencolar(cola);
		destruir_dato(dato);
	}
	cola->ult = NULL;
	free(cola);
	return;
}
