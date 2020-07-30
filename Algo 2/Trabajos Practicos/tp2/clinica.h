#ifndef CLINICA_H
#define CLINICA_H

#include <stddef.h>
#include <stdbool.h>
#include "structs.h"
#include "csv.h"
#include "mensajes.h"

struct especialidad;
typedef struct clinica clinica_t;

clinica_t* crear_clinica(char** argv);

void destruir_clinica(clinica_t* clinica);

void pedir_turno_paciente(clinica_t* clinica, char* nombre, char* nombre_especialidad , char* prioridad);

#endif
