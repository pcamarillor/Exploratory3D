#include "manipulador.h"
#include <iostream>
#include <vector>
#include <io.h>
#include <math.h>
#include <qgl.h>
#include <GL/GLU.h>

using namespace std;
Manipulador::Manipulador(void)
{
    alpha = 0.0f;
    beta = 0.0f;

    art1 = 0.0f;
    art2 = 0.0f;
    art3 = 0.0f;
    art4 = 0.0f;
    art5 = 0.0f;
    art6 = 0.0f;

    d6 = 1.0f;
    d2 = 1.8f;
    a2 = 3.0f;
    a3 = 0.0f;
    d4 = 3.3f;

    posX = 0;
    posY = 5;
    posZ = 0;

    primer.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/primer.ac");
    bounding_primer.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/b_primer.ac");
    segundo.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/segundo.ac");
    bounding_segundo.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/b_segundo.ac");
    tercer.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/tercer.ac");
    bounding_tercer.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/b_tercer.ac");
    cuarto.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/cuarto.ac");
    bounding_cuarto.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/b_cuarto.ac");
    cuarto_1.Load3DS("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/cuarto_1.3ds");
    quinto.Load3DS("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/quinto.3ds");
    sexto.Load3DS("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/sexto.3ds");
    sensor.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/sensor.ac");
    this->CinematicaDirecta();
    sensor.Trasladar(posX, posY, posZ);
    pintarSensor = true;
    sePintan = false;
}


Manipulador::~Manipulador(void)
{
    //delete sensor;
}

float Rad2Grad(float x)
{
    return (180*x)/3.1416;
}



//Método que calcula los ángulos de rotación de cada articulación del movil
//a partir de una posición del efector final deseada
void Manipulador::CinematicaInversa(float px, float py, float pz)
{
    //Theta 1
    float cmpY = py*sqrt(pow(px,2)+pow(py,2)-pow(d2,2)) - px*d2;
    float cmpX = px*sqrt(pow(px,2)+pow(py,2)-pow(d2,2)) - py*d2;
    if((abs(px) > 0 && abs(px) < 1) ||(abs(py) > 0 && abs(py) < 1 ))
        art1 = 0.0f;
    else
        art1 = atan2(cmpY, cmpX);

    //Theta 2
    float R,r;

    R = sqrt(pow(px,2) + pow(py,2) + pow(pz,2) - pow(d2,2));

    r = sqrt(pow(pz,2) + pow(py,2) - pow(d2,2));

    float sinAlpha, cosAlpha;
    float sinBeta, cosBeta;

    sinAlpha = -pz/R;
    cosAlpha = r/R;

    cosBeta = (pow(a2,2) + pow(R,2) - (pow(d4,2) + pow(a3,2)))/(2*a2*R);
    if((1 - pow(cosBeta,2)) < 0)
        sinBeta = 0.0f;
    else
        sinBeta = sqrt(1 - pow(cosBeta,2));



    float cosTeta2,sinTeta2;

    sinTeta2 = sinAlpha*cosBeta + cosAlpha*sinBeta;
    cosTeta2 = cosAlpha*cosBeta - sinAlpha*sinBeta;

    art2 = atan2(sinTeta2,cosTeta2);

    //Theta 3
    float cosPhi, sinPhi;

    cosPhi = (pow(a2,2) + (pow(d4,2) + pow(a3,2)) - pow(R,2))/(2*a2*sqrt(pow(d4,2) + pow(a3,2)));
    if((1 - pow(cosPhi,2)) < 0)
        sinPhi = 0.0f;
    else
        sinPhi = sqrt(1 - pow(cosPhi,2));

    sinBeta = d4/(sqrt(pow(d4,2) + pow(a3,2)));
    cosBeta = abs(a3) /(sqrt(pow(d4,2) + pow(a3,2)));

    float sinTeta3, cosTeta3;

    sinTeta3 = sinPhi*cosPhi - cosPhi*sinBeta;
    cosTeta3 = cosPhi*cosBeta + sinPhi*sinBeta;

    art3 = atan2(sinTeta3,cosTeta3);

    art1 = Rad2Grad(art1);
    art2 = Rad2Grad(art2);
    art3 = Rad2Grad(art3);

    this->posX = px;
    this->posY = py;
    this->posZ = pz;
}

