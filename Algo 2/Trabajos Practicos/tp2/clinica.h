#ifndef CLINICA_H
#define CLINICA_H
#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"
#include "csv.h"
#include "mensajes.h"

struct especialidad;
typedef struct clinica clinica_t;

clinica_t* crear_clinica(char** argv);

void destruir_clinica(clinica_t* clinica);

void pedir_turno_paciente(clinica_t* clinica, char* nombre, char* nombre_especialidad , char* prioridad);
void atender_siguiente_paciente(clinica_t* clinica, char* nombre_doc);

#endif
