#ifndef OBJETO3D_H
#define OBJETO3D_H
#include <vector>
#include <carve/csg.hpp>
#include <carve/poly.hpp>
#include <carve/geom.hpp>
#include "punto3d.h"
#include "poligono.h"

typedef carve::poly::Vertex<3> vertex_t;

class Objeto3D
{
public:
    Objeto3D(void);
    ~Objeto3D(void);
    void agregarVertice(float _x, float _y, float _z);
    void agregarPoligono(unsigned short _a, unsigned short _b, unsigned short _c);
    void agregarPoligono(std::vector<int> esquinas);
    void setNumPoligonos(int n);
    void setNumVertices(int n);
    int getNumPoligonos();
    int getNumVertices();
    void Trasladar(float xt, float yt, float zt);
    void Trasladar_Relativa(float xt, float yt, float zt);
    void Dibujar();
    void DibujarAC();
    void DibujarPoliedro(carve::poly::Polyhedron *p);
    bool ContienePunto(float x, float y, float z);
    bool ContienePunto(punto3d qcand);
    void GenerarConfiguracionesCandidatas();
    punto3d ObtenerCentroide();
    float CalcularVolumen();
    punto3d PuntoMedio(punto3d pto1, punto3d pto2);
    float Distancia(punto3d pto1, punto3d pto2);
    float ProductoPunto(punto3d vector1, punto3d vector2);
    void PintarPuntos();
    std::vector<punto3d> Bresenham3D(int x1, int y1, int z1, const int x2, const int y2, const int z2);
    std::vector<punto3d> vertices;
    std::vector<Poligono> poligonos;
    std::vector<carve::poly::Face<3> > caras_poliedro;
    std::vector<punto3d> configuracionesCandidatas;
    static float* CalcularNormal(float *p1, float *p2, float *p3)
    {
        float vectorFinal[3];
        float vectorU[3];
        float vectorV[3];

        vectorU[0] = *(p2 + 0) - *(p1 + 0);
        vectorU[1] = *(p2 + 1) - *(p1 + 1);
        vectorU[2] = *(p2 + 2) - *(p1 + 2);

        vectorV[0] = *(p3 + 0) - *(p1 + 0);
        vectorV[1] = *(p3 + 1) - *(p1 + 1);
        vectorV[2] = *(p3 + 2) - *(p1 + 2);

        vectorFinal[0] = vectorU[1]*vectorV[2] - vectorU[2]*vectorV[1];
        vectorFinal[1] = vectorU[2]*vectorV[0] - vectorU[0]*vectorV[2];
        vectorFinal[2] = vectorU[0]*vectorV[1] - vectorU[1]*vectorV[0];

        return vectorFinal;
    }
    void Load3DS (char *p_filename);
    void LoadAC3D(char *p_filename);
    Objeto3D CalcularOperacionBooleana(Objeto3D *B, int idOp);
    int BuscarVertice(vertex_t* ptr, carve::poly::Polyhedron *poli);
    float getOffX();
    float getOffY();
    float getOffZ();
    void setOffX(float _x);
    void setOffY(float _y);
    void setOffZ(float _z);
    void RotarX(float rx);
    void RotarY(float ry);
    void RotarZ(float rz);
    void Rotar(float theta, int gradoLibertad);
    void TransformarPuntos(carve::math::Matrix* matriz);
    void TransformarPuntos();
    friend std::ostream& operator<<(std::ostream& os, Objeto3D& objto)
    {
        os << "num vertices:" << objto.vertices.size() << " num poligonos:" << objto.poligonos.size() << std::endl;
        return os;
    }
    void setTheta(float t);
    carve::math::Matrix transformaciones;
    void ImprimirMatriz();
private:
    void toPoliedro();
    bool pintarPuntos;
    int numPoligonos;
    int numVertices;
    float offSetX, offSetY, offSetZ;
    float theta_ant;
    std::vector<float> angulosRotacion;
    std::vector<int> ordenRotacion;//0: rotacion X, 1: rotacion Y, 2: rotacion Z


};

#endif // OBJETO3D_H
