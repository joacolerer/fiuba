#ifndef CLINICA_H
#define CLINICA_H

#include <stddef.h>
#include "structs.h"
#include "csv.h"

struct especialidad;
typedef struct clinica clinica_t;

clinica_t* crear_clinica(char** argv);

void destruir_clinica(clinica_t* clinica);

#endif
