#ifndef GENETICOINVERSA_H
#define GENETICOINVERSA_H
#include <iostream>
#include <map>
#include "genetico.h"
#include "individuoinversa.h"
#include "sort_map.h"

using namespace std;
class GeneticoInversa : public genetico
{
public:
    GeneticoInversa():genetico()
    {
        float a[3];
        this->objetivo = a;
    }

    GeneticoInversa(float pCr, float pMut, int nGen, int tPob, float* obj):genetico(nGen, tPob, pCr, pMut)
    {
        this->objetivo = obj;
    }

    void Ejecutar();
    void GenerarPoblacionInicial();
    void EvaluarPoblacion(vector< sort_map> *fitness);
    float * ObtenerValorEsperado(int op);
    IndividuoInversa MejorIndividuo;
    vector<IndividuoInversa> ObtenerNuevaPoblacion();
    std::vector<int*> ObtenerGenotipos();

    float suma(vector<sort_map> vec);
    vector<IndividuoInversa> poblacion;
    ~GeneticoInversa();
     float *objetivo;

};



#endif // GENETICOINVERSA_H
