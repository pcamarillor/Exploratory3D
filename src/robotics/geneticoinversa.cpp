#include "geneticoinversa.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>


bool Sort_by(const sort_map& a ,const sort_map& b)
{
    return a.val < b.val;
}

void GeneticoInversa::Ejecutar()
{
    srand(time(NULL));
    vector<IndividuoInversa> nva;
    vector<IndividuoInversa> mejores;
    IndividuoInversa tmp;
    float desc;

    int pto_cruza;
    IndividuoInversa papa;
    IndividuoInversa mama;
    vector<IndividuoInversa> hijos;
    for(int i = 1; i < this->numGeneraciones; i++)
    {

        mejores     = this->ObtenerNuevaPoblacion();
        nva.clear();

        //Proceso de cruza
        for(int j = 0; j < mejores.size() - 1; j = j + 2)
        {
            //CRUZA en un punto
            pto_cruza = rand()%(LARGO_CROMOSOMA - 1);
            papa = mejores.at(j);
            mama = mejores.at(j + 1);
            nva.push_back(papa);
            nva.push_back(mama);
            hijos = papa.Cruzar(&mama, pto_cruza);
            papa = hijos[0];
            papa.generarFenotipo();
            if(papa.xaleat < -160)
                papa.xaleat = -160 % (int)papa.xaleat;
            else if(papa.xaleat > 160)
                papa.xaleat = 160 % (int)papa.xaleat;

            if(papa.yaleat < -225)
                papa.yaleat = -225 % (int)papa.yaleat;
            else if(papa.yaleat > 45)
                papa.yaleat = 45 % (int)papa.yaleat;


            if(papa.zaleat < -45)
                papa.zaleat = -45 % (int)papa.zaleat;
            else if(papa.zaleat > 225)
                papa.zaleat = 225 % (int)papa.zaleat;

            mama = hijos[1];
            mama.generarFenotipo();
            nva.push_back(papa);
            nva.push_back(mama);
        }

        //Proceso de mutación
        for(int j = 0; j < this->tamPoblacion; j++)
        {
            desc = ((double) rand() / (RAND_MAX));
            if(desc < this->pMutacion)
            {
                tmp = nva.at(j);
                tmp.Mutar();
                tmp.generarFenotipo();
                nva[j] = tmp;
            }
        }

        this->poblacion = nva;
    }
    sort_map m;
    vector<sort_map> fit;
    for(int i = 0; i < nva.size();i++)
    {
        nva.at(i).generarFenotipo();
        m.key = i;
        m.val = nva.at(i).fitness(this->objetivo);
        fit.push_back(m);
    }
    sort(fit.begin(), fit.end(), Sort_by);
    papa = nva.at(fit.at(0).key);
    papa.generarFenotipo();
    this->MejorIndividuo = papa;

}

void GeneticoInversa::EvaluarPoblacion(vector<sort_map> *fitness)
{
    IndividuoInversa tmp;
    sort_map sm;

    for(int i = 0; i < this->tamPoblacion; i++)
    {
        tmp = this->poblacion.at(i);
        sm.key = i;

        sm.val = tmp.fitness(this->objetivo);
        fitness->push_back(sm);
    }
}

float GeneticoInversa::suma(vector<sort_map> vec)
{
    float sum = 0;
    sort_map sm;
    for(int i = 0; i < this->tamPoblacion; i++)
    {
        sm = vec.at(i);
        sum += sm.val;
    }

    return sum;

}

float * GeneticoInversa::ObtenerValorEsperado(int op)
{
    float media;
    float suma;
    float pob = this->tamPoblacion;
    float valorEsperado[20];
    float sumCuadrados = 0;
    float sigma;
    vector< sort_map> fitness;
    sort_map sm;
    this->EvaluarPoblacion(&fitness);
    suma = this->suma(fitness);
    media = suma/(this->tamPoblacion);
    switch(op)
    {
        case 1:
            //Complemento original
            for(int i = 0; i < this->tamPoblacion; i++)
            {
                sm = fitness.at(i);
                valorEsperado[i] = sm.val / media;
            }
            break;
        case 2:
            //Complemento escalamiento sigma
            for(int i = 0; i < this->tamPoblacion; i++)
            {
                sm = fitness.at(1);
                sumCuadrados += pow(sm.val,2);
            }
            sigma = sqrt((this->tamPoblacion*sumCuadrados - pow(suma,2))/(pow(pob,2)));

            for(int i = 0; i < this->tamPoblacion; i++)
            {
                sm = fitness.at(i);
                if(sigma == 0)
                    valorEsperado[i] = 1;
                else
                    valorEsperado[i] = 1 + (sm.val - media)/(2*sigma);
            }
            break;
    }

    return valorEsperado;

}

vector<IndividuoInversa> GeneticoInversa::ObtenerNuevaPoblacion()
{

    vector<IndividuoInversa> nvaPob;
    vector< sort_map> fitness;
    this->EvaluarPoblacion(&fitness);
    sort(fitness.begin(), fitness.end(), Sort_by);


    sort_map mp;
    for(int i = 0; i < fitness.size()/2; i++)
    {
        mp = fitness.at(i);
        nvaPob.push_back(this->poblacion.at(mp.key));
    }

    return nvaPob;
}


std::vector<int*> GeneticoInversa::ObtenerGenotipos()
{
   std::vector<int*> genotipos;
   int * genotipo;
   IndividuoInversa tmp;
   for(int i = 0; i < this->tamPoblacion; i++)
   {
       tmp = this->poblacion.at(i);
       genotipo = tmp.fen2gen();
       genotipos.push_back(genotipo);
   }
   return genotipos;
}

void GeneticoInversa::GenerarPoblacionInicial()
{
    srand(time(NULL));
    float xaleat;
    float yaleat;
    float zaleat;
    IndividuoInversa *ind;
    int a = 0;
    int b = 360;
    for(int i = 0; i < this->tamPoblacion; i++)
    {
        xaleat = ((160 + 160)*((float)rand()/RAND_MAX)) - 160;
        yaleat = ((45 + 225)*((float)rand()/RAND_MAX)) - 225;
        zaleat = ((225 + 45)*((float)rand()/RAND_MAX)) -45;
        ind = new IndividuoInversa(xaleat, yaleat, zaleat);
        ind->generarGenotipo();
        this->poblacion.push_back(*ind);
    }
}


