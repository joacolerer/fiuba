#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap (int *x, int *y) {
	int aux = *x;
	*x = *y;
	*y=aux;
}


int maximo(int vector[], int n) {
	if(n == 0) return -1;//Si no hay elementos no vale la pena continuar
	int posMax = 0;
	int masGrande = vector[0];
	
	for(int i = 1; i<n;i++){
		if(vector[i]>masGrande){
			masGrande = vector[i];
			posMax = i;
		}
	}
    return posMax;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
	int i = 0;
	int j = 0;
	
	while(i<n1&&j<n2){
		if(vector1[i] < vector2[j]){
			return -1;
		} 
		
		if(vector1[i] > vector2[j]){
			return 1;
		}
		
		i++;
		j++;
	}
	if(i==n1 && j!=n2){
		return -1;
	}
		
	if(j==n2 && i!=n1){
		return 1;
	}
    return 0;
}	


void seleccion(int vector[], int n) {
	int posMax = maximo(vector, n);
	for(int i = 1; i<n;i++){
		swap(&vector[posMax], &vector[n-i]);
		posMax = maximo(vector, n-i);
	}
}
