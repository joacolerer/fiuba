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
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/
bool validar_prioridad(char* prioridad){
	return (strcmp(prioridad,"URGENTE") == 0) || (strcmp(prioridad,"REGULAR") == 0);
}


/* ******************************************************************
 *                           PRIMITIVAS
 * *****************************************************************/

clinica_t* crear_clinica(char** argv){
	clinica_t* clinica = malloc(sizeof(clinica_t));
	if (!clinica) return NULL;
	hash_t* hash_especialidades = hash_crear(w_destruir_especialidad);
	if(!hash_especialidades){
		free(clinica);
		return NULL;
	}
	clinica->doctores = csv_crear_estructura_doctor(argv[1],hash_especialidades);
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


void pedir_turno_paciente(clinica_t* clinica, char* nombre, char* nombre_especialidad , char* prioridad){
	if (!hash_pertenece(clinica->pacientes,nombre)){
		printf(ENOENT_PACIENTE,nombre);
		return;
	}
	especialidad_t* especialidad = hash_obtener(clinica->especialidades,nombre_especialidad);
	if (!especialidad){
		printf(ENOENT_ESPECIALIDAD,nombre_especialidad);
		return;
	}

	if (!validar_prioridad(prioridad)){
		printf(ENOENT_URGENCIA,prioridad);
		return;
	}

	if (strcmp(prioridad,"URGENCIA") == 0){
		encolar_paciente_urgencias(especialidad,nombre);
	}

	else{
		int* anio = hash_obtener(clinica->pacientes,nombre);
		encolar_paciente_regulares(especialidad,nombre,anio);
	}
	printf(PACIENTE_ENCOLADO,nombre);
	long cant_pacientes = cantidad_pacientes_especialidad(especialidad);
	printf(CANT_PACIENTES_ENCOLADOS,cant_pacientes,nombre_especialidad);
}

void destruir_clinica(clinica_t* clinica){
	abb_destruir(clinica->doctores);
	hash_destruir(clinica->pacientes);
	hash_destruir(clinica->especialidades);
	free(clinica);
}
