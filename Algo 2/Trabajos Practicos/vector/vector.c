#include "vector.h"


// Funciones del alumno.

// ...
void vector_destruir(vector_t* vector){
	//Primero libero el espacio alocado para los datos
	free(vector->datos);	
	//Y despues libero el espacio alocado para el TDA
	free(vector);
}


size_t vector_largo(vector_t* vector){
	//Simplemente devuelvo el largo del vector
	return vector->tam;
}



bool vector_obtener(vector_t* vector, size_t pos, int* valor){
	//Si el tam es 0 no tiene sentido obtener algo de un vector vacio. 
	//Debido a que pos es un size_t, nunca sera negativo, pero hay que chequear si el indice esta en el rango valido del vector.
	if(pos >= vector->tam){
		return false;
	}
	
	*valor = vector->datos[pos];
	return true;

}



bool vector_guardar(vector_t* vector, size_t pos, int valor){
	//Si el tam es 0 no tiene sentido guardar algo en un vector vacio. 
	//Debido a que pos es un size_t, nunca sera negativo, pero hay que chequear si el indice esta en el rango valido del vector.
	if(pos >= vector->tam){
		return false;
	}
	//Almaceno en el vector con indice en la posicion pedida, el valor.
	vector->datos[pos] = valor;
	return true;
}

// Funciones implementadas por la catedra.

vector_t* vector_crear(size_t tam) {
    vector_t* vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    vector->datos = malloc(tam * sizeof(int));

    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));

    // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
