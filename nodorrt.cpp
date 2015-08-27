#include "nodorrt.h"

NodoRRT::NodoRRT()
{
    punto3d pto(0,0,0);
    this->configuracion = pto;
    this->padre = NULL;
}

NodoRRT::NodoRRT(punto3d dato)
{
   this->configuracion = dato;
   this->padre = NULL;
}

void NodoRRT::AgregarHijo(NodoRRT *hijo)
{
    hijo->padre = this;
    this->hijos.push_back(hijo);
}

NodoRRT* NodoRRT::HijoMasProximo(NodoRRT *x)
{
    float dmin = 100000.0f;
    float d;
    NodoRRT *tmp, *prox;
    if(this->hijos.size() > 0)
    {
        for(int i = 0; i < this->hijos.size();i++)
        {
            prox = this->hijos.at(i)->HijoMasProximo(x);
            d = prox->configuracion.Distanica(&x->configuracion);
            if(d < dmin)
            {
                dmin = d;
                tmp = prox;
            }
        }
    }
    else
    {
        return this;
    }

    return tmp;
}

void NodoRRT::Dibujar()
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

void NodoRRT::Imprimir()
{
    cout << "padre:" << this->configuracion << endl;
    for(int i = 0; i < this->hijos.size();i++)
        cout << "   " << this->hijos.at(i)->configuracion;

    for(int i = 0; i < this->hijos.size();i++)
        this->hijos.at(i)->Imprimir();
}

