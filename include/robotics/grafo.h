#ifndef GRAFO_H
#define GRAFO_H

#include <QList>
#include <QQueue>
#include "arista.h"
#include "punto3d.h"
#include "heuristica.h"
#include "qgl.h"
#include <iostream>

using namespace std;
class Grafo
{
public:
    Grafo();
    QList<vertice*> vertices;
    QList<Arista> aristas;

    vertice* agregarVerticeQ(punto3d q);
    void agregarVertice(vertice *v);
    void agregarArco(vertice *o, vertice *d);
    void agregarArco(Arista a);
    QList<vertice> AEstrella(vertice *ini, vertice*fin);
    QList<vertice> Dijkstra(vertice *ini, vertice* fin);
    QList<vertice> generarRuta(vertice *n, vertice *meta);
    vertice* elementoConMenorCosto(QList<vertice*> *lista);
    int indexElementoMenor(QQueue<vertice*> cola);
    vertice* EncontrarVertice(vertice *buscado);
    int EncontrarIndexVertice(vertice *buscado);
    void Dibujar();
};

#endif // GRAFO_H
