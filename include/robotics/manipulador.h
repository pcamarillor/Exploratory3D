#ifndef MANIPULADOR_H
#define MANIPULADOR_H
#include "objeto3D.h"
#include "geneticoinversa.h"
#include "parescaneo.h"
#include "escena.h"
#include "srt.h"
#include "set.h"
#include "movil.h"
#include <iostream>
#include <io.h>
class Manipulador
{
public:
    Manipulador();
    ~Manipulador();
    void CinematicaDirecta();
    void CinematicaInversa(float x, float y, float z);
    void CinematicaInversa(punto3d configuracion);
    void Dibujar();
    void DibujarEfectorFinal();
    string Exploracion_Hibrida(Escena *escenario, int KGenMax, int Kmax, float alpha3D, float alpha2D,
                      float dmin3D, float dmin2D, float IMax2D, float IMax3D);
    string Exploracion_SRT(Escena *escenario, int KMax, int IMax, float alpha, float dmin);
    string Exploracion_SET(Escena *escenario, int KMAx, int estrategia);
    void TrasladarSensor(float xt, float yt, float zt);
    void ExploracionMovil(Escena *escenario, int Kmax, int IMax, float alpha, float dmin);
    void AnimarMovil();
    void AnimarManipulador();
    QList<punto3d> CrearLinea(punto3d qant, punto3d qpost, float angulo);
    float CalcularCobertura(Escena* escenario, vector<ParEscaneo>* map);
    float getD2();
    float getD6();
    float getA2();
    float getA3();
    float getD4();
    float getArt1();
    float getArt2();
    float getArt3();
    float getArt4();
    float getArt5();
    float getArt6();
    float getPosX();
    float getPosY();
    float getPosZ();
    void setArt1(float v);
    void setArt2(float v);
    void setArt3(float v);
    void setArt4(float v);
    void setArt5(float v);
    void setArt6(float v);
    void setPosX(float v);
    void setPosY(float v);
    void setPosZ(float v);

    Objeto3D primer;
    Objeto3D bounding_primer;
    Objeto3D segundo;
    Objeto3D bounding_segundo;
    Objeto3D tercer;
    Objeto3D bounding_tercer;
    Objeto3D cuarto;
    Objeto3D bounding_cuarto;
    Objeto3D cuarto_1;
    Objeto3D quinto;
    Objeto3D sexto;
    Objeto3D sensor;

    void MaterialOro();
    void MaterialRuby();
    void MaterialEsmeralda();
    vector<ParEscaneo> Escanear(Escena *escenario);
    void OcultarEfectorFinal();
    bool estaEnColision(Escena *escenario);
    bool autoColision();
    void TrasladarRobot(float _x, float _y, float _z);
    bool PuntoEnSensor(float x, float y, float z);
    vector<ParEscaneo> mapa;
    Objeto3D colision;
    bool sePintan;
    carve::math::Matrix m;
    float posX, posY, posZ;
    int indexNodoActual;
    movil *pionero;
signals:
    void Avanzar(int avance);

private:
    float art1;
    float art2;
    float art3;
    float art4;
    float art5;
    float art6;
    float ang_sensor;
    float d6;
    float d2;
    float a2;
    float a3;
    float d4;
    float alpha, beta;

    float tx,ty,tz; //Factores de traslacion general
    bool pintarSensor;

    SET *arbol_exploracion;
    SRT *arbol_srt;

    void DibujarArticulacion(Objeto3D object);
    float Gr2Rad(float grados);

    //Provisional
    Linea r;
    bool hayLinea;
};

#endif // MANIPULADOR_H
