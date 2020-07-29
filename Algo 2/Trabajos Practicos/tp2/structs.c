#include <stdlib.h>
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
	heap_t* regulares; // Puede ser un abb
	cola_t* urgencias;
	cola_t* doctores; // Puede ser una pila
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

doctor_t* crear_doctor(char** campos){
	doctor_t* doctor = malloc(sizeof(doctor_t));
	if (!doctor) return NULL;
	doctor->cant_atendidos = 0;
	doctor->nombre = campos[0];
	doctor->especialidad = campos[1];
	return doctor;
}

paciente_t* crear_paciente(char** campos,void* extra){
	paciente_t* paciente = malloc(sizeof(paciente_t));
	if (!paciente) return NULL;
	paciente->nombre = campos[0];
	paciente->anio = atoi(campos[1]); // Validar anios !
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
	//free(doctor->nombre)
	free(doctor);
}

//void (*hash_destruir_dato_t)(void *);
void w_destruir_especialidad(void* especialidad){
	destruir_especialidad((especialidad_t*) especialidad);
}

void destruir_especialidad(especialidad_t* especialidad){
	heap_destruir(especialidad->regulares,free);
	cola_destruir(especialidad->doctores,free);
	cola_destruir(especialidad->urgencias,free);
	free(especialidad);
}

/* ******************************************************************
 *                      FUNCIONES PARA ENCOLAR/DESENCOLAR
 * *****************************************************************/

void encolar_doctor_en_especialidad(especialidad_t* especialidad, doctor_t* doctor){
	cola_encolar(especialidad->doctores,doctor);
}
