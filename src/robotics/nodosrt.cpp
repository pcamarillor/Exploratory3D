#include "nodosrt.h"

NodoSRT::NodoSRT(NodoSRT *p)
{
    this->padre = p;
}


NodoSRT::NodoSRT(punto3d qact, vector<ParEscaneo> Segura, NodoSRT *p)
{
    this->configuracion = qact;
    this->S = Segura;
    this->padre = p;
}

bool NodoSRT::ContieneConfiguracion(punto3d qcand)
{
    bool siContiene = false;
    int i = 0, j = 0;
    do
    {
        siContiene = S.at(i).fronteraLibre.ContienePunto(qcand);
        i++;
    }while(siContiene || i == S.size() - 1);

    do
    {
        siContiene = this->hijos.at(j)->ContieneConfiguracion(qcand);
        j++;
    }while(siContiene || j == this->hijos.size() - 1);

    return siContiene;
}

void NodoSRT::Dibujar()
{
    for(int i = 0; i < this->hijos.size(); i++)
    {
        glBegin(GL_POINTS);
        glVertex3f(this->hijos.at(i)->configuracion.getX(),this->hijos.at(i)->configuracion.getY(),this->hijos.at(i)->configuracion.getZ());
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(this->configuracion.getX(), this->configuracion.getY(), this->configuracion.getZ());
        glVertex3f(this->hijos.at(i)->configuracion.getX(),this->hijos.at(i)->configuracion.getY(),this->hijos.at(i)->configuracion.getZ());
        glEnd();
        this->hijos.at(i)->Dibujar();
    }
}

int NodoSRT::GetNumNodos()
{
    int suma = 0;
    if(this->hijos.size() == 0)
    {
        return 0;
    }
    else
    {
        suma += this->hijos.size();
        for(int i = 0; i < this->hijos.size();i++)
            suma += this->hijos.at(i)->GetNumNodos();

        return suma;
    }
}
