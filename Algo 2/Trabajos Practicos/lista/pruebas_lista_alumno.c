#include "testing.h"
#include "lista.h"
#include "pila.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define CANT_ELEM_PRUEBA_VOLUMEN 5000



void prueba_crear_y_destruir_sin_funcion(){
	printf("\nINICIO DE PRUEBA CREACION Y DESTRUCCION SIN FUNCION DE DESTRUCCION DE DATOS\n");
	lista_t* lista = lista_crear();
	print_test("La lista fue creada", lista != NULL);
	lista_destruir(lista, NULL);
	print_test("La lista fue eliminada", true);
}

void destruir_dato_pila(void* dato){
	pila_destruir(dato);
}

pila_t* crear_y_cargar_pila(int n){
	pila_t* pila = pila_crear();
	
	int vec[n];
	for(int i = 0; i < n; i++){
		vec[i] = i;
		pila_apilar(pila, &vec[i]);
	}
	return pila;
}

void prueba_destruir_lista_con_funcion(){
	printf("\nINICIO DE PRUEBA DESTRUCCION con FUNCION DE DESTRUCCION DE DATOS\n");
	void (*funcion_destruir) (void*);
	funcion_destruir = destruir_dato_pila;
	
	lista_t* lista = lista_crear();
	//La funcion crear y cargar pila crea una  pila, la llena y la devuelve.
	lista_insertar_ultimo(lista, crear_y_cargar_pila(5));
	lista_insertar_ultimo(lista, crear_y_cargar_pila(10));
	lista_insertar_ultimo(lista, crear_y_cargar_pila(15));
	
	lista_destruir(lista, funcion_destruir);
	print_test("La lista se destruyo con funcion de destruccion de datos", true);
	
}

void prueba_insertar_primero_y_borrar(){
	printf("\nINICIO DE PRUEBA INSERTAR PRIMERO Y BORRAR\n");
	lista_t* lista = lista_crear();
	int valores[] = {5, 10};
	print_test("Inserto  1 elemento primero", lista_insertar_primero(lista, &valores[0]));
	print_test("Inserto  otro elemento primero", lista_insertar_primero(lista, &valores[1]));
	
	print_test("EL 1er elemnto es el correcto", lista_ver_primero(lista) == &valores[1]);
	print_test("El 2do elemento es el correcto", lista_ver_ultimo(lista) == &valores[0]);
	
	lista_destruir(lista, NULL);
	
}

void prueba_insertar_ultimo_y_borrar(){
	printf("\nINICIO DE PRUEBA INSERTAR ULTIMO Y BORRAR\n");
	lista_t* lista = lista_crear();
	int valores[] = {5, 10};
	print_test("Inserto  1 elemento ultimo", lista_insertar_ultimo(lista, &valores[0]));
	print_test("Inserto  otro elemento ultimo", lista_insertar_ultimo(lista, &valores[1]));
	
	print_test("EL 1er elemnto es el correcto", lista_ver_primero(lista) == &valores[0]);
	print_test("El 2do elemento es el correcto", lista_ver_ultimo(lista) == &valores[1]);
	
	lista_destruir(lista, NULL);
}

void prueba_insertar_null_prim(){
	printf("\nINICIO DE PRUEBA INSERTAR NULL PRIMERO\n");
	lista_t* lista = lista_crear();
	print_test("Inserto  Elemento NULL", lista_insertar_primero(lista, NULL));
	
	print_test("EL  elemnto es NULL", lista_ver_primero(lista) == NULL);
	lista_destruir(lista, NULL);
}

void prueba_insertar_null_ult(){
	printf("\nINICIO DE PRUEBA INSERTAR NULL ULTIMO\n");
	lista_t* lista = lista_crear();
	print_test("Inserto  Elemento NULL", lista_insertar_ultimo(lista, NULL));
	
	print_test("EL  elemnto es NULL", lista_ver_primero(lista) == NULL);
	lista_destruir(lista, NULL);
}

