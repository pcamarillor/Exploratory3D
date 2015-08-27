#ifndef NODORRT_H
#define NODORRT_H
#include <QList>
#include <qgl.h>
#include <iostream>
#include "punto3d.h"
using namespace std;
class NodoRRT
{
public:
    NodoRRT();
    NodoRRT(punto3d dato);
    void AgregarHijo(NodoRRT *hijo);
    NodoRRT* HijoMasProximo(NodoRRT *x);
    void Dibujar();
    void Imprimir();
    NodoRRT *padre;
    punto3d configuracion;
    QList<NodoRRT*> hijos;

};

#endif // NODORRT_H
