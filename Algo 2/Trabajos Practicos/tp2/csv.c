#define _POSIX_C_SOURCE 200809L //getline
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"
#include "abb.h"
#include "hash.h"
#include "structs.h"
#include "mensajes.h"
#define SEPARADOR ','

static void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

abb_t* csv_crear_estructura_doctor(const char* ruta_csv, void* (*creador) (char**, void*), void* extra){
	FILE* archivo = fopen(ruta_csv, "r");
	if (!archivo){
		printf(ENOENT_ARCHIVO, ruta_csv);
		return NULL;
	}

	abb_t* abb = abb_crear(strcmp,free);
	if (!abb) {
		fclose(archivo);
		return NULL;
	}
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, archivo) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, SEPARADOR);
		//Si no existe la especialidad en el hash
		doctor_t* doctor = creador(campos,extra);
		if(!hash_pertenece((hash_t*)extra,campos[1])){
			//La creo
			especialidad_t* especialidad = crear_especialidad(campos[1]);
			if(!especialidad){
				fclose(archivo);
				free_strv(campos);
				abb_destruir(abb);
				return NULL;
			}
			//Encolo el doctor en esa especialidad
			encolar_doctor_en_especialidad(especialidad,doctor);
			//Guardo la especialidad
			hash_guardar((hash_t*)extra,campos[1],especialidad);
		} else {
			//Si existe, obtengo la especialidad en el hash
			especialidad_t* especialidad = hash_obtener((hash_t*)extra,campos[1]);
			//Y encolo al doctor en esa especialidad
			encolar_doctor_en_especialidad(especialidad,doctor);
		}
		abb_guardar(abb, campos[0],doctor);
		free_strv(campos);
	}
	free(linea);
	fclose(archivo);
	return abb;
}


hash_t* csv_crear_estructura_pacientes(const char* ruta_csv, void* (*creador) (char**, void*), void* extra){
	FILE* archivo = fopen(ruta_csv, "r");
	if (!archivo) {
		//Mostramos error abrir archivo
		printf(ENOENT_ARCHIVO, ruta_csv);
		return NULL;
	}

	hash_t* hash = hash_crear(destruir_especialidad);
	if (!hash) {
		fclose(archivo);
		return NULL;
	}

	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, archivo) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, SEPARADOR);
		int anio = atoi(campos[1]);
		if(anio == 0 && strcmp(campos[1], "0") != 0){
			printf(ENOENT_ANIO, campos[1]);
			fclose(archivo);
			hash_destruir(hash);
			free_strv(campos);
			return NULL;
		}
		hash_guardar(hash,campos[0],creador(campos,extra));
		//PASAR ANIOS A INT Y HACER UNA COPIA ASI EL PUNTERO NO SE BORRA
		free_strv(campos);
	}
	free(linea);
	fclose(archivo);
	return hash;
}


