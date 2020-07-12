#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define CANT_ELEM_PRUEBA_3 5000
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
 //FUNCION AUXILIAR PARA APILAR
 pila_t* apilar_aux(pila_t *pila, int n){
	 int vec_aux[n];
	 for(int i = 0; i< n; i++){
		vec_aux[i] = i;
		pila_apilar(pila, &vec_aux[i]);
	}
	return pila;
 }
 
	
 
void prueba_crear_y_destruir(){
	printf("\nINICIO DE PRUEBA CREACION Y DESTRUCCION\n");
	//Creo la pila 
    pila_t* pila = pila_crear();
    print_test("La pila fue creada", pila != NULL);
    
    //Destruyo la pila
    pila_destruir(pila);
    print_test("La pila fue eliminada", true);

}

void prueba_apilar_y_desapilar(){
	printf("\nINICIO DE PRUEBA APILAR Y DESAPILAR\n");
	pila_t* pila = pila_crear();
	
    //Apilo un 5
    int valor_apilado[] = {5};
    
    print_test("Se apila correctamente", pila_apilar(pila, &valor_apilado[0]));
    
    //Desapilo y chequeo que sea el valor que acabo de apilar
    int* valor_desapilado;
    valor_desapilado = pila_desapilar(pila);
    print_test("Se desapila correctamente", *valor_desapilado == valor_apilado[0]);
    
    //Destruyo la pila
    pila_destruir(pila);
    
}

void prueba_volumen(){
	printf("\nINICIO DE PRUEBA DE VOLUMEN\n");
	//Creo la pila 
    pila_t* pila = pila_crear();
    
    //Apilo elementos segun la constante definida, en este caso es 5000
    int vec_aux[CANT_ELEM_PRUEBA_3];
	for(int i = 0; i < CANT_ELEM_PRUEBA_3; i++){
		vec_aux[i] = i;
		pila_apilar(pila, &vec_aux[i]);
	}
	
	//Desapilo hasta que este vacia
	int n = CANT_ELEM_PRUEBA_3; //Defino una variable para iterar el vector y comparar con cada tope
	bool valido = true; //Inicializo una bandera en true
	int *tope;
	while(!pila_esta_vacia(pila)&&valido){
		tope = pila_desapilar(pila);
		//Si en algun momento el tope es distinto al valor acorde en el vector, activo la bandera
		if(*tope != vec_aux[n-1]){
			valido = false;
		}
		n--;
	}
	print_test("Se desapilo correctamente todos los valores comprobando el invariante", valido);
    
    //Destruyo la pila
    pila_destruir(pila);
}

void prueba_apilar_null(){
	printf("\nINICIO DE PRUEBA APILAR NULL\n");
	//Creo la pila 
    pila_t* pila = pila_crear();
    
    //Apilo un NULL
    int *puntero_null;
    puntero_null = NULL;
    print_test("Se apila elemento NULL correctamente", pila_apilar(pila, puntero_null));
    
    //Destruyo la pila
    pila_destruir(pila);
}

void prueba_desapilar_hasta_vacio(){
	printf("\nINICIO DE PRUEBA BORDE: DESAPILAR HASTA QUE ESTA VACIA SE COMPORTA COMO RECIEN CREADA\n");
	//Creo la pila 
    pila_t* pila = pila_crear();
    
    //Apilo  valores
	pila = apilar_aux(pila, 8);
	
	//~ //Desapilo hasta que quede vacia
	int *tope;
	while(!pila_esta_vacia(pila)){
		tope = pila_desapilar(pila);
	}
    
    //Me fijo si se comporta como recien creada 
    printf("Prueba si pila desapilada hasta que quede vacia se comporta como pila recien creada\n");
    tope = pila_desapilar(pila);
    print_test("Desapilar una pila vacia devuelve NULL", tope == NULL);
    
    tope = pila_ver_tope(pila);
    print_test("Ver tope de una pila vacia devuelve NULL", tope == NULL);
    
    print_test("Pila recien creada esta vacia", pila_esta_vacia(pila));
    
    //Destruyo la pila
    pila_destruir(pila);
}

void prueba_desapilar_y_ver_tope_invalidos(){
	printf("\nINICIO DE PRUEBA BORDE 2: DESAPILAR Y VER_TOPE EN RECIEN CREADA ES INVALIDO\n");
	//Creo la pila 
    pila_t* pila = pila_crear();
   
   //Desapilo y miro el tope de una pila recien creada
    int *tope;
    
    tope = pila_desapilar(pila);
    print_test("Desapilar una pila recien creada devuelve NULL", tope == NULL);
    
    tope = pila_ver_tope(pila);
    print_test("Ver tope de una pila recien creada devuelve NULL", tope == NULL);
    
    //Destruyo la pila
    pila_destruir(pila);
    
}

void prueba_pila_recien_creada_esta_vacia(){
	printf("\nINICIO DE PRUEBA BORDE 3: PILA RECIEN CREADA TIENE QUE ESTAR VACIA\n");
	//Creo la pila 
    pila_t* pila = pila_crear();
   
    //Me fijo si una pila recien creada esta vacia
	print_test("Pila recien creada esta vacia", pila_esta_vacia(pila));
    
    //Destruyo la pila
    pila_destruir(pila);
    
}

void prueba_desapilar_y_ver_tope_2(){
	printf("\nINICIO DE PRUEBA 4: DESAPILAR Y VER TOPE EN PILA APILADA Y DESAPILADA ES INVALIDO\n");
	//Creo la pila 
    pila_t* pila = pila_crear();
    
    //Apilo valores 
	pila = apilar_aux(pila, 8);
	
	//Desapilo hasta que quede vacia
	int *tope;
	while(!pila_esta_vacia(pila)){
		tope = pila_desapilar(pila);
	}
    
    //Me fijo si se comporta como recien creada
    tope = pila_desapilar(pila);
    print_test("Desapilar una pila que se apilo y desapilo hasta estar vacia devuelve NULL", tope == NULL);
    
    tope = pila_ver_tope(pila);
    print_test("Ver tope de una pila una pila que se apilo y desapilo hasta estar vacia devuelve NULL", tope == NULL);
    
    //Destruyo la pila
    pila_destruir(pila);
}



void pruebas_pila_alumno() {
	prueba_crear_y_destruir();
	prueba_apilar_y_desapilar();
	prueba_volumen();
	prueba_apilar_null();
	prueba_desapilar_hasta_vacio();
	prueba_desapilar_y_ver_tope_invalidos();
	prueba_pila_recien_creada_esta_vacia();
	prueba_desapilar_y_ver_tope_2();
}

