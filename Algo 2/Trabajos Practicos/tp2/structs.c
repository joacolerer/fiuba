#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"


/* ******************************************************************
 *                    ESTRUCTURAS PRINCIPALES
 * *****************************************************************/

 struct doctor{
	char* nombre;
	char* especialidad;
	int cant_atendidos;
};

struct paciente{
	char* nombre;
	int anio;
};

 struct especialidad{
	char* nombre;
	heap_t* regulares;
	cola_t* urgencias;
	cola_t* doctores;
	int cant_pacientes;
};

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

//NO SE AL 100%, CREO QUE ES ASI
int cmp_pacientes(const void *a, const void *b){
	if(((paciente_t*)a)->anio == ((paciente_t*)b)->anio) return 0;
    if(((paciente_t*)a)->anio < ((paciente_t*)b)->anio) return 1;
    return -1;
}



/* ******************************************************************
 *                      FUNCIONES DE CREACION
 * *****************************************************************/

// Tal vez deberiamos hacer copia de los parametros en estas funciones

doctor_t* crear_doctor(const char* nombre, const char* especialidad){
	doctor_t* doctor = malloc(sizeof(doctor_t));
	if (!doctor) return NULL;
	doctor->cant_atendidos = 0;
	char* copia_nombre = strdup(nombre);
	doctor->nombre = copia_nombre;
	char* copia_especialidad = strdup(especialidad);
	doctor->especialidad = copia_especialidad;
	return doctor;
}

paciente_t* crear_paciente(char* nombre, int anio){
	paciente_t* paciente = malloc(sizeof(paciente_t));
	if (!paciente) return NULL;
	paciente->nombre = nombre;
	paciente->anio = anio;
	return paciente;
}

especialidad_t* crear_especialidad(char* nombre){
	especialidad_t* especialidad = malloc(sizeof(especialidad_t));
	if(!especialidad) return NULL;
	especialidad->nombre = nombre;
	especialidad->regulares = heap_crear(cmp_pacientes);
	if(!especialidad->regulares){
		free(especialidad);
		return NULL;
	}
	especialidad->urgencias = cola_crear();
	if(!especialidad->urgencias){
		heap_destruir(especialidad->regulares,free); // Pasar destruir paciente
		free(especialidad);
		return NULL;
	}
	especialidad->doctores = cola_crear();
	if(!especialidad->doctores){
		heap_destruir(especialidad->regulares,free);
		cola_destruir(especialidad->urgencias,free);
		free(especialidad);
		return NULL;
	}
	especialidad->cant_pacientes = 0;
	return especialidad;
}

/* ******************************************************************
 *                      FUNCIONES DE DESTRUCCIÒN
 * *****************************************************************/

void destruir_paciente(paciente_t* paciente){
	//free(paciente->nombre)?
	free(paciente);
}
void destruir_doctor(doctor_t* doctor){
	free(doctor->nombre);
	free(doctor->especialidad);
	free(doctor);
}

//void (*hash_destruir_dato_t)(void *);
void w_destruir_especialidad(void* especialidad){
	destruir_especialidad((especialidad_t*) especialidad);
}

void w_destruir_doctor(void* doctor){
	destruir_doctor((doctor_t*) doctor);
}

void destruir_especialidad(especialidad_t* especialidad){
	heap_destruir(especialidad->regulares,free);
	cola_destruir(especialidad->doctores,NULL);
	cola_destruir(especialidad->urgencias,free);
	free(especialidad);
}

/* ******************************************************************
 *                      FUNCIONES PARA ENCOLAR/DESENCOLAR
 * *****************************************************************/

void encolar_doctor_en_especialidad(especialidad_t* especialidad, doctor_t* doctor){
	cola_encolar(especialidad->doctores,doctor);
}

void encolar_paciente_urgencias(especialidad_t* especialidad,char* nombre){
	cola_encolar(especialidad->urgencias,nombre);
	especialidad->cant_pacientes++;
}

bool encolar_paciente_regulares(especialidad_t* especialidad,char* nombre,int* anio){
	paciente_t* paciente = crear_paciente(nombre,*anio);
	if(!paciente) return NULL;
	heap_encolar(especialidad->regulares,paciente);
	especialidad->cant_pacientes++;
	return true;
}

long cantidad_pacientes_especialidad(especialidad_t* especialidad){
	return especialidad->cant_pacientes;
}

/*
void mostrar_doctor_cola(especialidad_t* especialidad){
	char** doctor1 = cola_ver_primero(especialidad->doctores);
	printf("El nombre del primer doctor es: %s \n", *doctor1);
	char** doctor11 = cola_desencolar(especialidad->doctores);
	printf("Coincide: %d \n", *doctor1 == *doctor11);
	char** doctor2 = cola_ver_primero(especialidad->doctores);
	printf("El nombre del ultimo doctor es: %s \n", *doctor2);

}
*/
