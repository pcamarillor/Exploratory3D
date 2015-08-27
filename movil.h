#ifndef MOVIL_H
#define MOVIL_H
#include "objeto3D.h"
#include "parescaneo.h"
#include "escena.h"
#include "linea.h"
#include "srt.h"
#include "rrt.h"
#include "grafo.h"
#include "vertice.h"
#include <qgl.h>
#include <vector>
#include <io.h>
#include <carve/csg.hpp>
#include <carve/poly.hpp>
#include <carve/geom.hpp>
#include <stdlib.h>

using namespace std;
class movil
{
public:
    movil();
    movil(Escena *esc);
    punto3d ExplorarSRT(Escena *escenario, punto3d qact, int IMax, float alpha, float dmin);
    void Dibujar();
    void Mover(punto3d qcand);
    void Rotar(float angulo);
    //Métodos y propiedades para RRT ============================================
    RRT* CONSTRUIR_RRT(punto3d qini, punto3d qfin,int K);
    vector<punto3d> ConstruirRuta(RRT *miRRT, punto3d inicio, punto3d fin);
    NodoRRT* NUEVO_ESTADO(NodoRRT *x, NodoRRT *xprox);
    //============================================================================

    //Método para PRM ============================================================
    Grafo* AprendizajePRM(int numNodos, int kVecinos, float distancia);
    vector<punto3d> puntosRuta; //Puntos de la conexion entre dos configuraciones
    Grafo* roadMap;
    punto3d GenerarNodoAleatorio();
    void Conectar(punto3d qini, punto3d qfin);
    void EncontrarKVecinos(Grafo *miGrafo, int actual, int kVecinos, float distanciaTolerada);
    bool MetodoLocal(vertice *origen, vertice *destino);
    //============================================================================

    int EXTENDER_RRT(RRT* miRRT, NodoRRT *x);
    bool Brensenham(punto3d pto1, punto3d pto2);
    bool estaEnColision(Escena *esc);
    vector<ParEscaneo> Sensar(Escena* esc);
    vector<punto3d> ruta;
    vector<punto3d> camino;
    float x,y,theta;
    int indexNodoActual;
    double generarAleatorioDouble(double fMin, double fMax);
    Objeto3D inter;
    Escena *escenario;
private:
    Objeto3D llantaD;
    Objeto3D rinD;
    Objeto3D llantaI;
    Objeto3D rinI;
    Objeto3D body;
    Objeto3D llantaFr;
    Objeto3D tapa;
    Objeto3D sensores;
    Objeto3D sensor;
    Objeto3D bounding;
    SRT *arbol_srt;

    bool hayArbol;
    void MaterialEsmeralda();
    void MaterialRuby();
    void MaterialOro();
    void MaterialLLanta();
    void MaterialPlasticoRojo();

};

#endif // MOVIL_H
