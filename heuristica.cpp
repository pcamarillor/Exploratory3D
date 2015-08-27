#include "heuristica.h"

Heuristica::Heuristica(vertice *v)
{
    this->meta = v;
}

float Heuristica::calcularHeuristica(vertice *n)
{
    return this->meta->configuracion.Distanica(&n->configuracion);
}
