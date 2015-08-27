/*
 * Implementación del nodo del árbol de exploración basado en sensores.
*/
#ifndef NODOSET_H
#define NODOSET_H
#include "punto3d.h"
#include "parescaneo.h"
#include <vector>
using namespace std;
class NodoSET
{
public:
    NodoSET(NodoSET *p);
    NodoSET(ParEscaneo _q, NodoSET *p, float _u);
    void AgregarHijo(NodoSET *hijo);
    ~NodoSET();
    punto3d GetPunto();
    void SetUtility(float _u);
    int GetNumNodos();
    NodoSET *padre;
    friend std::ostream& operator<<(std::ostream& os, NodoSET& nodo)
    {
        os << "x:" << nodo.GetPunto().getX() << " y:" << nodo.GetPunto().getY() << " z:" << nodo.GetPunto().getZ() << std::endl;
        return os;
    }
private:
    ParEscaneo q; //Configuración, region libre segura, obstaculo y configuracion
    float Utility; //Uilidad calculada (volumen del poliedro que representa la mayor frontera libre)
    vector<NodoSET*> hijos;

};

#endif // NODOSET_H
