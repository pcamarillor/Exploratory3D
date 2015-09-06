#ifndef RRT_H
#define RRT_H
#include "nodorrt.h"
#include <vector>
#include <iostream>
#define ALCANZADO 0
#define AVANZADO 1
#define ATRAPADO 2
using namespace std;
class RRT
{
public:
    RRT();
    NodoRRT *ultimoHijo;
    NodoRRT *ESTADO_ALEATORIO(punto3d centro, punto3d fin);
    int EXTENDER(NodoRRT *x);
    NodoRRT* VECINO_MAS_PROXIMO(NodoRRT* x);
    void AgregarNodo(punto3d config);
    void AgregarNodo(NodoRRT *nvo);
    void Retornar_A_Padre();
    void Dibujar();
    void Imprimir();
    double generarAleatorioDouble(double fMin, double fMax);
    NodoRRT *raiz;
private:



};

#endif // RRT_H
