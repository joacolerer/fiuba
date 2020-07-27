#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#include "csv.h"
#include "abb.h"
#include "hash.h"
#include "heap.h"
#include "cola.h"
#include "lista.h"
#include "strutil.h"
#include "mensajes.h"
//#include "funciones_tp2.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"

/* ******************************************************************
 *                    ESTRUCTURAS PRINCIPALES
 * *****************************************************************/

typedef struct doctor{
	char* nombre;
	char* especialidad;
	int cant_atendidos;
}doctor_t;

typedef struct paciente{
	char* nombre;
	int anio;
}paciente_t;

typedef struct clinica{
	abb_t* doctores;
	abb_t* pacientes;
	hash_t* especialidades;
}clinica_t;

typedef struct especialidad{
	char* nombre;
	heap_t* regulares; // Puede ser un abb
	cola_t* urgencias;
	cola_t* ocupados; // Puede ser una pila
	cola_t* libres; // Puede ser una pila
}especialidad_t;

/* ******************************************************************
 *                      FUNCIONES DE CREACION
 * *****************************************************************/

// Tal vez deberiamos hacer copia de los parametros en estas funciones

doctor_t* crear_doctor(char** campos,void* extra){
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
	paciente->anio = campos[1]; // Validar anios !
	return paciente;
}

clinica_t* crear_clinica(char** argv){
	clinica_t* clinica = malloc(sizeof(clinica_t));
	if (!clinica) return NULL;
	clinica->doctores = csv_crear_estructura(argv[1],(void*)crear_doctor,NULL);
	clinica->pacientes = csv_crear_estructura(argv[2],(void*)crear_paciente,NULL);
	// clinica->especialidades
	return clinica;
}

void destruir_clinica(clinica_t* clinica){
	abb_destruir(clinica->doctores);
	abb_destruir(clinica->pacientes);
	hash_destruir(clinica->especialidades);
	free(clinica);
}

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

// bool validar_año();



/* ******************************************************************
 *                       FUNCIONES PRINCIPALES
 * *****************************************************************/

void cargar_informacion(){

}

void procesar_comando(const char* comando,char** parametros) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {

	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {

	} else if (strcmp(comando, COMANDO_INFORME) == 0) {

	} else {

	}
}

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

void procesar_entrada() {
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, stdin) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(campos[0], parametros);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}


/* ******************************************************************
 *                       PROGRAMA PRINCIPAL
 * *****************************************************************/

// Programa principal: se interpreta que el primer nombre recibido
// corresponde al archivo de doctores y el segundo al de pacientes
int main(int argc, char** argv) {

	if (argc != 3){ // Recibe el nombre del promgrama y el nombre de 2 archivos
		printf(ENOENT_CANT_PARAMS);
		//return o exit
	}


	return 0;
}
