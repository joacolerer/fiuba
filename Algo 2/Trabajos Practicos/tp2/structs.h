#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
struct doctor;
struct paciente;
struct clinica;
struct especialidad;

typedef struct doctor doctor_t;
typedef struct paciente paciente_t;
typedef struct clinica clinica_t;
typedef struct especialidad especialidad_t;

doctor_t *crear_doctor(char** campos,void* extra);

paciente_t* crear_paciente(char** campos,void* extra);

clinica_t* crear_clinica(char** argv);

void destruir_clinica(clinica_t* clinica);

void destruir_paciente(paciente_t* paciente);

void destruir_doctor(doctor_t* doctor);

void destruir_especialidad(especialidad_t* especialidad);

#endif