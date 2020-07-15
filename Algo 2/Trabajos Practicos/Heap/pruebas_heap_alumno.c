#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int funcion_comparacion(const void* a, const void* b){
    if(*(int*)a == *(int*)b) return 0;
    if(*(int*)a > *(int*)b) return 1;
    return -1;
}
void prueba_crear_heap_vacio(){
    printf("~~INICIO DE PRUEBA DE HEAP VACIO~~\n");
    heap_t* heap = heap_crear(funcion_comparacion);
    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap ver elemento maximo, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap vacio esta vacio",  heap_esta_vacio(heap));
    print_test("Prueba heap desencolar elemento, es NULL, no existe", !heap_desencolar(heap));
    heap_destruir(heap, NULL);
}

void prueba_abb_insertar(){
	printf("~~INICIO DE PRUEBA DE INSERTAR EN HEAP~~\n");
    heap_t* heap = heap_crear(funcion_comparacion);
    int vector[] = {1,2,3};

    /* Inserta 1 valor y luego lo borra */
    //print_test("Prueba heap enclar un valor", heap_encolar(heap,&vector[0]));
    //print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    //print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[0]);
    //print_test("Prueba heap con un elemento no esta vacio", !heap_esta_vacio(heap));
    //print_test("Prueba heap elemento desencolado es el elemento encolado", *(int*)heap_desencolar(heap) == vector[0]);
    //print_test("Prueba heap la cantidad de elementos es 0 despues de desencolar", heap_cantidad(heap) == 0);
    //print_test("Prueba heap esta vacio despues de desencolar el unico elemento encolado ", heap_esta_vacio(heap));

    print_test("Prueba heap encolar un valor", heap_encolar(heap,&vector[1]));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[1]);
    print_test("Prueba heap con un elemento no esta vacio", !heap_esta_vacio(heap));
    
    print_test("Prueba heap encolar otro valor", heap_encolar(heap,&vector[2]));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver elemento maximo, es el correcto", *(int*) heap_ver_max(heap) == vector[2]);
    heap_destruir(heap, NULL);
}

void pruebas_heap_alumno(){
    //int vector[] = {1,2,3,4,5,6,7,8,9};
    //prueba_crear_heap_vacio();
    prueba_abb_insertar();
}