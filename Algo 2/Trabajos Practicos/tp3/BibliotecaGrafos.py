from grafo import Grafo
from cola import Cola

# Recibe un grafo y una lista de vertices, si existe una relacion de precedencia entre los vertices
# devuelve una lista ordenada de estos segun corresponda, o None en caso de que se encuentren ciclos o no existan dichos vertices.
def orden_topologico_subgrafo(grafo,lista):
    subgrafo = Grafo(True)
    for vertice in lista:
        if not grafo.existe_vertice(vertice): return None
        subgrafo.agregar_vertice(vertice)
    for vertice in lista:
        for adyacente in grafo.obtener_adyacentes(vertice):
            subgrafo.agregar_arista(vertice,adyacente)
    return orden_topologico(subgrafo)
    # Esta deberiamos trabajarla afuera de la biblioteca, en NetStats

# Recibe un grafo,  si existe una relacion de precedencia entre los vertices
# devuleve una lista ordenada de de estos, o None en caso de que se encuentren ciclos
# Este algoritmo utiliza un recorrido similar a BFS
def orden_topologico(grafo):
    grados = {}
    resultados = []
    for v in grafo: grados[v] = 0
    for v in grafo:
        for w in grafo.obtener_adyacentes(v):
            grados[w] += 1
    cola = Cola()
    for v in grafo:
        if grados[v] == 0: cola.encolar(v)
    while not cola.esta_vacia():
        v = cola.desencolar()
        resultados.append(v)
        for w in grafo.obtener_adyecentes(v):
            grados[w] -= 1
            if grados[w] == 0: cola.encolar(w)
    if len(resultados) == len(grafo): return resultados
    return None

def calcular_diametro(grafo):
    diametro= 0
    for v in grafo:
        distancias = caminos_minimos(grafo, v)
        for w in distancias:
            if distancias[w] > diametro:
                diametro = distancias[w]
    return diametro

def caminos_minimos(grafo, origen):
    cola = Cola()
    visitados = set()
    distancia = {}
    distancia[origen] = 0
    visitados.add(origen)
    cola.encolar(origen)

    while not cola.esta_vacia():
        v = cola.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                distancia[w] = distancia[v] + 1
                cola.encolar(w)
                visitados.add(w)
    return distancia

def distancia_exacta(grafo,origen,n):
    #if n > len(grafo): return 0
    cola = Cola()
    cola.encolar(origen)
    distancia = {}
    distancia[origen] = 0
    lista = []
    while not cola.esta_vacia():
        v = cola.desencolar()
        for w in grafo.obtener_adyacentes(v):
            if w not in distancia:
                distancia[w] = distancia[v] + 1
                cola.encolar(w)
                if distancia[w] == n: lista.append(w)
                if distancia[w] > n: return len(lista)
    return len(lista)
        