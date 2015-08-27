#include "modelosensorial.h"
#include "manipulador.h"

ModeloSensorial::ModeloSensorial(char *path)
{
    modelo3ds.Load3DS(path);
    faces_modelo = ModeloSensorial::Objtedo3ds_2_Polyhedron(&modelo3ds);
}

ModeloSensorial::~ModeloSensorial(void)
{

}
carve::poly::Polyhedron * ModeloSensorial::Sensar(Objeto3D *escenario)
{
    std::vector<carve::poly::Face<3> > face_escenario;
    face_escenario = ModeloSensorial::Objtedo3ds_2_Polyhedron(escenario);
    carve::poly::Polyhedron cono(faces_modelo);
    carve::poly::Polyhedron escena(face_escenario);

    std::cout << "Cono " << cono << std::endl;
    std::cout << "Escena " << escena << std::endl;

    carve::poly::Polyhedron * is_poly = carve::csg::CSG().compute(&cono,&escena,
                                                                  carve::csg::CSG::INTERSECTION);

    std::cout << "Interseccion " << *is_poly << std::endl;
    return is_poly;
}

void ModeloSensorial::Dibujar()
{
    modelo3ds.Dibujar();
}
