#include "nodoset.h"

NodoSET::NodoSET(NodoSET *p)
{
    this->padre = p;
    this->Utility = 0.0f;
}

NodoSET::NodoSET(ParEscaneo _q, NodoSET *p, float _u)
{
    this->q = _q;
    this->padre = p;
    this->Utility = _u;
}

void NodoSET::AgregarHijo(NodoSET *hijo)
{
    this->hijos.push_back(hijo);
}

punto3d NodoSET::GetPunto()
{
    return this->q.configuracion;
}

void NodoSET::SetUtility(float _u)
{
    this->Utility = _u;
}

int NodoSET::GetNumNodos()
{
    int suma = 0;
    for(int i = 0; i < this->hijos.size();i++)
        suma += this->hijos.at(i)->GetNumNodos();
    return suma;
}

NodoSET::~NodoSET()
{}


