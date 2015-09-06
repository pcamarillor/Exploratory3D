#include "manipulador.h"
#include "geneticoset.h"
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
    a2 = 3.3f;
    a3 = 0.0f;
    d4 = 3.3f;

    posX = 0;
    posY = 5;
    posZ = 0;

    tx = 0.0f;
    ty = 0.0f;
    tz = 0.0f;

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


    sensor.Trasladar(posX, posY, posZ);
    pintarSensor = true;
    sePintan = false;
    hayLinea = false;
    pionero = new movil();
    this->CinematicaDirecta();
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
//    float cmpY = py*sqrt(pow(px,2)+pow(py,2)-pow(d2,2)) - px*d2;
//    float cmpX = px*sqrt(pow(px,2)+pow(py,2)-pow(d2,2)) - py*d2;
//    if((abs(px) > 0 && abs(px) < 1) ||(abs(py) > 0 && abs(py) < 1 ))
//        art1 = 0.0f;
//    else
//        art1 = atan2(cmpY, cmpX);

//    //Theta 2
//    float R,r;

//    R = sqrt(pow(px,2) + pow(py,2) + pow(pz,2) - pow(d2,2));

//    r = sqrt(pow(pz,2) + pow(py,2) - pow(d2,2));

//    float sinAlpha, cosAlpha;
//    float sinBeta, cosBeta;

//    sinAlpha = -pz/R;
//    cosAlpha = r/R;

//    cosBeta = (pow(a2,2) + pow(R,2) - (pow(d4,2) + pow(a3,2)))/(2*a2*R);
//    if((1 - pow(cosBeta,2)) < 0)
//        sinBeta = 0.0f;
//    else
//        sinBeta = sqrt(1 - pow(cosBeta,2));



//    float cosTeta2,sinTeta2;

//    sinTeta2 = sinAlpha*cosBeta + cosAlpha*sinBeta;
//    cosTeta2 = cosAlpha*cosBeta - sinAlpha*sinBeta;

//    art2 = atan2(sinTeta2,cosTeta2);

//    //Theta 3
//    float cosPhi, sinPhi;

//    cosPhi = (pow(a2,2) + (pow(d4,2) + pow(a3,2)) - pow(R,2))/(2*a2*sqrt(pow(d4,2) + pow(a3,2)));
//    if((1 - pow(cosPhi,2)) < 0)
//        sinPhi = 0.0f;
//    else
//        sinPhi = sqrt(1 - pow(cosPhi,2));

//    sinBeta = d4/(sqrt(pow(d4,2) + pow(a3,2)));
//    cosBeta = abs(a3) /(sqrt(pow(d4,2) + pow(a3,2)));

//    float sinTeta3, cosTeta3;

//    sinTeta3 = sinPhi*cosPhi - cosPhi*sinBeta;
//    cosTeta3 = cosPhi*cosBeta + sinPhi*sinBeta;

//    art3 = atan2(sinTeta3,cosTeta3);

//    art1 = Rad2Grad(art1);
//    art2 = Rad2Grad(art2);
//    art3 = Rad2Grad(art3);
    float obj[3];
    obj[0] = px;
    obj[1] = py;
    obj[2] = pz;

    GeneticoInversa *gi = new GeneticoInversa(0.8,0.6,50, 80,obj);
    gi->GenerarPoblacionInicial();
    gi->Ejecutar();
    IndividuoInversa mejor = gi->MejorIndividuo;
    int count = 0;
    float fitAnt = gi->MejorIndividuo.fitness(obj);
    float fitNvo;
    while(mejor.fitness(obj) > 1)
    {
        gi->Ejecutar();
        mejor = gi->MejorIndividuo;
        fitNvo = mejor.fitness(obj);
//        if(fitNvo == fitAnt)
//            break;

        if(count++ >= 80)
            break;

        fitAnt = fitNvo;
    }

 //cout << "fit:" << mejor.fitness(obj) << endl;
//    cout << "fit:" << mejor.fitness(obj) << endl;
//    cout << "best:" << mejor << endl;
    this->art1 = mejor.xaleat;
    this->art2 = mejor.yaleat;
    this->art3 = mejor.zaleat;

    this->CinematicaDirecta();
}

