Nombfe: Joaquin Matias Lerer
Padron: 105.493

Consideraciones para el uso del programa:

El programa viene con un grafo de prueba, es decir si lo corren va a mostrar los resultados de esa prueba en particular.

El metodo de ingreso del grafo es mediante una matriz de adyacencia.
Esta matriz se debera ingresar en la variable "grafo", la cual se encuentra en la section .data del codigo (la primer variable).

Se debe ingresar filas definidas con quadruple word (dq) con la misma cantidad de columnas que de filas.
El programa esta armado para calcular con grafos de entre 5 y 15 elementos (representa un grafo de entre 5 y 15 vertices).

Por ejemplo: una matriz de un grafo con 5 vertices (5x5) tendria el siguiente formato:

grafo   dq 0,0,0,0,0
        dq 0,0,0,0,0
        dq 0,0,0,0,0
        dq 0,0,0,0,0
        dq 0,0,0,0,0

Y una matriz de un grafo de 10 vertices:

grafo   dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0
        dq 0,0,0,0,0,0,0,0,0,0

Instrucciones para la ejecucion del programa:

1) Abrir una terminal y navegar hasta el directorio donde se encuentren los archivos. (O abrir la terminal directamente en la carpeta donde se encuentran los archivos)

2) Ingrese el comando "make", el cual ensambla y compila el trabajo.

3) Ejecute el archivo ./TpGrafo.out

