import random

class Grafo():
    def __init__(self,dirigido):
        self.vertices = {}
        self.dirigido = dirigido
    
    def existe_vertice(self,v):
        return v in self.vertices.keys()
    
    def agregar_vertice(self,v):
        if not self.existe_vertice(v):
            self.vertices[v] = {}
    
    def agregar_arista(self,inicio,fin,peso=1):
        if self.existe_vertice(inicio) and self.existe_vertice(fin):
            self.vertices[inicio][fin] = peso
            if self.dirigido == False:
                self.vertices[fin][inicio] = peso
             
    def sacar_vertice(self,v):
        if self.existe_vertice(v):
            self.vertices.pop(v)
        for i in self.vertices:
            if v in self.vertices[i].keys:
                self.vertices[i].pop(v)
    
    def sacar_arista(self,inicio,fin):
        if self.existe_vertice(inicio) and self.existe_vertice(fin):
            if fin in self.vertices[inicio].keys():
                self.vertices[inicio].pop(fin)
            if self.dirigido == False:
                if inicio in self.vertices[fin].keys():
                    self.vertices[fin].pop(inicio)
 
    def estan_unidos(self,inicio,fin):
        if self.existe_vertice(inicio) and self.existe_vertice(fin):
            if self.dirigido == True:
                return fin in self.vertices[inicio].keys()
            else:
                return (fin in self.vertices[inicio].keys()) and (inicio in self.vertices[fin].keys())
        return False
        
    def vertice_random(self):
        longitud = len(self.vertices)
        numero_aleatorio = random.randrange(longitud)
        claves = list(self.vertices.keys())
        return claves[numero_aleatorio]
    
    def obtener_vertices(self):
        return list(self.vertices.keys())
    
    def obtener_adyacentes(self,v):
        if self.existe_vertice(v):
            return list(self.vertices[v].keys())
        return None

    def esta_vacio(self):
        return True if len(self.obtener_vertices()) == 0 else False