#include "genetico.h"

genetico::genetico()
{
    this->numGeneraciones = 100;
    this->tamPoblacion = 20;
    this->pCruza = 0.8;
    this->pMutacion = 0.2;
}


genetico::genetico(int _nGeneraciones, int _tPoblacion, float _pCruza, float _pMutacion)
{
    this->numGeneraciones = _nGeneraciones;
    this->tamPoblacion = _tPoblacion;
    this->pCruza = _pCruza;
    this->pMutacion = _pMutacion;
}

genetico::~genetico()
{

}
