/*
 * Implementación del árbol de exploración basado en sensores
 * (Sensor-Based Exploration Tree)
*/
#ifndef SET_H
#define SET_H
#include "nodoset.h"

class SET
{
public:
    SET();
    SET(NodoSET *r);
    ~SET();

    NodoSET *raiz;
    NodoSET GenerarNuevaConfiguracion();
    void AgregarHijo(NodoSET *padre, NodoSET *hijo);
    int GetNumNodos();
};

#endif // SET_H
