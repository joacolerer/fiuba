#include "structs.h"
#include "csv.h"
#include "abb.h"
#include "hash.h"
#include "heap.h"
#include "cola.h"
#include "lista.h"


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

 struct clinica{
	abb_t* doctores;
	abb_t* pacientes;
	hash_t* especialidades;
};

 struct especialidad{
	char* nombre;
	heap_t* regulares; // Puede ser un abb
	cola_t* urgencias;
	cola_t* doctores; // Puede ser una pila
};

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
	//clinica->especialidades = hash_crear()
	return clinica;
}

especialidad_t* crear_especialidad(char* nombre){
	especialidad_t* especialidad = malloc(sizeof(especialidad_t));
	if(!especialidad) return NULL;
	especialidad->nombre = nombre;
	especialidad->regulares = heap_crear(cmp_pacientes);
	if(!especialidad->regulares) return NULL;
	especialidad->urgencias = cola_crear();
	if(!especialidad->urgencias) return NULL;
	especialidad->doctores = cola_crear();
	if(!especialidad->doctores) return NULL;
	return especialidad;
}

void destruir_clinica(clinica_t* clinica){
	abb_destruir(clinica->doctores);
	abb_destruir(clinica->pacientes);
	hash_destruir(clinica->especialidades);
	free(clinica);
}

void destruir_paciente(paciente_t* paciente){
	//free(paciente->nombre)?
	free(paciente);
}
void destruir_doctor(doctor_t* doctor){
	//free(doctor->nombre)
	free(doctor);
}

void destruir_especialidad(especialidad_t* especialidad){
	heap_destruir(especialidad->regulares, destruir_paciente);
	cola_destruir(especialidad->doctores,destruir_doctor);
	cola_destruir(especialidad->urgencias,destruir_paciente);
	free(especialidad);
}

//NO SE AL 100%, CREO QUE ES ASI
int cmp_pacientes(const void *a, const void *b){
	if(((paciente_t*)a)->anio == ((paciente_t*)b)->anio) return 0;
    if(((paciente_t*)a)->anio < ((paciente_t*)b)->anio) return 1;
    return -1;
}