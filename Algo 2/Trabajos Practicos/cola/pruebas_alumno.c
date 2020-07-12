#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define CANT_ELEM_PRUEBA_3 5000
void prueba_crear_y_destruir(){
	printf("\nINICIO DE PRUEBA CREACION Y DESTRUCCION\n");
	cola_t* cola = cola_crear();
	print_test("La cola fue creada", cola != NULL);
	
	cola_destruir(cola, NULL);
    print_test("La Cola fue eliminada", true);
}

void prueba_encolar_y_desencolar(){
	printf("\nINICIO DE PRUEBA APILAR Y DESAPILAR\n");
	cola_t* cola = cola_crear();
	
	int valores[] = {5, 10};
	
	print_test("Se encola correctamente 1 elemento", cola_encolar(cola, &valores[0]));
	print_test("Se encola correctamente 2 elementos", cola_encolar(cola, &valores[1]));
	
	int* valor_desencolado = cola_desencolar(cola);
	print_test("Se desencola correctamente 1 elemento", valor_desencolado == &valores[0]);
	valor_desencolado = cola_desencolar(cola);
	print_test("Se desencola correctamente 2 elementos", valor_desencolado == &valores[1]);
	cola_destruir(cola, NULL);
}

void prueba_volumen(){
	printf("\nINICIO DE PRUEBA DE VOLUMEN\n");
	cola_t* cola = cola_crear();
	int vec[CANT_ELEM_PRUEBA_3];
	for(int i = 0; i < CANT_ELEM_PRUEBA_3; i++){
		vec[i] = i;
		cola_encolar(cola, &vec[i]);
	}
	bool valido = true;
	int* desencolado;
	int i = 0;
	while(!cola_esta_vacia(cola) && valido){
		desencolado = cola_desencolar(cola);
		if(*desencolado != vec[i]){
			valido = false;
		}
		i++;
	}
	print_test("El valor desencolado es el correcto y cumple el invariante", valido);
	cola_destruir(cola, NULL);

}

void prueba_apilar_null(){
	printf("\nINICIO DE PRUEBA ENCOLAR NULL\n");	
    cola_t* cola = cola_crear();
    
    //Apilo un NULL
    int *puntero_null = NULL;
    print_test("Se encola elemento NULL correctamente", cola_encolar(cola, puntero_null));
	
	cola_destruir(cola, NULL);
}

void prueba_desencolar_hasta_vacio(){
	printf("\nINICIO DE PRUEBA BORDE: DESENCOLAR HASTA QUE ESTA VACIA SE COMPORTA COMO RECIEN CREADA\n");
    cola_t* cola = cola_crear();
    int vec[7];
    //Encolo 7 valores
    for(int i = 0; i < 7; i++){
		vec[i] = i;
		cola_encolar(cola, &vec[i]);
	}
    //Desencolo 7 valores
    for(int i = 0; i < 7; i++){
		cola_desencolar(cola);
	}
	printf("Prueba si cola desencolada hasta que quede vacia se comporta como cola recien creada\n");
    print_test("Cola recien creada esta vacia", cola_esta_vacia(cola));
    int* desencolado = cola_desencolar(cola);
    print_test("Desencolar una cola recien creada es invalido", desencolado == NULL);
    int* primero = cola_ver_primero(cola);
    print_test("Ver primero en una cola recien creada es invalido", primero == NULL);
    
	
	cola_destruir(cola, NULL);
}
void prueba_desencolar_y_ver_primero_invalidos(){
	printf("\nINICIO DE PRUEBA BORDE 2: DESENCOLAR Y VER_PRIMERO EN RECIEN CREADA ES INVALIDO\n");
    cola_t* cola = cola_crear();
    
    int* desencolado = cola_desencolar(cola);
    print_test("Desencolar una cola recien creada es invalido", desencolado == NULL);
    int* primero = cola_ver_primero(cola);
    print_test("Ver primero en una cola recien creada es invalido", primero == NULL);
    
    cola_destruir(cola, NULL);
}

void prueba_cola_recien_creada_esta_vacia(){
	printf("\nINICIO DE PRUEBA BORDE 3: COLA RECIEN CREADA TIENE QUE ESTAR VACIA\n");
    cola_t* cola = cola_crear();
    
    print_test("Cola recien creada esta vacia", cola_esta_vacia(cola));
    
    cola_destruir(cola, NULL);
}

void prueba_desencolar_y_ver_primero_2(){
	printf("\nINICIO DE PRUEBA 4: DESENCOLAR Y VER PRIMERO EN COLA ENCOLADA Y DESENCOLADA ES INVALIDO\n");
    cola_t* cola = cola_crear();
    int vec[5];
    //Encolo 7 valores
    for(int i = 0; i < 5; i++){
		vec[i] = i;
		cola_encolar(cola, &vec[i]);
	}
    //Desencolo 7 valores
    for(int i = 0; i < 5; i++){
		cola_desencolar(cola);
	}
    int* desencolado = cola_desencolar(cola);
    print_test("Desencolar una cola que se encolo y desencolo hasta estar vacia es invalido", desencolado == NULL);
    int* primero = cola_ver_primero(cola);
    print_test("Ver primero en una cola que se encolo y desencolo hasta estar vacia es invalido", primero == NULL);
    
    cola_destruir(cola, NULL);
}

void prueba_destruccion_sin_funcion(){
	printf("\nINICIO DE PRUEBA 9\n");
	cola_t* cola = cola_crear();
	
	int vec[10];
    //Encolo 7 valores
    for(int i = 0; i < 10; i++){
		vec[i] = i;
		cola_encolar(cola, &vec[i]);
	}
	cola_destruir(cola, NULL);
	print_test("La cola cargada se destruyo sin funcion de destruccion de datos", true);
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

void prueba_destruccion_con_funcion(){
	printf("\nINICIO DE PRUEBA 10\n");
	
	void (*funcion_destruir) (void*);
	funcion_destruir = destruir_dato_pila;
	
	cola_t* cola = cola_crear();
	pila_t* pila1 = crear_y_cargar_pila(10);
	pila_t* pila2 = crear_y_cargar_pila(2);
	pila_t* pila3 = crear_y_cargar_pila(5);
	
	cola_encolar(cola, pila1);
	cola_encolar(cola, pila2);
	cola_encolar(cola, pila3);

	cola_destruir(cola, funcion_destruir);
	print_test("La cola cargada se destruyo con funcion de destruccion de datos", true);
}
   


void pruebas_cola_alumno() {
	prueba_crear_y_destruir();
	prueba_encolar_y_desencolar();
	prueba_volumen();
	prueba_apilar_null();
	prueba_desencolar_hasta_vacio();
	prueba_desencolar_y_ver_primero_invalidos();
	prueba_cola_recien_creada_esta_vacia();
	prueba_desencolar_y_ver_primero_2();
	prueba_destruccion_sin_funcion();
	prueba_destruccion_con_funcion();
}