void Manipulador::CinematicaInversa(punto3d configuracion)
{
    this->CinematicaInversa(configuracion.getX(), configuracion.getY(), configuracion.getZ());
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


    float _gr_90 = Gr2Rad(-90);
    float _gr90 =  Gr2Rad(90);
    float _gr180 = Gr2Rad(180);

    m = carve::math::Matrix::IDENT();
    m = m*m.TRANS(tx,ty,tz + 5.8);
    m = m*m.TRANS(bounding_primer.getOffX(),bounding_primer.getOffY(),bounding_primer.getOffZ());
    bounding_primer.TransformarPuntos(&m);


    m = m*m.TRANS(0.1,-0.3,3.9);
    m = m*m.ROT(_gr_90, 0, 0, 1);
    m = m*m.ROT(-t1, 0, 0, 1);
    m = m*m.TRANS(bounding_segundo.getOffX(), bounding_segundo.getOffY(), bounding_segundo.getOffZ());
    bounding_segundo.TransformarPuntos(&m);

//    //m = m*m.TRANS(0.5,-2.3,5.8);
    m = m*m.TRANS(2.3,-0.5,2.35);
    m = m*m.ROT(_gr_90, 0, 1, 0);
    m = m*m.ROT(_gr90, 0, 0, 1);
    m = m*m.TRANS(bounding_tercer.getOffX(), bounding_tercer.getOffY(), bounding_tercer.getOffZ());
    m = m*m.ROT(-t2, 0, 0, 1);

    bounding_tercer.TransformarPuntos(&m);

    m = m*m.TRANS(3.2,0.3,-4.0);

    m = m*m.ROT(-t3, 0,0,1);
    m = m*m.TRANS(bounding_cuarto.getOffX(), bounding_cuarto.getOffY(), bounding_cuarto.getOffZ());
    bounding_cuarto.TransformarPuntos(&m);
    m = m*m.TRANS(0,-6,0);
    sensor.TransformarPuntos(&m);

//    m = m*m.ROT(-90.0f,0.0f, 0.0f, 1.0f);
//    m = m*m.ROT(90.f,0.0f,1.0f,0.0f);
//    m = m*m.ROT(90.f,0.0f,0.0f,1.0f);
//    m = m*m.TRANS(-0.1f, 0.0f, 3.5f);
//    m = m*m.ROT(this->getArt4(),0.0f, 0.0f, 1.0f);
//    m = m*m.ROT(-90.f,1.0f,0.0f,0.0f);
//    m = m*m.TRANS(0.0f,-0.35f, 0.0f);
//    m = m*m.ROT(this->getArt5(),0.0f, 0.0f, 1.0f);
//    m = m*m.ROT(90.f,1.0f,0.0f,0.0f);
//    m = m*m.ROT(this->getArt6(),0.0f, 0.0f, 1.0f);
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
}

void Manipulador::setArt2(float v)
{
    this->art2 = v;
}

void Manipulador::setArt3(float v)
{
     this->art3 = v;
}

void Manipulador::setArt4(float v)
{
     this->art4 = v;
}

void Manipulador::setArt5(float v)
{
     this->art5 = v;
}

void Manipulador::setArt6(float v)
{
     this->art6 = v;
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

    MaterialRuby();

    if(!sePintan)
    {

        glPushMatrix();
        glTranslatef(tx, ty, tz + 5.8);
        glPushMatrix();
        this->primer.DibujarAC();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 5.8f);
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

        glTranslatef(-0.1f, 0.0f, 3.5f);
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
        //  sensor.DibujarAC();
        glPopMatrix();

        glPopMatrix();

        MaterialRuby();


    }
    else
    {
        colision.DibujarAC();
    }

    glPopMatrix();

    pionero->Dibujar();

//    this->bounding_primer.DibujarAC();
//    this->bounding_segundo.DibujarAC();
//    this->bounding_tercer.DibujarAC();
//    this->bounding_cuarto.DibujarAC();

}

