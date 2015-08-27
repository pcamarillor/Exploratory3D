#include "arista.h"
#include "vertice.h"
Arista::Arista()
{}
Arista::Arista(vertice *o, vertice *d)
{
    this->origen = o;
    this->destino = d;
}

float Arista::peso()
{
    return this->origen->configuracion.Distanica(&destino->configuracion);
}
