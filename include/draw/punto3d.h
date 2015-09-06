#ifndef PUNTO3D_H
#define PUNTO3D_H

#include <iostream>
#include <carve/csg.hpp>
#include <carve/poly.hpp>
#include <carve/geom.hpp>
class punto3d
{
public:
    punto3d();
    punto3d(float _x, float _y, float _z);
    punto3d(float _angulo);
    ~punto3d(void);
    void setX(float _x);

    void setY(float _y);

    void setZ(float _z);

    float getX();

    float getY();

    float getZ();

    friend std::ostream& operator<<(std::ostream& os, punto3d& pto)
    {
        os << "x:" << pto.getX() << " y:" << pto.getY() << " z:" << pto.getZ() << std::endl;
        return os;
    }
    float xo, yo, zo;
    void TransformarPunto(carve::math::Matrix *transformaciones);
    float Distanica(punto3d *punto);
    float angulo;
private:
    float x,y,z;
};

#endif // PUNTO3D_H
