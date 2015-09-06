#ifndef INDIVIDUOSET_H
#define INDIVIDUOSET_H

#include "manipulador.h"
#include "individuo.h"
#include "objeto3D.h"
#include "escena.h"
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

class IndividuoSET : public Individuo
{
public:
    IndividuoSET()
    {
        this->fenotipo = 0;
        this->LargoCromosoma = 20;
    }
    IndividuoSET(int value, int lc)
    {
        this->fenotipo = value;
        this->LargoCromosoma = lc;
    }
    IndividuoSET(int * valores, int largo, int max):Individuo(valores)
    {
        this->LargoCromosoma = largo;
        this->maximo = max;
        cout << "largo:" << this->LargoCromosoma << endl;
        genotipo = new int[this->LargoCromosoma];
        for(int i = 0; i < this->LargoCromosoma; i++)
            *(genotipo + i) = *(valores  + i);
    }

    void generarGenotipo(int v);
    void generarFenotipo();
    float fitness(Manipulador *rob, Escena *esc, punto3d *config);
    vector<IndividuoSET> Cruzar(IndividuoSET *otro, int ptoCruce);
    void Mutar();
    float getFitnessCalculada();
    friend std::ostream& operator<<(std::ostream& os, IndividuoSET& ind)
    {
        int *v;
        v = ind.getValues();
        os << "fenotipo " << ind.fenotipo << endl;
        os << "genotipo:";
        for(int i = ind.LargoCromosoma -1; i >= 0; i--)
        {
            os << *(ind.genotipo + i) << " ";
        }
        os << endl;
        return os;
    }
    int LargoCromosoma;
    int *genotipo;
    int fenotipo;
    int maximo;
    float fit;

};

#endif // INDIVIDUOSET_H
