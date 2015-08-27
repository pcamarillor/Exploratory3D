#include "individuo.h"

Individuo::Individuo()
{
   int valores[15];
   this->Values = &valores[0];
}

Individuo::Individuo(int* _values)
{
   this->Values = _values;
}

int* Individuo::getValues()
{
    return this->Values;
}

void Individuo::setValues(int *nvoCromosoma)
{
    this->Values = nvoCromosoma;
}
