#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "strutil.h"
#include "mensajes.h"
#include "structs.h"
//#include "funciones_tp2.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"


/* ******************************************************************
 *                       FUNCIONES PRINCIPALES
 * *****************************************************************/


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
		return 1;
	}
	clinica_t* clinica = crear_clinica(argv);
	if(!clinica){
		return 1;
	}

	return 0;
}
