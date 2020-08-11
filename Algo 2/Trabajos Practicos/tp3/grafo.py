import random

class Grafo():
    def __self__(self,dirigido):
        self.vertices = {}
        self.dirigido = dirigido
    
    def existe_vertice(self,v):
        return v in self.vertices.keys()
    
    def agregar_vertice(self,v):
        if not existe_vertice(self,v):
            self.vertices[v] = {}
    
    def agregar_arista(self,inicio,fin,peso=1):
        if existe_vertice(self,inicio) and existe_vertice(self,fin):
            self.vertices[inicio][fin] = peso
            if self.dirgido == False:
                self.vertices[fin][inico] = peso
             
    def sacar_vertice(self,v):
        if existe_vertice(self,v):
            self.vertices.pop(v)
        for i in self.vertices:
            if v in self.vertices[i].keys:
                self.vertices[i].pop(v)
    
    def sacar_arista(self,inicio,fin):
        if existe_vertice(self,inicio) and existe_vertice(self,fin):
            if fin in self.vertices[inicio].keys():
                self.vertices[inicio].pop(fin)
            if self.dirgido == False:
                if inicio in self.vertices[fin].keys():
                    self.vertices[fin].pop(inicio)
 
    def estan_unidos(self,inicio,fin):
        if existe_vertice(self,inicio) and existe_vertice(self,fin):
            if self.dirigido == True:
                return fin in self.vertices[inicio].keys()
            else:
                return (fin in self.vertices[inicio].keys()) and (inicio in self.vertices[fin].keys())
        return False
        
    def vertice_random(self):
        tamanio = len(self.vertices)
        numero_aleatorio = random.randrange(tamanio)
    
    def obtener_vertices(self):
    
    def obtener_adyacentes(self):
        
    def recorrer_bfs(self):
    
    def recorrer_dfs(self):