void Manipulador::DibujarEfectorFinal()
{
    int gr = (int)(-this->Gr2Rad(this->art1)) % 180;
//    if(pintarSensor)
//    {
//        carve::math::Matrix mat =  carve::math::Matrix::IDENT();
//        mat = mat*mat.TRANS(posX, posY, posZ);
//        mat = mat*mat.ROT(gr,0,0,1);
//        mat = mat*mat.TRANS(sensor.getOffX(), sensor.getOffY(), sensor.getOffZ());
//        sensor.TransformarPuntos(&mat);
        sensor.PintarPuntos();
        sensor.DibujarAC();
//    }

}

//Objeto3D Manipulador::Escanear(Objeto3D *escenario)
//{
//    return sensor.CalcularOperacionBooleana(escenario, 1);
//}

vector<ParEscaneo> Manipulador::Escanear(Escena *escenario)
{
    Objeto3D inter;
    ParEscaneo tmp;
    bool hayUnion, hayInterseccion;
    vector<ParEscaneo> resultado;

    for(int i = 0; i < escenario->getNumObjetos();i++)
    {

        inter = sensor.CalcularOperacionBooleana(&escenario->objetos.at(i), 3);
        if(inter.getNumPoligonos()> 0)
        {

            tmp.fronteraLibre = inter;
            hayUnion = true;
        }
        inter = sensor.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
        if(inter.getNumPoligonos() > 0)
        {
            tmp.obstaculos = inter;
            hayInterseccion = true;
        }

        if(hayUnion || hayInterseccion)
        {
            resultado.push_back(tmp);
        }
        hayInterseccion = false;
        hayUnion = false;
    }
    return resultado;
}


void Manipulador::OcultarEfectorFinal()
{
    pintarSensor = false;
}

bool Manipulador::estaEnColision(Escena *escenario)
{
    bool t = false;
    Objeto3D inter_1, inter_2, inter_3, inter_4;
    for(int i = 0; i < escenario->getNumObjetos();i++)
    {
        inter_1 = bounding_primer.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
        if(inter_1.getNumPoligonos() > 0)
            return true;

        inter_2 = bounding_segundo.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
        if(inter_2.getNumPoligonos() > 0)
            return true;
        inter_3 = bounding_tercer.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
        if(inter_3.getNumPoligonos() > 0)
            return true;

        inter_4 = bounding_cuarto.CalcularOperacionBooleana(&escenario->objetos.at(i), 1);
        if(inter_4.getNumPoligonos() > 0)
            return true;

    }

    return false;
}

