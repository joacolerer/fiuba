#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
#include <string.h>
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

doctor_t *crear_doctor(const char* nombre, const char* especialidad);

paciente_t* crear_paciente(char* nombre,int anio);

especialidad_t* crear_especialidad(char* nombre);

void destruir_doctor(doctor_t* doctor);

void destruir_paciente(paciente_t* paciente);

void destruir_especialidad(especialidad_t* especialidad);

void encolar_doctor_en_especialidad(especialidad_t* especialidad, doctor_t* doctor);

void encolar_paciente_urgencias(especialidad_t* especialidad, char* nombre);

bool encolar_paciente_regulares(especialidad_t* especialidad, char* nombre,int* anio);

long cantidad_pacientes_especialidad(especialidad_t* especialidad);

char* conseguir_especialidad_doctor(doctor_t* doctor);

bool hay_pacientes_urgentes(especialidad_t* especialidad);

char* desencolar_urgente(especialidad_t* especialidad);

paciente_t* desencolar_regular(especialidad_t* especialidad);

char* nombre_especialidad(especialidad_t* especialidad);

bool hay_pacientes_regulares(especialidad_t* especialidad); 

char* nombre_paciente(paciente_t* paciente);

void atiende_doctor(doctor_t* doctor);

//wrappers
void w_destruir_doctor(void* doctor);

void w_destruir_paciente(void* paciente);

void w_destruir_especialidad(void* especialidad);

//imprimir debug
void mostrar_doctor_cola(especialidad_t* especialidad);

#endif
