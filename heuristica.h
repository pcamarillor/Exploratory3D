#ifndef HEURISTICA_H
#define HEURISTICA_H
#include "vertice.h"

class Heuristica
{
public:
    Heuristica(vertice* meta);
    float calcularHeuristica(vertice *n);
    vertice* meta;
};

#endif // HEURISTICA_H
