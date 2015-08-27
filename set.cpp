#include <stdlib.h>
#include <time.h>
#include "set.h"

SET::SET()
{
    this->raiz = new NodoSET(NULL);
}

SET::SET(NodoSET *r)
{
    this->raiz = r;
}

NodoSET SET::GenerarNuevaConfiguracion()
{
    srand(time(NULL));
    int a = -4;
    int b = 4;
    float xaleat,yaleat,zaleat;

    xaleat = (b - a)*((double)rand() / RAND_MAX) + a;

    yaleat = (b - a)*((double)rand() / RAND_MAX) + a;

    zaleat = (b - a)*((double)rand() / RAND_MAX) + a;

    punto3d config;
    config.setX(xaleat);
    config.setY(yaleat);
    config.setZ(zaleat);
    ParEscaneo pe;
    pe.configuracion = config;
    NodoSET nodo(pe, NULL, 0);
    return nodo;
}

void SET::AgregarHijo(NodoSET *padre, NodoSET *hijo)
{
    padre->AgregarHijo(hijo);
}

int SET::GetNumNodos()
{
    return this->raiz->GetNumNodos();
}

SET::~SET()
{

}
