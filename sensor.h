#ifndef SENSOR_H
#define SENSOR_H

#include "objeto3ds.h"
#include "punto3d.h"
#include "poligono.h"
#include "manipulador.h"
#include <carve/csg.hpp>
#include <carve/poly.hpp>
#include <carve/geom.hpp>

class Sensor
{
public:
    Sensor(void);
    Sensor(char *pathfile);
    ~Sensor();
    std::vector<carve::poly::Face<3> > Sensar();
    void Dibujar();
    static std::vector<carve::poly::Face<3> > Objtedo3ds_2_Polyhedron(Objeto3ds *objeto3ds)
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
        for (l_index = 0;l_index < objeto3ds->getNumPoligonos();l_index++)
        {
            x = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getA() ].getX();
            y = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getA() ].getY();
            z = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getA() ].getZ();
            tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(x,y,z)));

            x = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getB() ].getX();
            y = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getB() ].getY();
            z = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getB() ].getZ();
            tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(x,y,z)));

            x = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getC() ].getX();
            y = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getC() ].getY();
            z = objeto3ds->vertices[ objeto3ds->poligonos[l_index].getC() ].getZ();
            tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(x,y,z)));

            corners.clear();
            corners.push_back(&tet_verts[0]);
            corners.push_back(&tet_verts[2]);
            corners.push_back(&tet_verts[1]);
            tet_faces.push_back(face_t(corners));
        }
       // carve::poly::Polyhedron p();
        return tet_faces;
    }
   // carve::poly::Polyhedron modeloSensorial;
private:
    Objeto3ds modelo3ds;
    std::vector<carve::poly::Face<3> > caras;//Caras del modelo sensorial
};

#endif // SENSOR_H
