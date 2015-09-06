#ifndef INDIVIDUO_H
#define INDIVIDUO_H

class Individuo
{
public:
    Individuo();
    Individuo(int* _values);
    int* getValues();
    void setValues(int *nvoCromosoma);
protected:
    int* Values;
};

#endif // INDIVIDUO_H
