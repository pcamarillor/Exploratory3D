#include "geneticoset.h"
bool Sort_bySET(const sort_map& a ,const sort_map& b)
{
    return a.val < b.val;
}

void GeneticoSET::Ejecutar(int *numEscaneos, int estrategia)
{
    srand(time(NULL));
    vector<IndividuoSET> nva;
    vector<IndividuoSET> mejores;
    IndividuoSET tmp;
    float desc;
    int pto_cruza;
    IndividuoSET papa;
    IndividuoSET mama;
    vector<IndividuoSET> hijos;
    if(estrategia == 1) //Estrategia del genético
    {
        for(int i = 0; i <= this->numGeneraciones; i++)
        {

            mejores     = this->ObtenerNuevaPoblacion(numEscaneos);
            nva.clear();

            //Proceso de cruza
            for(int j = 0; j < mejores.size() - 1; j = j + 2)
            {
                //CRUZA en un punto
                pto_cruza = rand()%(this->LargoCromosoma - 1);
                papa = mejores.at(j);
                mama = mejores.at(j + 1);
                nva.push_back(papa);
                nva.push_back(mama);
                hijos = papa.Cruzar(&mama, pto_cruza);

                papa = hijos[0];
                papa.generarFenotipo();
                mama = hijos[1];
                mama.generarFenotipo();
                nva.push_back(papa);
                nva.push_back(mama);
            }

            //Proceso de mutación
            for(int j = 0; j < nva.size(); j++)
            {
                desc = ((double) rand() / (RAND_MAX));
                if(desc < this->pMutacion)
                {
                    tmp = nva.at(j);
                    tmp.Mutar();
                    tmp.generarFenotipo();
                    //                cout << "j:" << j << endl;
                    nva[j] = tmp;
                    //                cout << nva[j] << endl;
                }
            }
            this->poblacion = nva;
        }
        papa = nva.at(0);
        papa.generarFenotipo();
        this->MejorIndividuo = papa;
     }
    else if(estrategia == 2) //Estrategia de los centroides
    {
        vector<sort_map> fitness;
        sort_map key_valuePair;
        int pos;
        fitness.clear();
        for(int i = 0; i < 10;i++)
        {

            pos = rand() % (this->fronteraL->configuracionesCandidatas.size()-1);
            key_valuePair.key = pos;
            key_valuePair.val = this->poblacion.at(pos).fitness(this->robot, this->escenario, &this->fronteraL->configuracionesCandidatas.at(pos));
            *numEscaneos = *numEscaneos + 1;
            fitness.push_back(key_valuePair);
        }
        sort(fitness.begin(), fitness.end(), Sort_bySET);
        this->MejorIndividuo = this->poblacion.at(fitness.at(0).key);
    }

}

void GeneticoSET::GenerarPoblacionInicial()
{
    srand(time(NULL));
    int valor;
    IndividuoSET ind;
    int entera, largo = 0;
    //Se determina el ancho que puede tener el cromosoma
    entera = this->fronteraL->configuracionesCandidatas.size();
    while(entera >= 1)
    {
        entera = entera / 2;
        largo++;
    }
    this->LargoCromosoma = largo;
//    for(int i = 0; i < this->tamPoblacion; i++)
//    {
//        valor = rand() % (this->fronteraL->configuracionesCandidatas.size()-1);
//        ind.LargoCromosoma = this->LargoCromosoma;
//        ind.genotipo = new int[largo];
//        ind.maximo = this->fronteraL->configuracionesCandidatas.size();
//        ind.generarGenotipo(valor);
//        ind.generarFenotipo();
//        this->poblacion.push_back(ind);
//    }
    for(int i = 0; i < this->fronteraL->configuracionesCandidatas.size(); i++)
    {
        ind.LargoCromosoma = this->LargoCromosoma;
        ind.genotipo = new int[largo];
        ind.maximo = this->fronteraL->configuracionesCandidatas.size();
        ind.generarGenotipo(i);
        ind.generarFenotipo();
        this->poblacion.push_back(ind);
    }
}

void GeneticoSET::EvaluarPoblacion(vector< sort_map> *fitness,int *numEscaneos)
{
    sort_map key_valuePair;
    int pos;
    fitness->clear();
    for(int i = 0; i < this->poblacion.size();i++)
    {
        pos = this->poblacion.at(i).fenotipo;
        pos = pos % this->fronteraL->configuracionesCandidatas.size();
        cout << "pos:" << pos << " tam:" << this->fronteraL->configuracionesCandidatas.size() << endl;
        key_valuePair.key = i;
        key_valuePair.val = this->poblacion.at(i).fitness(this->robot, this->escenario, &this->fronteraL->configuracionesCandidatas.at(pos));
        *numEscaneos = *numEscaneos + 1;
        fitness->push_back(key_valuePair);
    }
}




vector<IndividuoSET> GeneticoSET::ObtenerNuevaPoblacion(int *numEscaneos)
{
    vector<IndividuoSET> nvaPob;
    vector<sort_map> fitness;
    this->EvaluarPoblacion(&fitness,numEscaneos);
    sort(fitness.begin(), fitness.end(), Sort_bySET);
    sort_map mp;
    for(int i = 0; i < fitness.size()/2; i++)
    {
        mp = fitness.at(i);
        nvaPob.push_back(this->poblacion.at(mp.key));
    }

    return nvaPob;
}
