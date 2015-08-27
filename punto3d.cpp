#include "punto3d.h"

punto3d::punto3d(void)
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    xo = 0.0f;
    yo = 0.0f;
    zo = 0.0f;
}

punto3d::punto3d(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
    xo = _x;
    yo = _y;
    zo = _z;
}

punto3d::punto3d(float _angulo)
{
    this->angulo = _angulo;
}
punto3d::~punto3d(void)
{
}

void punto3d::setX(float _x)
{
    this->x = _x;
}

void punto3d::setY(float _y)
{
    this->y = _y;
}

void punto3d::setZ(float _z)
{
    this->z = _z;
 }

float punto3d::getX()
{
    return this->x;

}

float punto3d::getY()
{
    return this->y;
}

float punto3d::getZ()
{
    return this->z;
}

 void punto3d::TransformarPunto(carve::math::Matrix *transformaciones)
 {
    float tmpx, tmpy, tmpz;
    tmpx = transformaciones->_11*this->xo + transformaciones->_21*this->yo + transformaciones->_31*this->zo + transformaciones->_41;
    tmpy = transformaciones->_12*this->xo + transformaciones->_22*this->yo + transformaciones->_32*this->zo + transformaciones->_42;
    tmpz = transformaciones->_13*this->xo + transformaciones->_23*this->yo + transformaciones->_33*this->zo + transformaciones->_43;

    this->x = tmpx;
    this->y = tmpy;
    this->z = tmpz;
 }

 float punto3d::Distanica(punto3d *punto)
 {
     float d;
     float pot = 2.0f;
     d = sqrt(pow((punto->getX() - this->getX()),pot) +
              pow((punto->getY() - this->getY()),pot) +
              pow((punto->getZ() - this->getZ()),pot));
     return d;
 }

