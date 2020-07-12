#include "hash.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool son_iguales(hash_t* hash1, hash_t* hash2){
    if(hash_cantidad(hash1) != hash_cantidad(hash2)) return false;
    hash_iter_t* iter_hash1 = hash_iter_crear(hash1);
    hash_iter_t* iter_hash2 = hash_iter_crear(hash2);
    bool iguales = true;
    while(!hash_iter_al_final(iter_hash1)){
        if(!hash_pertenece(hash2, hash_iter_ver_actual(iter_hash1))){
            iguales = false;
            break;
        } 
        if(*(int*) hash_obtener(hash1, hash_iter_ver_actual(iter_hash1)) != *(int*) hash_obtener(hash2,hash_iter_ver_actual(iter_hash1))){
           iguales = false;
           break;
        } 
        if(!hash_pertenece(hash1, hash_iter_ver_actual(iter_hash2))){
            iguales = false;
            break;
        } 
        if(*(int*) hash_obtener(hash2, hash_iter_ver_actual(iter_hash2)) != *(int*) hash_obtener(hash1,hash_iter_ver_actual(iter_hash2))){
            iguales = false;
            break;
        } 
        hash_iter_avanzar(iter_hash1);
        hash_iter_avanzar(iter_hash2);
    }
    hash_iter_destruir(iter_hash1);
    hash_iter_destruir(iter_hash2);
    return iguales;
}

int main(){
    printf("MAIN\n");
    hash_t* hash1 = hash_crear(NULL);
    hash_t* hash2 = hash_crear(NULL);
    int valor1 = 1;
    hash_guardar(hash1, "vaca", &valor1);
    printf("%d\n", son_iguales(hash1, hash2));
    hash_destruir(hash1);
    hash_destruir(hash2);
    return 1;
}