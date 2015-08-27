#ifndef NODOSRT_H
#define NODOSRT_H
#include "punto3d.h"
#include "parescaneo.h"
#include <qgl.h>

class NodoSRT
{
public:
    NodoSRT(NodoSRT *p);
    NodoSRT(punto3d qact, vector<ParEscaneo> Segura, NodoSRT *p);
    void Dibujar();
    int GetNumNodos();
    punto3d configuracion;
    vector<ParEscaneo> S; //Zona Local sergura
    vector<NodoSRT*> hijos;
    NodoSRT *padre;

    bool ContieneConfiguracion(punto3d qcand);
};

#endif // NODOSRT_H
