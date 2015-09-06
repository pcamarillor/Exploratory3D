#include "sensor.h"

Sensor::Sensor(void)
{
    modelo3ds = Manipulador::Load3DS("C:/Users/Pablo/Documents/QTDemos/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/debug/sensor.3ds");
    caras = Sensor::Objtedo3ds_2_Polyhedron(&modelo3ds);
    carve::poly::Polyhedron modeloSensorial(caras);
}
Sensor::Sensor(char *pathfile)
{


}


std::vector<carve::poly::Face<3> > Sensor::Sensar()
{
    return caras;
}

Sensor::~Sensor()
{

}

void Sensor::Dibujar()
{
   modelo3ds.Dibujar();
}
