#ifndef GENETICO_H
#define GENETICO_H
#include <iostream>
#include <vector>
#include "individuo.h"

using namespace std;
class genetico
{
public:
    genetico();
    genetico(int _nGeneraciones, int _tPoblacion, float _pCruza, float _pMutacion);
    ~genetico();
protected:
    int numGeneraciones;
    int tamPoblacion;
    float pCruza;
    float pMutacion;

};

#endif // GENETICO_H
