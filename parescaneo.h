#ifndef PARESCANEO_H
#define PARESCANEO_H
#include <vector>
#include <iostream>
#include "objeto3D.h"

using namespace std;
class ParEscaneo
{
public:
    ParEscaneo();
    Objeto3D obstaculos;
    Objeto3D fronteraLibre;
    punto3d configuracion;
    //Articulaciones del robot en esos puntos
    float art1;
    float art2;
    float art3;
    //Para el movil
    float x, y, theta;
};

#endif // PARESCANEO_H
