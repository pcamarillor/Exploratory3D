#ifndef INDIVIDUOINVERSA_H
#define INDIVIDUOINVERSA_H
#include "individuo.h"
#include <iostream>
#include <vector>
#define LARGO_CROMOSOMA  15
class IndividuoInversa : public Individuo
{
public:
    IndividuoInversa();

    IndividuoInversa(float x, float y, float z):Individuo()
    {
        this->xaleat = x;
        this->yaleat = y;
        this->zaleat = z;

    }

    IndividuoInversa(int * valores):Individuo(valores)
    {
        for(int i = 0; i < LARGO_CROMOSOMA; i++)
            genotipo[i] = *(valores  + i);
    }

    int* fen2gen();
    float* gen2fen(int* fenotipo);
    void generarGenotipo();
    void generarFenotipo();
    void punto2fenotipo(float *pto, int *fenotipo, int inf, int sup);
    void fenotipo2punto(float *pto, int *fenotipo, int inf);
    float fitness(float *objetivo);
    float Gr2Rad(float grados);
    std::vector<IndividuoInversa> Cruzar(IndividuoInversa *otro, int ptoCruce);
    void Mutar();
    void Imprimir();
    friend std::ostream& operator<<(std::ostream& os, IndividuoInversa& ind)
    {
        int *v;
        v = ind.getValues();
        os << "fenotipo x:" << ind.xaleat << " y:" << ind.yaleat << " z:" << ind.zaleat << std::endl;
        os << "genotipo:";
        for(int i = 0; i < LARGO_CROMOSOMA; i++)
        {
            os << ind.genotipo[i] << " ";
        }
        os << std::endl;
        return os;
    }
    int genotipo[15];
    float xaleat, yaleat, zaleat;

};

#endif // INDIVIDUOINVERSA_H