void prueba_borrar_hasta_vacio_insertando_ult(){
	printf("\nINICIO DE PRUEBA BORDE 1: BORRAR ELEMENTOS HASTA QUE ESTE VACIA LA LISTA Y QUE SE COMPORTE COMO RECIEN CREADA (INSERTANDO ULTIMO)\n");
	lista_t* lista = lista_crear();
	int vec[7];
    //Inserto 7 valores
    for(int i = 0; i < 7; i++){
		vec[i] = i;
		lista_insertar_ultimo(lista, &vec[i]);
	}
	//Elimino los 7 valores
	for(int i = 0; i < 7; i++){
		lista_borrar_primero(lista);
	}
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Ver primer elemento de lista vacia devuelve NULL", lista_ver_primero(lista) == NULL);
	print_test("Como no puedo eliminar elementode una lista vacia devuelve NULL", lista_borrar_primero(lista) == NULL);
	lista_destruir(lista, NULL);
}
void prueba_borrar_hasta_vacio_insertando_prim(){
	printf("\nINICIO DE PRUEBA BORDE 1: BORRAR ELEMENTOS HASTA QUE ESTE VACIA LA LISTA Y QUE SE COMPORTE COMO RECIEN CREADA (INSERTANDO PRIMERO)\n");
	lista_t* lista = lista_crear();
	int vec[7];
    //Inserto 7 valores
    for(int i = 0; i < 7; i++){
		vec[i] = i;
		lista_insertar_primero(lista, &vec[i]);
	}
	//Elimino los 7 valores
	for(int i = 0; i < 7; i++){
		lista_borrar_primero(lista);
	}
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Ver primer elemento de lista vacia devuelve NULL", lista_ver_primero(lista) == NULL);
	print_test("Como no puedo eliminar elementode una lista vacia devuelve NULL", lista_borrar_primero(lista) == NULL);
	lista_destruir(lista, NULL);
}

void prueba_lista_recien_creada(){
	printf("\nINICIO DE PRUEBA BORDE 2: BORRAR Y VER PRIMERO EN  LISTA RECIEN CREADA ES INVALIDO\n");
	lista_t* lista = lista_crear();
	print_test("Ver primer elemento de lista recien creada devuelve NULL", lista_ver_primero(lista) == NULL);
	print_test("Eliminar elemento de una lista recien crada devuelve NULL", lista_borrar_primero(lista) == NULL);
	lista_destruir(lista, NULL);
}

void prueba_lista_vacia(){
	printf("\nINICIO DE PRUEBA BORDE 3: LISTA RECIEN CREADA ESTA VACIA \n");
	lista_t* lista = lista_crear();
	print_test("Lista recien creada tiene largo 0", lista_largo(lista) == 0);
	print_test("Lista recien creada esta vacia", lista_esta_vacia(lista));
	lista_destruir(lista, NULL);
}

void prueba_volumen_ultimo(){
	printf("\nINICIO DE PRUEBA DE VOLUMEN INSERTANDO ULTIMO\n");
	lista_t* lista = lista_crear();
	int vec[CANT_ELEM_PRUEBA_VOLUMEN];
	for(int i = 0; i < CANT_ELEM_PRUEBA_VOLUMEN; i++){
		vec[i] = i;
		lista_insertar_ultimo(lista, &vec[i]);
	}
	//Uso una bandera booleana para salir del while si algun dato no es el correcto 
	bool valido = true;
	int* dato;
	int i = 0;
	while(!lista_esta_vacia(lista) && valido){
		dato = lista_borrar_primero(lista);
		//~ print_test("EL valor eliminado fue el correcto", *dato == vec[i]);
		if(*dato != vec[i]){
			valido = false;
		}
		i++;
	}
	print_test("Todos los valores eliminados fueron los correctos", valido);
	lista_destruir(lista, NULL);
}

void prueba_volumen_primero(){
	printf("\nINICIO DE PRUEBA DE VOLUMEN INSERTANDO PRIMERO\n");
	lista_t* lista = lista_crear();
	int vec[CANT_ELEM_PRUEBA_VOLUMEN];
	for(int i = 0; i < CANT_ELEM_PRUEBA_VOLUMEN; i++){
		vec[i] = i;
		lista_insertar_primero(lista, &vec[i]);
	}
	//Uso una bandera booleana para salir del while si algun dato no es el correcto 
	bool valido = true;
	int* dato;
	int i = CANT_ELEM_PRUEBA_VOLUMEN-1;
	while(!lista_esta_vacia(lista) && valido){
		dato = lista_borrar_primero(lista);
		//~ print_test("EL valor eliminado fue el correcto", *dato == vec[i]);
		if(*dato != vec[i]){
			valido = false;
		}
		i--;
	}
	print_test("Todos los valores eliminados fueron los correctos", valido);
	lista_destruir(lista, NULL);
}

