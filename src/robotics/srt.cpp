#include "srt.h"

SRT::SRT()
{
    this->raiz = NULL;
    this->ultimoHijo = NULL;
}

void SRT::AgregarConfiguracion(punto3d qact, vector<ParEscaneo> S)
{
    NodoSRT *hoja;
    if(raiz == NULL)
    {
        hoja = new NodoSRT(qact, S, NULL);
        raiz = hoja;
        this->ultimoHijo = raiz;
    }
    else
    {
        hoja = new NodoSRT(qact, S, this->ultimoHijo);
        this->ultimoHijo->hijos.push_back(hoja);
        this->ultimoHijo = hoja;

    }
}

bool SRT::VALIDA(punto3d qact,punto3d qcand, float dmin, vector<ParEscaneo> S, vector<vector<ParEscaneo>> otras)
{
    //Debe estar en S, pero no en otras
    //más lejos que dmin de la configuración actual, y no debe estar en ninguna region
    //local segura previa.
    bool esValida = true;
    //Primero, se verifica que no este en ninguna region local previa


    for(int i = 0; i < otras.size();i++)
    {
        for(int j = 0; j < otras.at(i).size();j++)
        {
            esValida = !otras.at(i).at(j).fronteraLibre.ContienePunto(qcand);
            if(!esValida)
            {
                break;
            }
        }
    }

    //Después, se verifica que la contenga la region local acutal S
    for(int i = 0; i < S.size();i++)
    {
        esValida = S.at(i).fronteraLibre.ContienePunto(qcand);
        if(!esValida)
        {
            break;
        }
    }
    //Ahora se verifica la distancia
    if(esValida)
    {
        esValida = qcand.Distanica(&qact) > dmin;
    }
    return esValida;
}



Linea SRT::RADIO(vector<ParEscaneo> S, float tRandZ, float tRandX)
{
    //Se selecciona la region local segura mas grande
    float vMin = 10000.0f, vAct = 0;
    int indexMin;

    for(int i = 0; i < S.size();i++)
    {
        vAct = S.at(i).fronteraLibre.CalcularVolumen();
        if(vAct < vMin)
        {
            vMin = vAct;
            indexMin = i;
        }
    }

    //Se obtiene el centroide de la region local máxima
    punto3d centroide = S.at(indexMin).fronteraLibre.ObtenerCentroide();
    punto3d qcand, vectorDireccion;

    Linea *radio;
    float xp, yp, zp;
    float xt, yt;
    xp = centroide.getX() + 1;
    yp = centroide.getY();
    zp = centroide.getZ();

    //Se encuentra el radio rotado al rededor del eje Z
    xt = centroide.getX() + (xp - centroide.getX())*cos(tRandZ) - (yp - centroide.getY())*sin(tRandZ);
    yt = centroide.getY() + (xp - centroide.getY())*sin(tRandZ) + (yp - centroide.getY())*cos(tRandZ);

    //Finalmente, se encuentra el radio final, rotando el radio rotado en Z, ahora rotado en X
    qcand.setX(xt);
    qcand.setY(centroide.getY() + (yt - centroide.getY())*cos(tRandX) - (zp - centroide.getZ())*sin(tRandX));
    qcand.setZ(centroide.getZ() + (yt - centroide.getY())*sin(tRandX) + (zp - centroide.getZ())*cos(tRandX));

    vectorDireccion.setX(qcand.getX() - centroide.getX());
    vectorDireccion.setY(qcand.getY() - centroide.getY());
    vectorDireccion.setZ(qcand.getZ() - centroide.getZ());

    radio = new Linea(centroide,vectorDireccion);
    return *radio;
}

Linea SRT::RADIO2D(vector<ParEscaneo> S, float tRandX, float X, float Y)
{
    //Se obtiene el centroide de la region local máxima
    punto3d centroide;
    centroide.setX(X);
    centroide.setY(Y);
    centroide.setZ(2.93783);
    punto3d qcand, vectorDireccion;

    Linea *radio;
    float xp, yp, zp;
    float xt, yt;
    xp = centroide.getX() + 1;
    yp = centroide.getY() + 1;
    zp = centroide.getZ() + 1;

    //Se encuentra el radio rotado al rededor del eje Z
    xt = centroide.getX() + (xp - centroide.getX())*cos(tRandX) - (yp - centroide.getY())*sin(tRandX);
    yt = centroide.getY() + (xp - centroide.getY())*sin(tRandX) + (yp - centroide.getY())*cos(tRandX);

    //Finalmente, se encuentra el radio final, rotando el radio rotado en Z, ahora rotado en X
    qcand.setX(xt);
    qcand.setY(yt);
    qcand.setZ(zp);

    vectorDireccion.setX(qcand.getX() - centroide.getX());
    vectorDireccion.setY(qcand.getY() - centroide.getY());
    vectorDireccion.setZ(qcand.getZ() - centroide.getZ());

    radio = new Linea(centroide,vectorDireccion);
    return *radio;
}

punto3d SRT::DESPLAZAR(Linea *r, float alpha_r)
{
    punto3d qcand;
    qcand.setX(r->punto.getX() + alpha_r*r->vectorDireccion.getX());
    qcand.setY(r->punto.getY() + alpha_r*r->vectorDireccion.getY());
    qcand.setZ(r->punto.getZ() + alpha_r*r->vectorDireccion.getZ());
    return qcand;
}

punto3d SRT::DESPLAZAR2D(Linea *r, float alpha_r)
{
    punto3d qcand;
    qcand.setX(r->punto.getX() + alpha_r*r->vectorDireccion.getX());
    qcand.setY(r->punto.getY() + alpha_r*r->vectorDireccion.getY());
    qcand.setZ(2.9);
    return qcand;
}
void SRT::Dibujar()
{
    this->raiz->Dibujar();
}

int SRT::GetNumeroNodos()
{
    return this->raiz->GetNumNodos();
}