string Manipulador::Exploracion_SET(Escena *escenario, int KMAx, int estrategia)
{
    //Se instancia el árbol SET
    NodoSET *raiz;
    raiz = new NodoSET(NULL);
    raiz->GetPunto().setX(this->posX);
    raiz->GetPunto().setY(this->posY);
    raiz->GetPunto().setZ(this->posZ);

    NodoSET *tmp, *padre(NULL);

    vector<ParEscaneo> pe;
    ParEscaneo escaneoParcial;
    GeneticoSET *gs;
    IndividuoSET sigConfig;
    IndividuoSET mejorIndividuo;
    int indexMejorIndividuo;
    punto3d configNva;
    //Se escanea en la posición inicial


    //Indices de rendimiento
    int Llamadas = 0;
    int numEscaneos = 0;
    pe = this->Escanear(escenario);
    numEscaneos++;
    configNva.setX(this->posX);
    configNva.setY(this->posY);
    configNva.setZ(this->posZ);
    for(int i = 0; i < pe.size();i++)
    {
        escaneoParcial = pe.at(i);
        escaneoParcial.fronteraLibre.GenerarConfiguracionesCandidatas();
        escaneoParcial.configuracion = configNva;
    }

    raiz = new NodoSET(escaneoParcial, NULL, 0);
    arbol_exploracion = new SET(raiz);
    escaneoParcial.art1 = this->art1;
    escaneoParcial.art2 = this->art2;
    escaneoParcial.art3 = this->art3;
    this->CinematicaDirecta();
    Llamadas++;
    mapa.push_back(escaneoParcial);
    padre = raiz;
    //Se ejecuta el método SET
    for(int i = 0; i < KMAx;i++)
    {
        cout << "i:" << i  << endl;
        //If local free boundary is not empty
        mejorIndividuo.fit = 0;
        indexMejorIndividuo = 0;
        for(int j = 0; j < pe.size();j++)
        {
            escaneoParcial = pe.at(j);
            if(escaneoParcial.fronteraLibre.getNumPoligonos() > 0)
            {
                //Search configuration with maximum utility inside current admisible set D(qk, k)
                escaneoParcial.fronteraLibre.GenerarConfiguracionesCandidatas();
                gs = new GeneticoSET(0.2f,0.8f,1,20,this,escenario,&escaneoParcial.fronteraLibre);
                gs->GenerarPoblacionInicial();
                gs->Ejecutar(&numEscaneos, estrategia);
                sigConfig = gs->MejorIndividuo;
                mejorIndividuo = sigConfig.getFitnessCalculada() > mejorIndividuo.getFitnessCalculada() ? sigConfig : mejorIndividuo;
                indexMejorIndividuo = sigConfig.getFitnessCalculada() > mejorIndividuo.getFitnessCalculada() ? j : indexMejorIndividuo;
                //========================= FIN DE BUSQUEDA =========================
            }
            else
            {
                sigConfig.fit = 0;
            }
        }
        sigConfig = mejorIndividuo;
        //If U(qk+1) >= Umin
        if(sigConfig.getFitnessCalculada() >= 100)
        {

            escaneoParcial = pe.at(indexMejorIndividuo);
            escaneoParcial.fronteraLibre.GenerarConfiguracionesCandidatas();
            configNva = escaneoParcial.fronteraLibre.configuracionesCandidatas.at(sigConfig.fenotipo);

            tmp = new NodoSET(escaneoParcial,padre,sigConfig.getFitnessCalculada());
            int entera = (int)configNva.getX();
            float dec = configNva.getX() - entera;
            entera = entera % 5;
            configNva.setX(entera + dec);

            entera = (int)configNva.getY();
            dec = configNva.getY() - entera;
            entera = entera % 5;
            configNva.setY(entera + dec);

            entera = (int)configNva.getZ();
            dec = configNva.getZ() - entera;
            entera = entera % 5;
            configNva.setZ(entera + dec);

            this->CinematicaInversa(configNva.getX(), configNva.getY(), configNva.getZ());
            Llamadas++;
            arbol_exploracion->AgregarHijo(padre,tmp);
            pe = this->Escanear(escenario);
            numEscaneos++;
            for(int j = 0; j < pe.size();j++)
            {
                escaneoParcial = pe.at(j);
                escaneoParcial.fronteraLibre.GenerarConfiguracionesCandidatas();
                escaneoParcial.configuracion = configNva;
                escaneoParcial.art1 = this->art1;
                escaneoParcial.art2 = this->art2;
                escaneoParcial.art3 = this->art3;
                mapa.push_back(escaneoParcial);
            }
            padre = tmp;
        }

    }
    stringstream ss;
    ss << "Num nodos:" << arbol_exploracion->GetNumNodos() << endl;
    ss << "Lamadas al detector:" << Llamadas << endl;
    ss << "Escaneos:" << numEscaneos << endl;
    ss << "Cobertura:" << this->CalcularCobertura(escenario, &mapa) << endl;
    indexNodoActual = 0;
    return ss.str();
}

float Manipulador::CalcularCobertura(Escena* escenario, vector<ParEscaneo>* map)
{
    float volReal = 0.0f;
    for(int i = 0; i < escenario->getNumObjetos();i++)
        volReal += escenario->objetos.at(i).CalcularVolumen();

    float volCalculado = 0.0f;
//    Objeto3D union_de_todo;
//    cout << "antes" << endl;
//    for(int i = 0; i < map->size();i++)
//        union_de_todo = union_de_todo.CalcularOperacionBooleana(&map->at(i).obstaculos,2);
//    cout << "despues" << endl;
    for(int i = 0; i < map->size();i++)
        volCalculado += map->at(i).obstaculos.CalcularVolumen();
    //volCalculado = union_de_todo.CalcularVolumen();
    return (volCalculado*100)/volReal;
}