//Método que calcula la posición del efetor final a partir de los valores de
//los ángulos de cada articulación del manipulador
void Manipulador::CinematicaDirecta()
{
    float t1 = Gr2Rad(this->getArt1());
    float t2 = Gr2Rad(this->getArt2());
    float t3 = Gr2Rad(this->getArt3());
    float t4 = Gr2Rad(this->getArt4());
    float t5 = Gr2Rad(this->getArt5());
    float t6 = Gr2Rad(this->getArt6());

    bounding_segundo.Rotar(t1,2);
    bounding_tercer.Rotar(t1,2);
    bounding_cuarto.Rotar(t1,2);


    bounding_tercer.Trasladar(-2.64512,-5.88704,-2.136782);
    bounding_tercer.Rotar(t2,1);
    bounding_tercer.Trasladar_Relativa(0,0,0);

    posX = cos(t1)*(this->getD6()*(cos(t2 + t3)*cos(t4)*sin(t5) + sin(t2 + t3)*cos(t5)) + sin(t2 + t3)*this->getD4() + this->getA3()*cos(t2+t3) + this->getA2()*cos(t2)) - (sin(t1)*(this->getD6()*sin(t4)*sin(t5) + this->getD2()));
    posY = sin(t1)*(this->getD6()*(cos(t2 + t3)*cos(t4)*sin(t5) + sin(t2 + t3)*cos(t5)) + sin(t2 + t3)*this->getD4() + this->getA3()*cos(t2+t3) + this->getA2()*cos(t2)) + (cos(t1)*(this->getD6()*sin(t4)*sin(t5) + this->getD2()));
    posZ = this->getD6()*(cos(t2 + t3)*cos(t5) - sin(t2 + t3)*cos(t4)*sin(t5)) + cos(t2 + t3)*this->getD4() - this->getA3()*sin(t2 + t3) - this->getA2()*sin(t2);
}

float Manipulador::getPosX()
{
    return this->posX;
}

float Manipulador::getPosY()
{
    return this->posY;
}

float Manipulador::getPosZ()
{
    return this->posZ;
}

float Manipulador::getD2()
{
    return this->d2;
}

float Manipulador::getD6()
{
    return this->d6;
}

float Manipulador::getA2()
{
    return this->a2;
}

float Manipulador::getA3()
{
    return this->a3;
}

float Manipulador::getD4()
{
    return this->d4;
}

float Manipulador::getArt1()
{
    return art1;
}

float Manipulador::getArt2()
{
    return art2;
}

float Manipulador::getArt3()
{
    return art3;
}

float Manipulador::getArt4()
{
    return art4;
}

float Manipulador::getArt5()
{
    return art5;
}

float Manipulador::getArt6()
{
    return art6;
}

void Manipulador::setArt1(float v)
{
    this->art1 = v;
    this->CinematicaDirecta();
}

void Manipulador::setArt2(float v)
{
    this->art2 = v;
    this->CinematicaDirecta();
}

void Manipulador::setArt3(float v)
{
     this->art3 = v;
     this->CinematicaDirecta();
}

void Manipulador::setArt4(float v)
{
     this->art4 = v;
     this->CinematicaDirecta();
}

void Manipulador::setArt5(float v)
{
     this->art5 = v;
     this->CinematicaDirecta();
}

void Manipulador::setArt6(float v)
{
     this->art6 = v;
     this->CinematicaDirecta();
}

void  Manipulador::setPosX(float v)
{
    this->posX = v;
}


void  Manipulador::setPosY(float v)
{
    this->posY = v;
}

void  Manipulador::setPosZ(float v)
{
    this->posZ = v;
}

void Manipulador::MaterialEsmeralda()
   {
    GLfloat mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
    GLfloat mat_diffuse[] =  {0.07568f, 0.61424f, 0.07568f, 0.55f };
    GLfloat mat_specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
    GLfloat shineness = 76.8f;


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shineness);

    glColor3f(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]); //Material esmeralda
  }

void Manipulador::MaterialRuby()
{
    GLfloat mat_ambient[] = { 0.1745f, 0.01175f, 0.01175f};
    GLfloat mat_diffuse[] =  {0.61424f, 0.04136f, 0.04136f};
    GLfloat mat_specular[] = { 0.727811f, 0.626959f, 0.626959f };
    GLfloat shineness = 0.6f;


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shineness);

    glColor3f(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]); //Material esmeralda
}

void Manipulador::MaterialOro()
{
    GLfloat mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f};
    GLfloat mat_diffuse[] =  {0.75164f, 0.60648f, 0.22648f};
    GLfloat mat_specular[] = { 0.628281f, 0.555802f, 0.366065f };
    GLfloat shineness = 0.4f;


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shineness);

    glColor3f(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]); //Material esmeralda
}

float Manipulador::Gr2Rad(float grados)
{
    return (3.1416*grados)/180;
}

void solidCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks) {

    GLUquadricObj* qobj = gluNewQuadric();

    gluCylinder(qobj, radius, radius, height, slices, stacks);
    glScalef(-1.0, 1.0, -1.0);
    gluDisk(qobj, 0.0, radius, slices, stacks);
    glScalef(-1.0, 1.0, -1.0);
    glTranslatef(0.0, 0.0, height);
    gluDisk(qobj, 0.0, radius, slices, stacks);

    gluDeleteQuadric(qobj);
}

