#include "clinica.h"


/* ******************************************************************
 *                    ESTRUCTURAS PRINCIPALES
 * *****************************************************************/

 struct clinica{
	abb_t* doctores;
	hash_t* pacientes;
	hash_t* especialidades;
};


/* ******************************************************************
 *                      FUNCIONES DE CREACION
 * *****************************************************************/

// Tal vez deberiamos hacer copia de los parametros en estas funciones

clinica_t* crear_clinica(char** argv){
	clinica_t* clinica = malloc(sizeof(clinica_t));
	if (!clinica) return NULL;
	hash_t* hash_especialidades = hash_crear(w_destruir_especialidad);
	if(!hash_especialidades){
		free(clinica);
		return NULL;
	}
	clinica->doctores = csv_crear_estructura_doctor(argv[1],(void*)crear_doctor,hash_especialidades);
	if(!clinica->doctores){
		hash_destruir(hash_especialidades);
		free(clinica);
		return NULL;
	}
	clinica->pacientes = csv_crear_estructura_pacientes(argv[2]);
	if(!clinica->pacientes){
		hash_destruir(hash_especialidades);
		abb_destruir(clinica->doctores);
		free(clinica);
		return NULL;
	}
	clinica->especialidades = hash_especialidades;
	return clinica;
}


/* ******************************************************************
 *                      FUNCIONES DE DESTRUCCIÒN
 * *****************************************************************/

void destruir_clinica(clinica_t* clinica){
	abb_destruir(clinica->doctores);
	hash_destruir(clinica->pacientes);
	hash_destruir(clinica->especialidades);
	free(clinica);
}


