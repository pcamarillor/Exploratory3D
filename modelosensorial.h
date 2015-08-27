#ifndef MODELOSENSORIAL_H
#define MODELOSENSORIAL_H

#include "objeto3D.h"
#include <carve/csg.hpp>
#include <carve/poly.hpp>
#include <carve/geom.hpp>
#include <iostream>

class ModeloSensorial
{
public:
    ModeloSensorial(char *path);
    ~ModeloSensorial(void);
    carve::poly::Polyhedron * Sensar(Objeto3D *escenario);
    void Dibujar();
    static std::vector<carve::poly::Face<3> > Objtedo3ds_2_Polyhedron(Objeto3D *Objeto3D)
    {
        typedef carve::poly::Vertex<3> vertex_t;
        typedef carve::poly::Edge<3> edge_t;
        typedef carve::poly::Face<3> face_t;
        typedef carve::geom::vector<3> vec_t;
        std::vector<carve::poly::Vertex<3> > tet_verts;
        std::vector<carve::poly::Face<3> > tet_faces;
        std::vector<const vertex_t *> corners;

        int l_index;
        float x,y, z;
        for(int i = 0; i < Objeto3D->getNumVertices();i++)
        {
            x = Objeto3D->vertices[i].getX();
            y = Objeto3D->vertices[i].getY();
            z = Objeto3D->vertices[i].getZ();
            std::cout << "x:" << x << " y:" << y << " z:" << z << std::endl;
            tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(x,y,z)));
        }

        for (l_index = 0;l_index < Objeto3D->getNumPoligonos();l_index++)
        {
            corners.clear();
            corners.push_back(&tet_verts[Objeto3D->poligonos[l_index].getA()]);
            corners.push_back(&tet_verts[Objeto3D->poligonos[l_index].getB()]);
            corners.push_back(&tet_verts[Objeto3D->poligonos[l_index].getC()]);
            std::cout << "a:" << Objeto3D->poligonos[l_index].getA() << " b:" << Objeto3D->poligonos[l_index].getB() << " c:" << Objeto3D->poligonos[l_index].getC() << std::endl;
            tet_faces.push_back(face_t(corners));
        }
        // carve::poly::Polyhedron p();
        return tet_faces;
    }
private:
    Objeto3D modelo3ds;
    std::vector<carve::poly::Face<3> > faces_modelo;

};

#endif // MODELOSENSORIAL_H