void Manipulador::Dibujar()
{
    glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
    glRotatef(180.0f,0.0f, 0.0f, 1.0f);

    //MaterialRuby();


    glPushMatrix();
        this->primer.DibujarAC();
    glPopMatrix();
    glTranslatef(0.0f, 0.0f, 5.8f);

    glPushMatrix();
        glRotatef(-90.0f,0.0f,0.0f,1.0f);
        glRotatef(this->getArt1(),0.0f,0.0f,1.0f);
        MaterialEsmeralda();

        glPushMatrix();
            this->segundo.DibujarAC();
        glPopMatrix();

        glRotatef(-90.0f,0.0f,1.0f,0.0f);
        glRotatef(90.0f,0.0f,0.0f,1.0f);
        glRotatef(this->getArt2(),0.0f, 0.0f, 1.0f);

        MaterialRuby();
        glTranslatef(0.0f,0.0f, 2.5f);
        glPushMatrix();
            this->tercer.DibujarAC();
        glPopMatrix();

        MaterialRuby();
        glTranslatef(3.5f,0.0f, -0.6f);
        glRotatef(this->getArt3(),0.0f, 0.0f, 1.0f);
        glPushMatrix();
            this->cuarto.DibujarAC();

        glPopMatrix();

        //EFECTOR FINAL
        glRotatef(-90.0f,0.0f, 0.0f, 1.0f);

        glRotatef(90.f,0.0f,1.0f,0.0f);
        glRotatef(90.f,0.0f,0.0f,1.0f);


        MaterialEsmeralda();

        glTranslatef(-0.5f, 0.0f, 3.5f);
        glRotatef(this->getArt4(),0.0f, 0.0f, 1.0f);
        glPushMatrix();
            this->cuarto_1.Dibujar();

        glPopMatrix();


        glRotatef(-90.f,1.0f,0.0f,0.0f);
        MaterialOro();
        glTranslatef(0.0f,-0.35f, 0.0f);
        glRotatef(this->getArt5(),0.0f, 0.0f, 1.0f);
        glPushMatrix();
            this->quinto.Dibujar();

        glPopMatrix();


        glRotatef(90.f,1.0f,0.0f,0.0f);
        glRotatef(this->getArt6(),0.0f, 0.0f, 1.0f);

        glTranslatef(0.0f,0.0f, 0.0f);

        glPushMatrix();
            this->sexto.Dibujar();
           // sensor.DibujarAC();
        glPopMatrix();

    glPopMatrix();

   if(sePintan)
    {
        inter_1.DibujarAC();
        inter_2.DibujarAC();
        inter_3.DibujarAC();
        inter_4.DibujarAC();
    }
    else
    {
        this->bounding_primer.DibujarAC();
        this->bounding_segundo.DibujarAC();
        this->bounding_tercer.DibujarAC();
        this->bounding_cuarto.DibujarAC();
    }
}

void Manipulador::DibujarEfectorFinal()
{

    if(pintarSensor)
    {
      //  glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
      //  std::cout << "x: " << posX << " y:" << posY << " z:" << posZ << std::endl;
        sensor.Trasladar(posX, posY, posZ);
        sensor.DibujarAC();
        //glPopMatrix();
    }

}

Objeto3D Manipulador::Escanear(Objeto3D *escenario)
{
    return sensor.CalcularOperacionBooleana(escenario, 1);
}

Objeto3D  Manipulador::Escanear(Escena *escenario)
{
    Objeto3D inter, todo;

    for(int i = 0; i < escenario->getNumObjetos();i++)
    {
      inter = sensor.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
      if(inter.getNumPoligonos() > 0)
      {
          todo = inter.CalcularOperacionBooleana(&todo, 2);
      }
    }
    return todo;
}


void Manipulador::OcultarEfectorFinal()
{
    pintarSensor = false;
}

bool Manipulador::estaEnColision(Escena *escenario)
{
    Objeto3D todo;

    bool t = false;

    for(int i = 0; i < escenario->getNumObjetos();i++)
    {
      inter_1 = primer.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
      if(inter_1.getNumPoligonos() > 0)
      {
          cout << "1" << endl;
          sePintan = true;

          return true;
      }
      inter_2 = segundo.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
      if(inter_2.getNumPoligonos() > 0)
      {
          cout << "2" << endl;
          sePintan = true;
          return true;
      }
      inter_3 = tercer.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
      if(inter_3.getNumPoligonos() > 0)
      {
          cout << "3" << endl;
          sePintan = true;
          return true;
      }
      inter_4 = cuarto.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
      if(inter_4.getNumPoligonos() > 0)
      {
          cout << "4" << endl;
          sePintan = true;
          return true;
      }
    }
    return t;
}
