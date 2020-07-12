#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "strutil.h"
#include "pila.h"


bool validar_num(char *num){
    size_t i = 0;
    if(num[0] == '-') i = 1;
    for (; i < strlen(num); i++){
        if(isdigit(num[i]) == 0)    return  false;
    }
    return  true;
}


bool mi_pila_apilar(pila_t* pila, long valor){
    long* val = malloc(sizeof(long));
    if (val == NULL) return false;
    *val = valor;
    return  pila_apilar(pila, val);
}

long mi_pila_desapilar(pila_t* pila){
    long val_tmp = *(long*)pila_ver_tope(pila);
    free(pila_desapilar(pila));
    return  val_tmp;
}



bool evaluar_expresion(pila_t* pila, char *op, size_t operandos, long* resultado){
    long valor1 = 0;
    long valor2 = 0;
    long valor3 = 0;
    if(operandos == 1){
        if(pila_esta_vacia(pila))   return  false;
        valor1 = mi_pila_desapilar(pila);
    } else{
        
        if (operandos ==2)
        {
            if(pila_esta_vacia(pila))   return  false;
            valor2 = mi_pila_desapilar(pila);
            if(pila_esta_vacia(pila))   return  false;            
            valor1 = mi_pila_desapilar(pila);
        }else{
            if(pila_esta_vacia(pila))   return  false;
            valor3 = mi_pila_desapilar(pila);
            if(pila_esta_vacia(pila))   return  false;
            valor2 = mi_pila_desapilar(pila);
            if(pila_esta_vacia(pila))   return  false;
            valor1 = mi_pila_desapilar(pila);
        }
    }
    double val_tmp;
    switch (op[0]){
        case '+': 
            *resultado =  valor1 + valor2;
            break;
        case '*':
            *resultado = valor1 * valor2;
            break;
        case '-':
            *resultado = valor1 - valor2;
            break;
        case '/':
            if(valor2 == 0) return  false;
            *resultado = valor1 / valor2;
            break;
        case 's':
            if(valor1 < 0)  return  false;
            val_tmp = sqrt((double) valor1);
            *resultado = (long) val_tmp;
            break;
        case '^':
            if(valor2 < 0)  return  false;
            val_tmp = pow((double) valor1,(double) valor2);
            *resultado = (long) val_tmp;
            break;
        case 'l':
            if(valor2 < 2)  return  false;
            val_tmp = log((double) valor1) / log((double) valor2);
            *resultado = (long) val_tmp;
            break;
        case '?':
            *resultado =  (valor1 ? valor2 : valor3);
            break;
    }
    return  true;
}

size_t cant_operandos(char* op){
    switch (op[0]){
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case 'l':
        return  2;
    case 's':
        return  1;
    case '?':
        return  3;
    }
    return  -1;
}

void liberar_pila_entera(pila_t *pila){
    while(!pila_esta_vacia(pila)){
        mi_pila_desapilar(pila);
    }
    pila_destruir(pila);
}


bool procesar_entrada(char **arr){
    pila_t *pila = pila_crear();
    for (size_t i = 0; arr[i] != NULL; i++){
        //FALTA VALIDAR CASOS PARTICUALRES COMO 2AA
        //Pregunto si estoy leyendo un espacio                                                                                                                                                                                          
        if(strcmp(arr[i], "") != 0){

            long es_num = strtol(arr[i], NULL, 10);
            
            if(es_num != 0 || strcmp(arr[i], "0") == 0){
                //Tengo un numero
                bool num_valido = validar_num(arr[i]);
                if (!num_valido){
                    liberar_pila_entera(pila);
                    return  false;
                }
                mi_pila_apilar(pila, es_num);
            } else {
                //Es un operador aca
                size_t operandos_necesarios = cant_operandos(arr[i]);
                if(operandos_necesarios == -1){
                    //Si es -1 significa que el operador no es valido
                    liberar_pila_entera(pila);
                    return  false;
                }
                long result_temp;
                bool expresion_valida = evaluar_expresion(pila, arr[i], operandos_necesarios,&result_temp);
                if(!expresion_valida){
                    //Si entra aca es porque fallo al evaluar la expresion, esto puede ser por falta de operandos o por errores propios de cada operacion
                    liberar_pila_entera(pila);
                    return  false;
                }
                mi_pila_apilar(pila, result_temp);
            }
        }
    }
    long resultado_final;
    //Si la pila no tiene ningun valor por alguna razon, hay error
    if(!pila_esta_vacia(pila)){
        resultado_final = mi_pila_desapilar(pila);
        //Si despues de desapilar el resultado, queda algun valor mas en la pila tenemos error
        if(!pila_esta_vacia(pila)){
            liberar_pila_entera(pila);
            return  false;
        }
    }else{
        return  false;
    }
    
    fprintf(stdout, "%ld\n", resultado_final);

    pila_destruir(pila);
    return  true;
}

void leer_entrada(){
    while(!feof(stdin)){
        char ingresado[50];
        if(fgets(ingresado, 50, stdin)!=NULL){
            char **arr = split(ingresado, ' ');
            if(!procesar_entrada(arr)){
                fprintf(stdout,"%s\n", "ERROR");
            }
            free_strv(arr);
        }
    }
}

int main(){
    leer_entrada();
    return 0;
}