from grafo import Grafo
import csv 

def cargar_grafo_archivo(archivo):
    grafo = Grafo(dirigido = True)
    lineas = []
    
    with open(archivo) as file:
        file_tsv = csv.reader(file,delimiter="\t")
        for linea in file_tsv:
            if len(linea) != 0:    
                grafo.agregar_vertice(linea[0])
                lineas.append(linea)
        
    for linea in lineas:
        for i in range(1,len(linea)):
            if len(linea) > 1: grafo.agregar_arista(linea[0],linea[i])
    
    return grafo 

def wenardo(grafo):
    lista= grafo.obtener_vertices()
    print(len(lista))

def main(archivo):
    grafo = cargar_grafo_archivo(archivo)
    wenardo(grafo)

main("wiki-reducido-5000.tsv")