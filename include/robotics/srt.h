#ifndef SRT_H
#define SRT_H
#include "escena.h"
#include "nodosrt.h"
#include "linea.h"
#include <qgl.h>

class SRT
{
public:
    SRT();
    NodoSRT *raiz;
    NodoSRT *ultimoHijo;
    void AgregarConfiguracion(punto3d qact, vector<ParEscaneo> S);
    bool VALIDA(punto3d qact, punto3d qcand, float dmin, vector<ParEscaneo> S,vector<vector<ParEscaneo>> otras);
    Linea RADIO(vector<ParEscaneo> S, float tRandZ, float tRandX);
    Linea RADIO2D(vector<ParEscaneo> S, float tRandX, float X, float Y);
    punto3d DESPLAZAR(Linea *r, float alpha_r);
    punto3d DESPLAZAR2D(Linea *r, float alpha_r);
    int GetNumeroNodos();
    void Dibujar();
};

#endif // SRT_H
