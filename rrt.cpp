#include "rrt.h"

RRT::RRT()
{
    this->raiz =  NULL;
    this->ultimoHijo = NULL;

}

void RRT::AgregarNodo(punto3d config)
{
    NodoRRT *nvo = new NodoRRT(config);
    if(this->raiz == NULL)
    {
        this->raiz = new NodoRRT(config);
        this->ultimoHijo = raiz;
    }
    else
    {
        ultimoHijo->AgregarHijo(nvo);
        ultimoHijo = nvo;
    }
}

void RRT::AgregarNodo(NodoRRT *nvo)
{
    if(this->raiz == NULL)
    {
        raiz = nvo;
        ultimoHijo = nvo;
    }
    else
    {
        ultimoHijo->AgregarHijo(nvo);
        ultimoHijo = nvo;
    }
}

NodoRRT* RRT::ESTADO_ALEATORIO(punto3d centro, punto3d fin)
{
    srand(time(NULL));
    punto3d punto;
    float xaleat;
    float yaleat;
    xaleat = centro.getX() > fin.getX() ? this->generarAleatorioDouble(fin.getX(),centro.getX()) :
                                          this->generarAleatorioDouble(centro.getX(),fin.getX());
    yaleat = centro.getY() > fin.getY() ? this->generarAleatorioDouble(fin.getY(),centro.getY()) :
                                          this->generarAleatorioDouble(centro.getY(),fin.getY());
    punto.setX(xaleat);
    punto.setY(yaleat);
    punto.setZ(centro.getZ());
//    cout << "qini:" << centro << endl;
//    cout << "qfin:" << fin << endl;
//    cout << "qnuevo:" << punto << endl;
//    system("PAUSE");
    return new NodoRRT(punto);
}

void RRT::Imprimir()
{
    this->raiz->Imprimir();
}

void RRT::Retornar_A_Padre()
{
    this->ultimoHijo = this->ultimoHijo->padre;
}

NodoRRT* RRT::VECINO_MAS_PROXIMO(NodoRRT* x)
{
    NodoRRT *xprox;
    xprox = this->raiz->HijoMasProximo(x);
    return xprox;
}

void RRT::Dibujar()
{
    this->raiz->Dibujar();
}

double RRT::generarAleatorioDouble(double fMin, double fMax)
{
//    cout << "fmin:" << fMin << endl;
//    cout << "fmax:" << fMax << endl;
    double f = (double)rand() / RAND_MAX;
//    cout << "resultado:" << fMin + f * (fMax - fMin) << endl;

     return fMin + f * (fMax - fMin);
}

