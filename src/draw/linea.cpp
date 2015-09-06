#include "linea.h"

Linea::Linea()
{
    this->punto.setX(0);
    this->punto.setY(0);
    this->punto.setZ(0);

    this->vectorDireccion.setX(1);
    this->vectorDireccion.setY(1);
    this->vectorDireccion.setZ(1);
}

Linea::Linea(punto3d pto, punto3d  vectorDir)
{
    this->punto = pto;
    this->vectorDireccion = vectorDir;
}
