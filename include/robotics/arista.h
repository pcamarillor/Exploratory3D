#ifndef ARISTA_H
#define ARISTA_H

class vertice;
class Arista
{
public:
    Arista();
    Arista(vertice *o, vertice *d);
    vertice *origen;
    vertice *destino;
    float peso();

};

#endif // ARISTA_H
