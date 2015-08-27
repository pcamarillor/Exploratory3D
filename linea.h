#ifndef LINEA_H
#define LINEA_H
#include "punto3d.h"

class Linea
{
public:
    Linea();
    Linea(punto3d pto, punto3d  vectorDir);
    //Una linea se puede definir por un punto y un vector de direccion
    punto3d punto;
    punto3d vectorDireccion;
};

#endif // LINEA_H
