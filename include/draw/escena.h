#ifndef ESCENA_H
#define ESCENA_H

#include <iostream>
#include <vector>
#include "objeto3D.h"

class Escena
{
public:
    Escena();
    ~Escena();
    void Abrir(char* path);
    void Dibujar();
    int getNumObjetos();
    std::vector<Objeto3D> objetos;
};

#endif // ESCENA_H
