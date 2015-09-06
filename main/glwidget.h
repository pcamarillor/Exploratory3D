#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QTimer>
#include <carve/csg.hpp>
#include <carve/poly.hpp>
#include <carve/geom.hpp>
#include "manipulador.h"
#include "escena.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    Manipulador *robot;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *ev);
    int x, y;
    void ProbarCSG();
    void DibujarPoliedro(carve::poly::Polyhedron *p);
    string ExploracionHibrida(int iter2D, int iter3D,float alpha2D, float alpha3D, float dMin2D,
                       float dMin3D, int k2D, int k3D);
    string Exploracion3D_SRT(int KMax, int IMax, float alpha, float dmin);
    string Exploracion3D_SET(int KMax, int estrategia);
    string ExploracionMovil_Simple(int IMax, float alpha, float dmin);
    void MoverMovil();
    void Explorar();
    void iniciarAnimacion();
    void detenerAnimacion();
    void iniciarAnimacion3D();
    void detenerAnimacion3D();
    void VerRobot();
    void VerificarColision();
    void VerificarPuntoEnPoliedro(float x, float y, float z);
    void VerEscena();
    void TestConexion();
    void MaterialPlata();
    void MaterialAzul();
    Objeto3D escenaExplorada;
private slots:
    void Explorar2D();
    void Explorar3D();
    void CaminarMovil();
signals:
    void Mousse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();


private:
    vector<ParEscaneo> inter;
    bool pintarEscena;
    Escena escena;
    QTimer *temporizador;
    QTimer *temporizador2D;
    QTimer *temporizador3D;
    carve::poly::Polyhedron *is_poly;
    bool hay_escena;
    bool animacion_3D;
    float alpha, beta, xabc, yabc, rotx;
    int screen_width;
    int screen_height;
    float cam_x, cam_y, cam_z;
    float posX, posY, posZ;
    vector<Objeto3D> map;
    vector<Objeto3D> map_2;
    bool momentoExploracion3D;
    bool momentoExploracion2D;
    punto3d qact;
    punto3d qant;
    vector<punto3d> rutaMovil;
    QTimer *temporizadorMovil;
    int indexMovil;
    bool caminaMovil;
    float cob, numEscaneos;
};

#endif // GLWIDGET_H