void prueba_insertar_intercalado(){
	printf("\nINICIO DE PRUEBA INSERTAR INTERCALADO\n");
	lista_t* lista = lista_crear();
	int valores[] = {5, 10, 15, 20, 25};
	
	print_test("Inserto  el 5 elemento ultimo", lista_insertar_ultimo(lista, &valores[0]));
	print_test("Inserto  el 10 elemento primero", lista_insertar_primero(lista, &valores[1]));
	print_test("Inserto  el 15 elemento ultimo", lista_insertar_ultimo(lista, &valores[2]));
	print_test("Inserto  el 20 elemento primero", lista_insertar_primero(lista, &valores[3]));
	print_test("Inserto  el 25 elemento ultimo", lista_insertar_ultimo(lista, &valores[4]));
	printf("La lista quedaria con los valores de la siguiente manera {20, 10, 5, 15, 25}\n");
	int* dato = lista_borrar_primero(lista);
	print_test("EL primer elemento es el 20", *dato == valores[3]);
	dato = lista_borrar_primero(lista);
	print_test("EL segundo elemento es el 10", *dato == valores[1]);
	dato = lista_borrar_primero(lista);
	print_test("EL tercer elemento es el 5", *dato == valores[0]);
	dato = lista_borrar_primero(lista);
	print_test("EL cuarto elemento es el 15", *dato == valores[2]);
	dato = lista_borrar_primero(lista);
	print_test("EL quinto elemento es el 25", *dato == valores[4]);
	
	lista_destruir(lista, NULL);
}



bool sumar_elementos(void *elemento, void *extra){
   *(int*) extra += *(int*) elemento;
    return true; 
}


void prueba_sumar_elementos(lista_t *lista){	
	
    printf("\nINICIO DE PRUEBA SUMAR TODOS LOS ELEMENTOS\n");
    int acum1 = 0;
    lista_iterar(lista, sumar_elementos, &acum1);
    int acum2 = 0;
    while(!lista_esta_vacia(lista)){
		acum2 += *(int*)lista_ver_primero(lista);
		lista_borrar_primero(lista);
	}
    print_test("La suma de los elementos con iterador interno fue correcta", acum1 == acum2);
}

void pruebas_iterador_interno(){
	printf("\nINICIO DE PRUEBAS ITERADOR INTERNO\n");
    lista_t *lista = lista_crear();
	
	int vec[10];
    //Inserto 10 valores
    for(int i = 0; i < 10; i++){
		vec[i] = i+3;
		lista_insertar_ultimo(lista, &vec[i]);
	}

    prueba_sumar_elementos(lista);

    lista_destruir(lista, NULL);
}

