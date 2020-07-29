#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
#include "abb.h"
#include "hash.h"
#include "heap.h"
#include "cola.h"

struct doctor;
struct paciente;
struct especialidad;

typedef struct doctor doctor_t;
typedef struct paciente paciente_t;
typedef struct especialidad especialidad_t;

doctor_t *crear_doctor(char** campos);

paciente_t* crear_paciente(char** campos,void* extra);

especialidad_t* crear_especialidad(char* nombre);

void destruir_doctor(doctor_t* doctor);

void destruir_paciente(paciente_t* paciente);

void destruir_especialidad(especialidad_t* especialidad);

void encolar_doctor_en_especialidad(especialidad_t* especialidad, doctor_t* doctor);

//wrappers
void w_destruir_doctor(void* doctor);

void w_destruir_paciente(void* paciente);

void w_destruir_especialidad(void* especialidad);

#endif