QList<punto3d> Manipulador::CrearLinea(punto3d qant, punto3d qpost, float angulo)
{
    int x0 = qant.getX();
    int y0 = qant.getY();

    int x1 = qpost.getX();
    int y1 = qpost.getY();

    int x, y, dx, dy, p, incE, incNE, stepx, stepy;
    punto3d tmp;
    QList<punto3d> Linea;
      dx = (x1 - x0);
      dy = (y1 - y0);

     /* determinar que punto usar para empezar, cual para terminar */
      if (dy < 0)
      {
        dy = -dy;
        stepy = -1;
      }
      else
      {
        stepy = 1;
      }

      if (dx < 0)
      {
        dx = -dx;
        stepx = -1;
      }
      else
      {
        stepx = 1;
      }

      x = x0;
      y = y0;
     /* se cicla hasta llegar al extremo de la línea */
      if(dx > dy)
      {
        p = 2*dy - dx;
        incE = 2*dy;
        incNE = 2*(dy-dx);
        while (x != x1)
        {
          x = x + stepx;
          if (p < 0)
          {
            p = p + incE;
          }
          else
          {
            y = y + stepy;
            p = p + incNE;
          }
          tmp.setX(x);
          tmp.setY(y);
          tmp.setZ(2.93783);
          tmp.angulo = angulo;
          Linea.push_back(tmp);
        }
      }
      else{
        p = 2*dx - dy;
        incE = 2*dx;
        incNE = 2*(dx-dy);
        while (y != y1){
          y = y + stepy;
          if (p < 0){
            p = p + incE;
          }
          else {
            x = x + stepx;
            p = p + incNE;
          }
          tmp.setX(x);
          tmp.setY(y);
          tmp.setZ(2.93783);
          tmp.angulo = angulo;
          Linea.push_back(tmp);
        }
      }

    return Linea;
}
string Manipulador::Exploracion_Hibrida(Escena *escenario, int KGenMax, int Kmax, float alpha3D, float alpha2D,
                               float dmin3D, float dmin2D, float IMax2D, float IMax3D)
{
    punto3d qact;
    punto3d qcand;
    punto3d posAbsoluta;
    punto3d qant, qpost;
    vector<ParEscaneo> S;
    QList<punto3d> linea;

    vector<vector<ParEscaneo>> otras;
    Linea radio;
    float trandX, trandZ;
    bool esValida = false;

    //Se establece la posicion absoluta del sistema
    posAbsoluta.setX(0);
    posAbsoluta.setY(0);
    posAbsoluta.setZ(2.9);
    qant = posAbsoluta;


    qact.setX(this->posX);
    qact.setY(this->posY);
    qact.setZ(this->posZ);
    int numEscaneos = 0;
    int llamadasDetector = 0;
    int numNodos = 0;
    float angulo = 0.0f;
    float dy, dx;
    srand(time(NULL));

    this->arbol_srt = new SRT();
    for(int kk = 1; kk <= KGenMax;kk++)
    {
        cout << "kk:" << kk << endl;
        for(int k = 1; k <= Kmax;k++)
        {

            cout << "k:" << k << endl;
            numEscaneos++;
            S = this->Escanear(escenario);
            for(int i = 0; i < S.size();i++)
            {
                S.at(i).art1 = this->art1;
                S.at(i).art2 = this->art2;
                S.at(i).art3 = this->art3;
            }
            arbol_srt->AgregarConfiguracion(qact,S);
            esValida = false;
            for(int i = 0; i < IMax3D ;i++)
            {
                trandX = rand() % 360;
                trandZ = rand() % 360;
                radio = arbol_srt->RADIO(S,trandX,trandZ);
                qcand = arbol_srt->DESPLAZAR(&radio,alpha3D);
                esValida = arbol_srt->VALIDA(qact, qcand, dmin3D, S, otras);
                this->CinematicaInversa(qcand);
                esValida = !this->estaEnColision(escenario);
                llamadasDetector++;
                if(esValida)
                {
                    break;
                }
            }

            if(esValida)
            {
                int entera =  (int)qcand.getZ();
                float dec = qcand.getZ() - entera;
                entera = entera % 5;
                qcand.setZ(entera + dec);
                entera = (int)qcand.getX();
                dec = qcand.getX() - entera;
                entera = entera % 5;
                qcand.setX(entera + dec);

                entera = (int)qcand.getY();
                dec = qcand.getY() - entera;
                entera = entera % 5;
                qcand.setY(entera + dec);

                this->CinematicaInversa(qcand);
                qact = qcand;
                otras.push_back(S);
                for(int l = 0; l < S.size();l++)
                    mapa.push_back(S.at(l));
            }
            else
            {
                this->CinematicaInversa(arbol_srt->ultimoHijo->configuracion);
                qact = arbol_srt->ultimoHijo->padre->configuracion;
                arbol_srt->ultimoHijo = arbol_srt->ultimoHijo->padre;
            }

        emit Avanzar(50);
        }
        //Se mueve el sistema robótico al siguiente punto de exploracion
        qpost = this->pionero->ExplorarSRT(escenario,qant, IMax2D, alpha2D, dmin2D);
        this->pionero->Conectar(qant,qpost);

        dx = qpost.getX() - qant.getX();
        dy = qpost.getY() - qant.getY();

        angulo = atan2(this->Gr2Rad(dy), this->Gr2Rad(dx));
        this->pionero->Mover(qpost);
        this->TrasladarRobot(qpost.getX(), qpost.getY(), qpost.getZ());

        cout << "creo linea" << endl;
        this->pionero->camino.push_back(qant);
        for(int i = 0;i < this->pionero->puntosRuta.size() - 1;i++)
        {
            linea = this->CrearLinea(this->pionero->puntosRuta.at(i), this->pionero->puntosRuta.at(i + 1), angulo);
            for(int jj = 0; jj < linea.size();jj++)
            {

                this->pionero->camino.push_back(linea.at(jj));
            }
        }
        this->pionero->camino.push_back(qpost);
        //this->pionero->camino.push_back(qant);
        qant = qpost;
    }

    numNodos = arbol_srt->GetNumeroNodos();
    stringstream ss;
    ss << "Numero de escaneos:" << numEscaneos << endl;
    ss << "Llamadas al detector:" << llamadasDetector << endl;
    ss << "Numero de nodos:" << numNodos << endl;
    ss << "Coberura" << this->CalcularCobertura(escenario,&mapa) << endl;
    this->indexNodoActual = 0;
    this->pionero->indexNodoActual = 0;
    return ss.str();
}