void insertar_iter_principio(){
	printf("\nINSERTAR ELEMENTO EN LA POSICION DONDE SE CREA EL ITERADOR ES INSERTAR AL PRINCIPIO\n");
	 lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    int dato = 10;
	lista_iter_insertar(iter, &dato);
    print_test("El elemento insertado es el correcto", lista_ver_primero(lista) == &dato);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

void insertar_iter_final(){
	printf("\nINSERTAR ELEMENTO CON EL ITERADOR AL FINAL ES INSERTAR AL FINAL\n");
	lista_t *lista = lista_crear();
    int vec[10];
    //Inserto 10 valores
    for(int i = 0; i < 10; i++){
		vec[i] = i;
		lista_insertar_ultimo(lista, &vec[i]);
	}
	
    lista_iter_t *iter = lista_iter_crear(lista);
    //Avanzo el iterador hasta el final
    while (!lista_iter_al_final(iter))
    {
        lista_iter_avanzar(iter);
    }
    int dato = 10;
    //Inserto al final
	lista_iter_insertar(iter, &dato);
    print_test("El elemento insertado es el correcto", lista_ver_ultimo(lista) == &dato);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}
void insertar_item_medio(){
	printf("\nINSERTAR ELEMENTO EN EL MEDIO LO INSERTA EN LA POSICION CORRECTA\n");
	lista_t *lista = lista_crear();
	int vec[5];
    //Inserto 5 elementos
    for(int i = 0; i < 5; i++){
		vec[i] = i;
		lista_insertar_ultimo(lista, &vec[i]);
	}
	lista_iter_t *iter = lista_iter_crear(lista);
	lista_iter_avanzar(iter);
	lista_iter_avanzar(iter);
	int valor = 10;
	lista_iter_insertar(iter, &valor);
	//Se deberia haber insertado en la segunda posicion, ya que el iterador estaba en esa posicion 0-1-VALOR-2-3-4
	void* dato;
	dato = lista_borrar_primero(lista);//0
	dato = lista_borrar_primero(lista);//1
	dato = lista_borrar_primero(lista);//VALOR INSERTADO
	print_test("EL dato se inserto en la psoicion correcta", *(int*)dato == valor);
	
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
}

void eliminar_primer_elemento_iter(){
	printf("\nINICIO PRUEBA ELIMINAR PRIMER ELEMENTO DE LA LISTA\n");
	lista_t *lista = lista_crear();
	int vec[5];
    //Inserto 5 elementos
    for(int i = 0; i < 5; i++){
		vec[i] = i;
		lista_insertar_ultimo(lista, &vec[i]);
	}
	//La lista esta asi: 0-1-2-3-4
	lista_iter_t *iter = lista_iter_crear(lista);
	lista_iter_borrar(iter);
	//Si borro el primer elemento, el 0, el nuevo primer elemento debe ser el 1
	print_test("El primer elemento es el correcto", *(int*)lista_ver_primero(lista) == vec[1]);
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
}

void eliminar_ultimo_elemento_iter(){
	printf("\nINICIO PRUEBA ELIMINAR ULTIMO ELEMENTO DE LA LISTA\n");
	lista_t *lista = lista_crear();
	int vec[5];
    //Inserto 5 elementos
    for(int i = 0; i < 5; i++){
		vec[i] = i;
		lista_insertar_ultimo(lista, &vec[i]);
	}
	//La lista esta asi: 0-1-2-3-4
	lista_iter_t *iter = lista_iter_crear(lista);
	//Avanzo el iterador hasta el ultimo elemento
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
	lista_iter_borrar(iter);
	//Si borro el ultimo elemento, el 4, el nuevo ultimo elemento debe ser el 3
	print_test("El ultimo elemento es el correcto", *(int*)lista_ver_ultimo(lista) == vec[3]);
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
}

void eliminar_elemento_medio_iter(){
	printf("\nINICIO PRUEBA ELIMINAR ELEMENTO DEL MEDIO DE LA LISTA\n");
	lista_t *lista = lista_crear();
	int vec[5];
    //Inserto 5 elementos
    for(int i = 0; i < 5; i++){
		vec[i] = i;
		lista_insertar_ultimo(lista, &vec[i]);
	}
	//La lista esta asi: 0-1-2-3-4
	lista_iter_t *iter = lista_iter_crear(lista);
	//Avanzo el iterador hasta la tercera posicion
    lista_iter_avanzar(iter);//1
    lista_iter_avanzar(iter);//2
    lista_iter_avanzar(iter);//3
	lista_iter_borrar(iter);
	//Me fijo si la lista quedo como deberia quedar, si elimino todos los elementos y esta vacia, significa que el 3 fue eliminado correctamente
	//La lista ahora deberia ser 0-1-2-4
	print_test("El primer elemento es el correcto",  *(int*)lista_borrar_primero(lista) == vec[0]);
	print_test("El segundo elemento es el correcto", *(int*)lista_borrar_primero(lista) == vec[1]);
	print_test("El tercer elemento es el correcto",  *(int*)lista_borrar_primero(lista) == vec[2]);
	print_test("El cuarto elemento es el correcto",  *(int*)lista_borrar_primero(lista) == vec[4]);
	print_test("Me aseguro que no hay mas elementos", lista_esta_vacia(lista));
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
}

void pruebas_iterador_externo(){
	printf("\nINICIO DE PRUEBAS ITERADOR INTERNO\n");
    insertar_iter_principio();
    insertar_iter_final();
    insertar_item_medio();
    eliminar_primer_elemento_iter();
    eliminar_ultimo_elemento_iter();
    eliminar_elemento_medio_iter();
}
void  pruebas_lista_alumno(){
	prueba_crear_y_destruir_sin_funcion();
	prueba_insertar_primero_y_borrar();
	prueba_insertar_ultimo_y_borrar();
	prueba_insertar_null_prim();
	prueba_insertar_null_ult();
	prueba_borrar_hasta_vacio_insertando_ult();
	prueba_borrar_hasta_vacio_insertando_prim();
	prueba_lista_recien_creada();
	prueba_lista_vacia();
	prueba_volumen_ultimo();
	prueba_volumen_primero();
	prueba_insertar_intercalado();
	pruebas_iterador_interno();
	pruebas_iterador_externo();
	prueba_destruir_lista_con_funcion();
	
}



