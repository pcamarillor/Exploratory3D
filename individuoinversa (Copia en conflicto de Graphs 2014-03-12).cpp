#include "individuoinversa.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
IndividuoInversa::IndividuoInversa()
{
}

int* IndividuoInversa::fen2gen()
{
    int fenotipo[15];
    this->punto2fenotipo(&this->xaleat, fenotipo, 0, 4);
    this->punto2fenotipo(&this->yaleat, fenotipo, 5, 9);
    this->punto2fenotipo(&this->zaleat, fenotipo, 10, 14);

    return fenotipo;
}

void IndividuoInversa::Imprimir()
{

    cout << "fenotipo x:" << this->xaleat << " y:" << this->yaleat << " z:" << this->zaleat << std::endl;
    cout << "genotipo:";
    for(int i = 0; i < LARGO_CROMOSOMA; i++)
    {
        cout << genotipo[i];
    }
    cout << std::endl;
}

void IndividuoInversa::generarGenotipo()
{
    this->punto2fenotipo(&this->xaleat, genotipo, 0, 4);
    this->punto2fenotipo(&this->yaleat, genotipo, 5, 9);
    this->punto2fenotipo(&this->zaleat, genotipo, 10, 14);
}

void IndividuoInversa::generarFenotipo()
{
    this->fenotipo2punto(&this->xaleat, genotipo, 0);
    this->fenotipo2punto(&this->yaleat, genotipo, 5);
    this->fenotipo2punto(&this->zaleat, genotipo, 10);
}

void IndividuoInversa::Mutar()
{
    int mt;
    int lugar_mutacion;

    //Se genera el valor para mutar
    mt = rand()%9;
    //Se genera la posición de la mutacion
    lugar_mutacion = rand()%(LARGO_CROMOSOMA - 1);
    genotipo[lugar_mutacion] = mt;

}

std::vector<IndividuoInversa> IndividuoInversa::Cruzar(IndividuoInversa *otro, int ptoCruce)
{
    std::vector<IndividuoInversa> hijos;
    int aux[15];
    int *h1;
    int *h2;

    h1 = this->genotipo;
    for(int i = 0; i < LARGO_CROMOSOMA; i++)
        aux[i] = *(h1 + i);
    h2 = otro->genotipo;

    for(int i = 0; i <= ptoCruce;i++)
        *(h1 + i) = *(h2 + i);

    for(int i = 0; i <= ptoCruce;i++)
        *(h2 + i) = *(aux + i);

    IndividuoInversa h11(h1);
    IndividuoInversa h22(h2);
    hijos.push_back(h11);
    hijos.push_back(h22);
    return hijos;
}

void IndividuoInversa::punto2fenotipo(float *pto, int *fenotipo, int inf, int sup)
{
    int entera;
    float dec;
    int dec_entera;
    int array[5];
    entera = (int)*pto;
    dec = *pto - entera;
    dec_entera = dec*100;
    for(int i = 2; i >= 0;i--)
    {
        array[i] = entera % 10;
        entera = entera / 10;
    }

    for(int i = 4; i >= 3;i--)
    {
        array[i] = dec_entera % 10;
        dec_entera = dec_entera / 10;
    }


    for(int i = inf, j = 0; i <= sup;i++, j++)
        *(fenotipo + i) = array[j];

}

void IndividuoInversa::fenotipo2punto(float *pto, int *fenotipo, int inf)
{
    int centenas, decenas, unidades;
    float base = 10;
//    for(int i = 0; i < LARGO_CROMOSOMA;i++)
//        cout << *(fenotipo + i) << " ";
//    cout << endl;
    centenas = pow(base,2)*(*(fenotipo + inf));
    decenas = pow(base,1)*(*(fenotipo + inf + 1));
    unidades = pow(base,0)*(*(fenotipo + inf + 2));

    float centesimas, milesimas;
    centesimas = pow(base,-1)*(*(fenotipo + inf + 3));
    milesimas = pow(base,-2)*(*(fenotipo + inf + 3));

    *pto = centenas + decenas + unidades + centesimas + milesimas;
}

float* IndividuoInversa::gen2fen(int* fenotipo)
{
    float o[3];

    return o;
}

float  IndividuoInversa::Gr2Rad(float grados)
{
    return (3.1416*grados)/180;
}

float IndividuoInversa::fitness(float *objetivo)
{
    float px, py, pz;
    float d6 = 1.0f;
    float d2 = 1.8f;
    float a2 = 3.3f;
    float a3 = 0.0f;
    float d4 = 3.3f;

    float t1 = Gr2Rad(this->xaleat);
    float t2 = Gr2Rad(this->yaleat);
    float t3 = Gr2Rad(this->zaleat);
    float t4 = Gr2Rad(0);
    float t5 = Gr2Rad(0);

    px = cos(t1)*(d6*(cos(t2 + t3)*cos(t4)*sin(t5) + sin(t2 + t3)*cos(t5)) + sin(t2 + t3)*d4 + a3*cos(t2+t3) + a2*cos(t2)) - (sin(t1)*(d6*sin(t4)*sin(t5) + d2));
    py = sin(t1)*(d6*(cos(t2 + t3)*cos(t4)*sin(t5) + sin(t2 + t3)*cos(t5)) + sin(t2 + t3)*d4 + a3*cos(t2+t3) + a2*cos(t2)) + (cos(t1)*(d6*sin(t4)*sin(t5) + d2));
    pz = d6*(cos(t2 + t3)*cos(t5) - sin(t2 + t3)*cos(t4)*sin(t5)) + cos(t2 + t3)*d4 - a3*sin(t2 + t3) - a2*sin(t2);

    return sqrt(pow(*(objetivo + 0) - px,2) +
                pow(*(objetivo + 1) - py,2) +
                pow(*(objetivo + 2) - pz,2));

}
