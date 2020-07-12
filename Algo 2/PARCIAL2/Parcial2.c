#include "lista.h"
#include "hash.h"
/*
    Joaquin Matias Lerer
    Padron: 105.493
*/
// EJERCICIO 2
/*
    a) Falso, ya que podemos implementar una prioridad nueva nosotros (una funcion de comparacion), y podriamos hacer heapify al heap (heap es
    un arreglo y por eso, es valido hacer esta operacion). Heapify va a realizar downheap del ultimo al primero utilizando cada vez los valores
    del heap en base a la nueva funcion de prioridad, esto haria que se forme un nuevo heap con esta prioridad. No hay necesidad alguna de desencolar 
    todos los elementos y volver a encolarlos.
    Y heapify es un algoritmo que corre en O(n), ya que por mas que haga constantemente donwheap(que cuesta O(log n)), sabemos que en la mitad del arreglo
    las operaciones cuestan 0, ya que son hojas. Y resulta que cuanto mas alto sea el nivel tenemos menos nodos, en relacion al total,
    a los cuales simplemente le cuesta muy poco hacer ese downheap extra y debido a esto, resulta que es lineal O(n), lo cual es mejor que O(n log n).
    b) Es verdadero
    c) Diria que es falso. Realizar una cola de prioridad te dara otras ventajas, como encolar en O(1). Pero el objetivo del heap es que puede mantener una prioridad sin favorecer  necesariamente una funcionalidad. 
    Al implementar un heap las operaciones de encolar y desencolar resultaran en O(log n), obteniendo asi un "balance" entre ambas operaciones. 
    Ademas esta implementacion empeora notablemente la cola, haciendo que el desencolar sea O(n), en vez de O(1), lo cual no tiene sentido alguno.
*/



// EJERCICIO 3A

ab_t* buscar_clave(ab_t* ab, const char* clave){
    if(!ab) return NULL;
    if(strcmp(ab->clave, clave) == 0) return ab;
    //Llamo a ambos lados
    ab_t* ab_izq = buscar_clave(ab->izq, clave);
    ab_t* ab_der = buscar_clave(ab->der, clave);
    //si ambos lados son null significa que no encontramos por ese camino
    if(!ab_izq && !ab_der) return NULL;
    //Si alguno no es null significa que ahi encontramos la clave pedida, entonces con un if detectamos cual de los dos no es null y lo devolvemos.
    return (!ab_izq) ? ab_der : ab_izq;
}

void listar_post_order(ab_t* ab, lista_t* lista){
    if(!ab) return NULL;
    //llamo lado izquierdo
    listar_post_order(ab->izq);
    //lamo lado derecho
    listar_post_order(ab->der);
    //inserto en lista el actual
    lista_insertar_ultimo(lista, ab->clave);
    return;
}

lista_t* ab_debajo(ab_t* ab, const char* clave){
    lista_t* lista = lista_crear();
    if(!lista)  return NULL;
    ab_t* clave_buscada = buscar_clave(ab, clave);
    listar_post_order(ab, lista);
    return lista;
}
/*
    El orden termina siendo O(n), con n siendo todos la cantidad de nodos en el arbol, ya que no hacemos comparaciones para decidir si vamos por un lado 
    o por el otro, el logaritmo no aparece..Y como estamos buscando una clave en particuar como peor caso podemos tener que este al final y que tengamos que 
    recorrer todos los nodos.
    Luego el recorrido para apilar tambien resulta O(n) ya que visitamos todos los nodos una sola vez y agregamos a la lista, quee s una operacion O(1)
*/


// EJERCICIO 4 CERRADO
//Uso un hash cerrado igual al implementado en clase 
hash_par_t* crear_par_hash(const char* clave, void* dato){
    hash_par_t* hash_par = malloc(sizeof(hash_par_t));
    if(!hash_par) return NULL;
    hash_par->clave = strdup(clave);
    hash_par->dato = dato;
    return hash_par;
}

void destruir_par_hash(void* dato){
    free(dato->clave);
    free(dato);
    return;
}

lista_t* obtener_lista_claves(const hash_t *hash){
    //Me toco hash cerrado
    void (*funcion_destruir) (void*);
    funcion_destruir = destruir_par_hash;
    lista_t* lista = lista_crear();
    if(!lista) return NULL;
    size_t cont = 0;
    while(cont < hash->capacidad){
        if(hash->campos[cont].estado == ocupado){
            hash_par_t* hash_par = crear_par_hash(hash->campos[cont].clave, hash->campos[cont].valor);
            if(!hash_par){
                lista_destruir(lista, funcion_destruir);
                return NULL;
            }
            lista_insertar_ultimo(lista, hash_par);
        }
        cont++;
    }
    return lista;
}
/*
    La comlejidad del algoritmo implementado seria O(n), siendo n la capacidad del hash. Como queremos obtener todas las claves y valores si o si vamos a 
    recorrer todo el hash, preguntando si el campo esta ocupado, cuando esta ocupado copiamos sus valores al struct y lo agregamos a la lista(lo cual es O(1)),
    cuando esta vacio o borrado seguimos. Tenemos que recorrer toda la capacidad del hash para chequear todos los posibles campos ocupados

*/