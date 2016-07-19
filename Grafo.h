#ifndef GRAFO_H
#define	GRAFO_H

typedef int TElemento;

typedef struct arista{
    TElemento info;
    float peso;
    struct arista *sig;
}TArista;

typedef struct vertice{
    TElemento info;
    TArista *aristasInicio;
    TArista *aristasFin;
    struct vertice *sig;
}TVertice;

typedef struct grafo{
    int numVertices;
    
    TVertice *adjInicio;
    TVertice *adjFin;
}TGrafo;

void inicializar_Mapa(TGrafo *);
void insertar_Space_Mapa(TGrafo *, TElemento);
void insertar_Aristas_Mapa(TGrafo *, TElemento, TElemento, float);
void imprimir_Mapa(TGrafo *);

#endif