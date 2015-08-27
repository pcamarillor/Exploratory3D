#include "individuoset.h"
#include "parescaneo.h"

void IndividuoSET::generarGenotipo(int v)
{
    //De número Real, pasa a binario en un arreglo
    int entera, modulo;

    entera = v;
    for(int i = 0; i < this->LargoCromosoma; i++)
    {
        modulo = entera % 2;
        *(genotipo + i) = modulo;
        entera = entera / 2;
    }
}

void IndividuoSET::generarFenotipo()
{
    //De un arreglo de 0s y 1s, pasa a entero
    int suma = 0;
    float base = 2;
    float potencia = 0;
    for(int i = (this->LargoCromosoma - 1); i >= 0;i--)
    {
        potencia = i;
        suma = suma + *(genotipo + i)*pow(base, potencia);
    }
    fenotipo = suma;
}

float IndividuoSET::getFitnessCalculada()
{
    return this->fit;
}

float IndividuoSET::fitness(Manipulador *rob, Escena *esc, punto3d *config)
{
    //Se calcula el volumen del solido, en esa configuracion
    vector<ParEscaneo> pe;
    this->generarFenotipo();
    rob->CinematicaInversa(config->getX(), config->getY(), config->getZ());
    pe = rob->Escanear(esc);
    this->fit = 0;
    for(int i = 0; i < pe.size();i++)
        this->fit += pe.at(i).fronteraLibre.CalcularVolumen();
    return this->fit;
}

vector<IndividuoSET> IndividuoSET::Cruzar(IndividuoSET *otro, int ptoCruce)
{
    //Se cruza el individuo con uno nuevo y los resultados se almacenan
    //en un vector de salida.
    vector<IndividuoSET> hijos;
    int *aux = new int[this->LargoCromosoma];
    int *h1;
    int *h2;


    h1 = this->genotipo;
    for(int i = this->LargoCromosoma - 1; i >= 0 ; i--)
    {
        *(aux + i) = *(h1 + i)  ;
        cout << *(aux + i)<< " ";;
    }
    cout << endl;
    h2 = otro->genotipo;

    for(int i = 0; i <= ptoCruce;i++)
    {
        *(h1 + i) = *(h2 + i);
    }

    for(int i = 0; i <= ptoCruce;i++)
    {
        *(h2 + i) = *(aux + i);
    }

    IndividuoSET h11(h1, this->LargoCromosoma, this->maximo);
    IndividuoSET h22(h2, this->LargoCromosoma, this->maximo);
    h11.generarFenotipo();
    h22.generarFenotipo();
    h11.fenotipo = h11.fenotipo >= this->maximo ? h11.fenotipo % (this->maximo - 1) : h11.fenotipo;
    h22.fenotipo = h22.fenotipo >= this->maximo ? h22.fenotipo % (this->maximo - 1) : h22.fenotipo;
    hijos.push_back(h11);
    hijos.push_back(h22);
    return hijos;
}

void IndividuoSET::Mutar()
{
   // srand(time(NULL));
    //Se cambia un valor del genotipo
    int lugar_mutacion;

    //Se genera la posición de la mutacion
    lugar_mutacion = rand()%(this->LargoCromosoma);
    if(*(genotipo + lugar_mutacion) == 0)
        *(genotipo + lugar_mutacion) = 1;
    else
        *(genotipo + lugar_mutacion) = 0;

    this->generarFenotipo();
    this->fenotipo = this->fenotipo > this->maximo ?  this->fenotipo % (this->maximo - 1) : this->fenotipo;
    this->generarGenotipo(this->fenotipo);
}

