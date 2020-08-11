from grafo import Grafo


def main():
    grafo = Grafo(True)
    grafo.agregar_vertice("boca")
    grafo.agregar_vertice("river")
    grafo.agregar_vertice("independiente")
    grafo.agregar_vertice("san lorenzo")
    grafo.agregar_vertice("racing")
    print(grafo.obtener_vertices())
    print(grafo.obtener_vertices())
    grafo.agregar_arista("boca", "river")
    print(grafo.obtener_adyacentes("boca"))

if __name__ == "__main__":
    main()