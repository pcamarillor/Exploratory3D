#include "vertice.h"

vertice::vertice()
{
    predecesor = NULL;
    configuracion.setX(0);
    configuracion.setY(0);
    configuracion.setZ(0);
    costoHastaAhora = 0;
    costoEstimado = 0;
    costoTotalEstimado = 0;
    visitado = false;
}

vertice::vertice(punto3d q)
{
    predecesor = NULL;
    configuracion = q;
    costoHastaAhora = 0;
    costoEstimado = 0;
    costoTotalEstimado = 0;
    visitado = false;
}


void vertice::addAdyacente(vertice *v, Arista a)
{
    adyacentes.push_back(v);
    conexiones.push_back(a);
}

void vertice::addAdyacente(vertice *v)
{
    Arista a(this,v);
    adyacentes.push_back(v);
    conexiones.push_back(a);
}

void vertice::addConexion(Arista a)
{
    conexiones.push_back(a);
}

bool vertice::esIgual(vertice * otro)
{
    return this->configuracion.getX() == otro->configuracion.getX() &&
           this->configuracion.getY() == otro->configuracion.getY() &&
           this->configuracion.getZ() == otro->configuracion.getZ();
}
