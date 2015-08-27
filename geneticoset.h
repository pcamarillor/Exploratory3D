#ifndef GENETICOSET_H
#define GENETICOSET_H
#include "manipulador.h"
#include "genetico.h"
#include "sort_map.h"
#include "individuoset.h"
#include "escena.h"


class GeneticoSET : public genetico
{
public:

    //El robot, es el manipulador que realiza la exploración,
    //El escenario, es el ambiente que se desea reconstruir
    //La frontera libre se refiere al sensor a partir del cual, se está buscando el siguiente
    //punto de visión.
    vector<IndividuoSET> poblacion;
    IndividuoSET MejorIndividuo;
    Manipulador *robot;
    Escena *escenario;
    Objeto3D *fronteraL;
    int LargoCromosoma; //Este largo se adapta al tamaño de la poblacion de configuraciones candidatas
    GeneticoSET(float pCr, float pMut, int nGen, int tPob, Manipulador *rob, Escena *esc, Objeto3D *fronteraLibre):genetico(nGen, tPob, pCr, pMut)
    {
        this->robot = rob;
        this->escenario = esc;
        this->fronteraL = fronteraLibre;
    }
    ~GeneticoSET();

    void Ejecutar(int *numEscaneos, int estrategia);
    void GenerarPoblacionInicial();
    void EvaluarPoblacion(vector< sort_map> *fitness, int *numEscaneos);
    vector<IndividuoSET> ObtenerNuevaPoblacion(int *numEscaneos);

};

#endif // GENETICOSET_H
