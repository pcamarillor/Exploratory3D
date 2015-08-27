#ifndef MANIPULADOR_H
#define MANIPULADOR_H
#include "objeto3D.h"
#include "modelosensorial.h"
#include "geneticoinversa.h"
#include "parescaneo.h"
#include "escena.h"
#include "set.h"
#include <iostream>
#include <io.h>
class Manipulador
{
public:
    Manipulador();
    ~Manipulador();
    void CinematicaDirecta(int _art);
    void CinematicaInversa(float x, float y, float z);
    void Dibujar();
    void DibujarEfectorFinal();
    vector<vector<Objeto3D>> Explorar_SET(Escena *escenario);

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
 //   Objeto3D Escanear(Objeto3D *escenario);
    ParEscaneo Escanear(Escena *escenario);
    void OcultarEfectorFinal();
    bool estaEnColision(Escena *escenario);
    bool estaEnAutoColision();
    Objeto3D colision;
    bool sePintan;
    carve::math::Matrix m;
private:
    float art1;
    float art2;
    float art3;
    float art4;
    float art5;
    float art6;
    float d6;
    float d2;
    float a2;
    float a3;
    float d4;
    float alpha, beta;
    float posX, posY, posZ;
    float ax, ay, az;
    bool pintarSensor;
    void DibujarArticulacion(Objeto3D object);
    float Gr2Rad(float grados);
};

#endif // MANIPULADOR_H
