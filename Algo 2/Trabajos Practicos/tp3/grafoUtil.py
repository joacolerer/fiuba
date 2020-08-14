from grafo import Grafo
from cola import Cola
from pila import Pila

def camino(grafo,origen,destino):
    if(grafo.existe_vertice(origen) and grafo.existe_vertice(destino)):
        destino_visitado = False
        orden = {}
        padre = {}
        visitados = set()
        q = Cola()
        orden[origen] = 0
        padre[origen] = None
        visitados.add(origen)
        q.encolar(origen)

        while q:
            v = q.desencolar()
            for w in grafo.obtener_adyacentes(v):
                if w not in visitados:
                    padre[w] = v
                    orden[w] = orden[v] + 1
                    visitados.add(w)
                    if destino in visitados:
                        destino_visitado = True
                        break
                    q.encolar(w)
            if destino_visitado:
                break
        
        if destino_visitado:
            resultado = []
            resultado.append(destino)
            w = destino
            v = padre[w]
            while v is not None:
                resultado.append(v)
                w = v
                v = padre[w]
            resultado.reverse()

            for v in resultado:
                print(v)
            print("Costo {}".format(orden[destino]))
        else:
            print("No se encontro recorrido")


def conectados(grafo,pagina):
    if grafo.existe_vertice(pagina):
        visitados = set()
        apilados = set()
        orden = dict()
        mb = dict()
        pila = Pila()
        todas_cfc = []
        orden[pagina] = 0
        
        tarjan(pagina,visitados,mb,orden,pila,apilados,grafo,todas_cfc)

        for cfc in todas_cfc:
            if pagina in cfc:
                print(cfc)
        
    

def tarjan(v, visitados,mb,orden,pila,apilados,grafo,todas_cfc):
    visitados.add(v)
    pila.apilar(v)
    apilados.add(v)
    mb[v] = orden[v]

    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            orden[w] = orden[v] + 1
            tarjan(w, visitados,mb,orden,pila,apilados,grafo,todas_cfc)
        
        if w in apilados:
            mb[v] = min(mb[w], mb[v])
    
    if len(pila) > 0 and orden[v] == mb[v]:
        cfc = []
        while True:
            w = pila.desapilar()
            cfc.append(w)
            apilados.remove(w)
            if w == v:
                break
        todas_cfc.append(cfc)

def main():
    print("main")
    grafo = Grafo(True)
    grafo.agregar_vertice("boca")
    grafo.agregar_vertice("river")
    grafo.agregar_vertice("san lorenzo")
    grafo.agregar_vertice("huracan")
    grafo.agregar_vertice("independiente")
    grafo.agregar_vertice("racing")
    grafo.agregar_arista("boca", "river")
    #grafo.agregar_arista("boca", "huracan")
    #grafo.agregar_arista("boca", "independiente")

    grafo.agregar_arista("river", "independiente")
    #grafo.agregar_arista("river", "racing")

    grafo.agregar_arista("independiente", "san lorenzo")
    #grafo.agregar_arista("huracan", "racing")
    grafo.agregar_arista("san lorenzo", "boca")
    #grafo.agregar_arista("racing", "san lorenzo")
    grafo.agregar_arista("racing", "huracan")
    conectados(grafo,"boca")
    

if __name__ == "__main__":
    main()