string Manipulador::Exploracion_SRT(Escena *escenario, int KMax, int IMax, float alpha, float dmin)
{
    punto3d qact;
    punto3d qcand;
    punto3d posAbsoluta;
    vector<ParEscaneo> S;

    vector<vector<ParEscaneo>> otras;
    Linea radio;
    float trandX, trandZ;
    bool esValida = false;

    //Se establece la posicion absoluta del sistema
    posAbsoluta.setX(0);
    posAbsoluta.setY(0);
    posAbsoluta.setZ(0);

    qact.setX(this->posX);
    qact.setY(this->posY);
    qact.setZ(this->posZ);
    int numEscaneos = 0;
    int llamadasDetector = 0;
    int numNodos = 0;
    srand(time(NULL));

    this->arbol_srt = new SRT();
    this->mapa.clear();
    for(int k = 1; k <= KMax;k++)
    {

        cout << "k:" << k << endl;
        numEscaneos++;
        S = this->Escanear(escenario);
        for(int i = 0; i < S.size();i++)
        {
            S.at(i).art1 = this->art1;
            S.at(i).art2 = this->art2;
            S.at(i).art3 = this->art3;
        }
        arbol_srt->AgregarConfiguracion(qact,S);
        esValida = false;
        for(int i = 0; i < IMax ;i++)
        {
            trandX = rand() % 360;
            trandZ = rand() % 360;
            radio = arbol_srt->RADIO(S,trandX,trandZ);
            qcand = arbol_srt->DESPLAZAR(&radio,alpha);
            esValida = arbol_srt->VALIDA(qact, qcand, dmin, S, otras);
            this->CinematicaInversa(qcand);
            esValida = !this->estaEnColision(escenario);
            llamadasDetector++;
            if(esValida)
            {
                break;
            }
        }

        if(esValida)
        {
            int entera =  (int)qcand.getZ();
            float dec = qcand.getZ() - entera;
            entera = entera % 5;
            qcand.setZ(entera + dec);
            entera = (int)qcand.getX();
            dec = qcand.getX() - entera;
            entera = entera % 5;
            qcand.setX(entera + dec);

            entera = (int)qcand.getY();
            dec = qcand.getY() - entera;
            entera = entera % 5;
            qcand.setY(entera + dec);

            this->CinematicaInversa(qcand);
            qact = qcand;
            otras.push_back(S);
             // mapa.push_back(S.at(0));
            for(int l = 0; l < S.size();l++)
                mapa.push_back(S.at(l));
        }
        else
        {
            this->CinematicaInversa(arbol_srt->ultimoHijo->configuracion);
            qact = arbol_srt->ultimoHijo->padre->configuracion;
            arbol_srt->ultimoHijo = arbol_srt->ultimoHijo->padre;
        }



    }
    numNodos = arbol_srt->GetNumeroNodos();
    stringstream ss;
    ss << "Num nodos:" << numEscaneos << endl;
    ss << "Lamadas al detector:" << llamadasDetector << endl;
    ss << "Escaneos:" << numEscaneos << endl;
    ss << "Cobertura:" << this->CalcularCobertura(escenario, &mapa) << endl;
    this->indexNodoActual = 0;
    return ss.str();
}

void Manipulador::TrasladarRobot(float _x, float _y, float _z)
{
    this->tx =    _x;
    this->ty =    _y;
    this->tz =    0;
    this->CinematicaDirecta();

}
void Manipulador::Avanzar(int avance)
{

}

void Manipulador::TrasladarSensor(float xt, float yt, float zt)
{
    carve::math::Matrix mat =  carve::math::Matrix::IDENT();
    mat = mat*mat.TRANS(xt, yt, zt);
    mat = mat*mat.TRANS(sensor.getOffX(), sensor.getOffY(), sensor.getOffZ());
    sensor.TransformarPuntos(&mat);
}
bool Manipulador::autoColision()
{
    Objeto3D obj;
    obj = sensor.CalcularOperacionBooleana(&this->primer,1);
    if(obj.getNumPoligonos() > 0)
       return true;

    obj = sensor.CalcularOperacionBooleana(&this->segundo,1);
    if(obj.getNumPoligonos() > 0)
        return true;

    obj = sensor.CalcularOperacionBooleana(&this->tercer,1);
    if(obj.getNumPoligonos() > 0)
        return true;

   obj = sensor.CalcularOperacionBooleana(&this->cuarto,1);
    if(obj.getNumPoligonos() > 0)
        return true;

    return false;
}

 bool Manipulador::PuntoEnSensor(float x, float y, float z)
 {

     return this->sensor.ContienePunto(x,y,z);
 }

 void Manipulador::AnimarManipulador()
 {
     //TODO: se debe generar un recorrido del arbol, para recorrelo como lista
     //En cada invocación a este método se anima un nodo de esa lista
    indexNodoActual =  (indexNodoActual + 5) % this->mapa.size();
 }

 void Manipulador::AnimarMovil()
 {
     //this->pionero->indexNodoActual =  (this->pionero->indexNodoActual + 1) % this->pionero->camino.size();
     //para la animacion de la prueba
     this->pionero->indexNodoActual = (this->pionero->indexNodoActual + 1) % this->pionero->camino.size();
 }
void Manipulador::ExploracionMovil(Escena *escenario, int Kmax, int IMax, float alpha, float dmin)
{

    //this->pionero->ExplorarSRT(escenario,Kmax, IMax, alpha, dmin);
}
