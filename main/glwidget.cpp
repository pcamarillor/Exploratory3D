#include "glwidget.h"
#include "objeto3D.h"

#include <GL/GLU.h>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>

typedef carve::poly::Vertex<3> vertex_t;
typedef carve::poly::Edge<3> edge_t;
typedef carve::poly::Face<3> face_t;
typedef carve::geom::vector<3> vec_t;

void GLWidget::ProbarCSG()
{
    std::vector<carve::poly::Vertex<3> > tet_verts;
    std::vector<carve::poly::Face<3> > tet_faces;
    std::vector<const vertex_t *> corners;

    tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(0.0, 0.0, 0.0)));
    tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(5.0, 0.0, 0.0)));
    tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(0.0, 5.0, 0.0)));
    tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(0.0, 0.0, 5.0)));

    corners.push_back(&tet_verts[0]);
    corners.push_back(&tet_verts[2]);
    corners.push_back(&tet_verts[1]);
    tet_faces.push_back(face_t(corners));
    robot->MaterialRuby();
    corners.clear();
    corners.push_back(&tet_verts[0]);
    corners.push_back(&tet_verts[1]);
    corners.push_back(&tet_verts[3]);
    tet_faces.push_back(face_t(corners));



    corners.clear();
    corners.push_back(&tet_verts[0]);
    corners.push_back(&tet_verts[3]);
    corners.push_back(&tet_verts[2]);
    tet_faces.push_back(face_t(corners));


    corners.clear();
    corners.push_back(&tet_verts[1]);
    corners.push_back(&tet_verts[2]);
    corners.push_back(&tet_verts[3]);
    tet_faces.push_back(face_t(corners));

    carve::poly::Polyhedron  tetrahedron(tet_faces);

    //create a triangle
    std::vector<carve::poly::Vertex<3> > tri_verts;
    std::vector<carve::poly::Face<3> > tri_faces;

    //Vertices
    //crashes if last coordinate set to 1e-8, but ok for 1e-7
    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(-3.0, -3.0, 3.0)));
    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(3.0, -3.0, 3.0)));
    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(3.0, 3.0, 3.0)));
    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(-3.0, 3.0, 3.0)));

    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(3.0, -3.0, -3.0)));
    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(-3.0, -3.0, -3.0)));
    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(-3.0, 3.0, -3.0)));
    tri_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(3.0, 3.0, -3.0)));

    //Face 01
    corners.clear();
    corners.push_back(&tri_verts[0]);
    corners.push_back(&tri_verts[1]);
    corners.push_back(&tri_verts[2]);
    corners.push_back(&tri_verts[3]);
    tri_faces.push_back(face_t(corners));
    /*glBegin(GL_POLYGON);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(1.0, 1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(1.0, 1.0, -1.0);
        glVertex3f(1.0, 1.0, 1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);
        glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(-1.0, -1.0, -1.0);
    glEnd();*/
    //Face 02
    corners.clear();
    corners.push_back(&tri_verts[4]);
    corners.push_back(&tri_verts[5]);
    corners.push_back(&tri_verts[6]);
    corners.push_back(&tri_verts[7]);
    tri_faces.push_back(face_t(corners));

    //Face 03
    corners.clear();
    corners.push_back(&tri_verts[5]);
    corners.push_back(&tri_verts[0]);
    corners.push_back(&tri_verts[3]);
    corners.push_back(&tri_verts[6]);
    tri_faces.push_back(face_t(corners));

    //Face 04
    corners.clear();
    corners.push_back(&tri_verts[1]);
    corners.push_back(&tri_verts[4]);
    corners.push_back(&tri_verts[7]);
    corners.push_back(&tri_verts[2]);
    tri_faces.push_back(face_t(corners));

    //Face 05
    corners.clear();
    corners.push_back(&tri_verts[3]);
    corners.push_back(&tri_verts[2]);
    corners.push_back(&tri_verts[7]);
    corners.push_back(&tri_verts[6]);
    tri_faces.push_back(face_t(corners));

    //Face 06
    corners.clear();
    corners.push_back(&tri_verts[4]);
    corners.push_back(&tri_verts[1]);
    corners.push_back(&tri_verts[0]);
    corners.push_back(&tri_verts[5]);
    tri_faces.push_back(face_t(corners));


    carve::poly::Polyhedron triangle(tri_faces);
    // DibujarPoliedro(&tetrahedron);
    //cut triangle with tetrahedron.
  //  std::vector<carve::poly::Face<3> > caras = ModeloSensorial::Objtedo3ds_2_Polyhedron(&escena);
    //carve::poly::Polyhedron cosa(caras);
    //DibujarPoliedro(&cosa);
    carve::poly::Polyhedron * is_poly = carve::csg::CSG().compute(&tetrahedron,&triangle,
                                                                  carve::csg::CSG::INTERSECTION);

    DibujarPoliedro(is_poly);
    /*std::cout << "Tetrahedron is ... \n" << tetrahedron;
    std::cout << "Triangle is ... \n" << triangle;
    std::cout << "Intersection is ... \n" << *is_poly;*/

}


void GLWidget::DibujarPoliedro(carve::poly::Polyhedron *p)
{
    vertex_t t;
    vertex_t *ptr;
    face_t f;
    vec_t vec, normal;
    for(int j = 0; j  < p->faces.size(); j++)
    {

        f = (face_t)p->faces[j];
        normal = f.plane_eqn.N.v;

        glNormal3f(normal[0],normal[1],normal[2]);
        glBegin(GL_POLYGON);
        for(int i = 0; i < f.nVertices(); i++)
        {
            ptr = (vertex_t*)f.vertex(i);
            vec = ptr->v;
            std::cout << vec << std::endl;
            glVertex3f(vec[0], vec[1], vec[2]);
        }
        glEnd();
    }


}

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    beta = 0;
    alpha = 0;
    cam_x = -55;
    cam_y = 40;
    cam_z = 160;

    posX = 0;
    posY = 0;
    posZ = 0;

    robot = new Manipulador();

    temporizador = new QTimer(this);
    temporizador->setInterval(500);

    temporizador2D = new QTimer(this);
    temporizador2D->setInterval(500);

    temporizador3D = new QTimer(this);
    temporizador3D->setInterval(5);

    temporizadorMovil = new QTimer(this);
    temporizadorMovil->setInterval(500);
    caminaMovil = false;
    indexMovil = 0;

    escena.Abrir("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/escena_02.esc");
    robot->pionero = new movil(&this->escena);
    punto3d qini;
    qini.setX(0);
    qini.setY(0);
    qini.setZ(2.9);
    qini.angulo = 0;
    robot->pionero->Mover(qini);
    hay_escena = false;
    animacion_3D = false;
    pintarEscena = false;
    momentoExploracion3D = false;
    momentoExploracion2D = false;
    map.clear();
    map_2.clear();
    this->qact.setX(0);
    this->qact.setY(0);
    this->qact.setZ(2.9);

    this->qant.setX(0);
    this->qant.setY(0);
    this->qant.setZ(2.9);

}

void GLWidget::initializeGL()
{


    glClearColor(0.7, 0.9, 1.0, 0.0); // This clear the background color to black

    GLfloat light_position1[]  = {0.0f, 10.0f, 0.0f, 1.0f};
    GLfloat light_position2[]  = {0.0f, -10.0f, 0.0f, 1.0f};
    GLfloat light_amiente[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffuseLight[] =  { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat specularLight[] = { 0.4f, 0.5f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);


    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_amiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    screen_height = 471;
    screen_width = 1041;
}

void GLWidget::paintGL()
{
    ParEscaneo pe;
    punto3d q;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport   ( 0, 0, screen_width, screen_height );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ( );
    //float nRange = 10.0f;
    gluPerspective ( 60, ( float ) screen_width / ( float ) screen_height, 1.0, 300.0 );
    // glOrtho(-nRange * screen_width / screen_height, nRange * screen_width / screen_height, -nRange, nRange, -nRange, nRange);
    glMatrixMode   ( GL_MODELVIEW );
    glLoadIdentity ( );
    gluLookAt(cam_x,cam_y,cam_z,0.0,0.0,0.0,0.0,1.0,0.0);

    //ESCALAMIENTO DE LA ESCENA
    glScalef(5.0,5.0,5.0);
    //ROTACION DE LA ESCENA
    glRotatef(alpha,1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);

    glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
    glRotatef(180.0f,0.0f, 0.0f, 1.0f);


    //Ejes
//    glLineWidth(2.5);
//    glColor3f(1.0f,0.0f,0.0f);
//    glBegin(GL_LINES);
//    glVertex3d(-100,0,0);
//    glVertex3d(100,0,0);
//    glEnd();

//    glColor3f(0.0f,1.0f,0.0f);
//    glBegin(GL_LINES);
//    glVertex3d(0,-100,0);
//    glVertex3d(0,100,0);
//    glEnd();

//    glColor3f(0.0f,0.0f,1.0f);
//    glBegin(GL_LINES);
//    glVertex3d(0,0,-100);
//    glVertex3d(0,0,100);
//    glEnd();

    //Piso
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->MaterialPlata();
    glBegin(GL_POLYGON);
        glVertex3d(-100,-100,0);
        glVertex3d(-100,100,0);
        glVertex3d(100,100,0);
        glVertex3d(100,-100,0);
    glEnd();
    if(animacion_3D)
    {
        pe = robot->mapa.at(robot->indexNodoActual);
        if(robot->indexNodoActual == 0)
            map.clear();
        cout << "index actual:" << robot->indexNodoActual << endl;

        map.push_back(pe.obstaculos);
        map_2.push_back(pe.obstaculos);
        robot->setArt1(pe.art1);
        robot->setArt2(pe.art2);
        robot->setArt3(pe.art3);
        robot->CinematicaDirecta();
        robot->Dibujar();
        robot->DibujarEfectorFinal();
        robot->pionero->Dibujar();

        robot->MaterialEsmeralda();
        for(int i = 0; i < map.size(); i++)
            map.at(i).DibujarAC();
        //   robot->mapa.at(i).obstaculos.DibujarAC();

    }
    if(caminaMovil)
    {
        robot->pionero->Mover(this->rutaMovil.at(this->indexMovil));
    }
    if(!hay_escena)
    {
        robot->Dibujar();
        robot->pionero->Dibujar();
        robot->MaterialEsmeralda();
        robot->DibujarEfectorFinal();
        this->MaterialAzul();
        for(int i = 0; i < map_2.size(); i++)
            map_2.at(i).DibujarAC();
      //  robot->pionero->roadMap->Dibujar();
//        for(int i = 0; i < robot->mapa.size(); i++)
//            robot->mapa.at(i).obstaculos.DibujarAC();
    }
    if(hay_escena)
    {
//        if(momentoExploracion3D)
//        {
//            pe = robot->mapa.at(robot->indexNodoActual);
//            if(robot->indexNodoActual == 0)
//                map.clear();
//            cout << "index actual:" << robot->indexNodoActual << endl;

//            map.push_back(pe.obstaculos);
//            robot->setArt1(pe.art1);
//            robot->setArt2(pe.art2);
//            robot->setArt3(pe.art3);
//            robot->CinematicaDirecta();
//            robot->Dibujar();
//            robot->DibujarEfectorFinal();
//            for(int i = 0; i < map.size(); i++)
//               map.at(i).DibujarAC();

//            temporizador->stop();
//            temporizador2D->start();
//        }

//        if(momentoExploracion2D)
//        {
            this->MaterialAzul();
            robot->pionero->roadMap->Dibujar();
            q = robot->pionero->camino.at(robot->pionero->indexNodoActual);
            robot->pionero->Mover(q);
            robot->pionero->Dibujar();
            robot->TrasladarRobot(q.getX(), q.getY(), 0);
            robot->Dibujar();
            this->MaterialAzul();
            for(int i = 0; i < robot->mapa.size(); i++)
                robot->mapa.at(i).obstaculos.DibujarAC();
//        }


    }

    if(pintarEscena)
    {
        this->MaterialAzul();
        escena.Dibujar();
    }


}
void GLWidget::VerEscena()
{
    this->pintarEscena = !this->pintarEscena;
}
void GLWidget::resizeGL(int w, int h)
{

}

void GLWidget::mousePressEvent(QMouseEvent *ev)
{

   this->x = ev->x();
   this->y = ev->y();
   xabc = this->x; yabc = this->y;
   emit Mousse_Pressed();
}

void GLWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() && Qt::LeftButton)
    {
        alpha = (alpha + (ev->y() - yabc));
        beta = (beta + (ev->x() - xabc));
        xabc = ev->x(); yabc = ev->y();
        emit Mouse_Pos();
    }

}

void GLWidget::leaveEvent(QEvent *ev)
{
    emit Mouse_Left();
}
void GLWidget::Explorar2D()
{
    robot->AnimarMovil();
    this->repaint();
}

void GLWidget::Explorar3D()
{
    robot->AnimarManipulador();
    this->repaint();
}

string GLWidget::ExploracionHibrida(int iter2D, int iter3D,float alpha2D, float alpha3D, float dMin2D,
                   float dMin3D, int k2D, int k3D)
{
    clock_t t_ini;
    clock_t t_fin;
    double secs;
    string performance;
    t_ini = clock();
    performance = robot->Exploracion_Hibrida(&escena,iter2D,iter3D,alpha3D,alpha2D,dMin2D,dMin3D,k2D,k3D);
    t_fin = clock();
    stringstream ss;
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    ss << "tiempo de simulación:" << secs << "segundos" << endl;
    performance.append(ss.str());
    return performance;

}
string GLWidget::Exploracion3D_SRT(int KMax, int IMax, float alpha, float dmin)
{
    clock_t t_ini;
    clock_t t_fin;
    double secs;
    string performance;
    t_ini = clock();
    performance = robot->Exploracion_SRT(&escena,KMax,IMax,alpha,dmin);
    t_fin = clock();
    stringstream ss;
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    ss << "tiempo de simulación:" << secs << " segundos" << endl;
    performance.append(ss.str());
    return performance;
}

string GLWidget::Exploracion3D_SET(int KMax, int estrategia)
{
    clock_t t_ini;
    clock_t t_fin;
    double secs;
    string performance;
    t_ini = clock();
    performance = robot->Exploracion_SET(&escena,KMax,estrategia);
    t_fin = clock();
    stringstream ss;
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    performance.append("tiempo de simulación:");
    ss << secs;
    performance.append(ss.str());
    performance.append("segundos");
    return performance;
}
void GLWidget::iniciarAnimacion()
{
    QObject::connect(temporizador, SIGNAL(timeout()), this, SLOT(Explorar2D()));
    temporizador->start();
    hay_escena = true;
}

void GLWidget::detenerAnimacion()
{
    temporizador->stop();
}

void GLWidget::iniciarAnimacion3D()
{
    QObject::connect(temporizador3D,SIGNAL(timeout()),this,SLOT(Explorar3D()));
    temporizador3D->start();
    animacion_3D = true;
}

void GLWidget::detenerAnimacion3D()
{
    temporizador3D->stop();
    animacion_3D = false;
}

void GLWidget::VerRobot()
{
    hay_escena = false;
    robot->sePintan = false;
}

void GLWidget::VerificarColision()
{
    QMessageBox qmsj;
    if(robot->estaEnColision(&this->escena))
        qmsj.setText("En colision");
    else
        qmsj.setText("Libre");

    qmsj.exec();
}

void GLWidget::VerificarPuntoEnPoliedro(float x, float y, float z)
{
    QMessageBox qmsj;
    if(robot->PuntoEnSensor(x,y,z))
        qmsj.setText("Si lo contiene");
    else
        qmsj.setText("No lo contiene");
    qmsj.exec();
}

void GLWidget::TestConexion()
{
    punto3d qini(1,0,2.93783);
    punto3d qfin(0,15,2.93783);
    robot->pionero->Conectar(qini,qfin);
    QObject::connect(temporizador, SIGNAL(timeout()), this, SLOT(Explorar()));
    temporizador->start();

}

void GLWidget::MaterialPlata()
{
    GLfloat mat_ambient[] = { 0.19225 ,	0.19225 ,0.19225 };
    GLfloat mat_diffuse[] =  {0.50754,0.50754,0.50754 };
    GLfloat mat_specular[] = { 0.508273 ,0.508273 ,0.508273};
    GLfloat shineness = 0.4f;


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shineness);

    glColor3f(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]); //Material plata
}

void GLWidget::MaterialAzul()
{
    GLfloat ambientAndDiffuse[] = {0.0, 0.1, 0.9, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);

    //glColor3f(mat_specular[0], mat_specular[1], mat_specular[2]); //Material azul
}

void GLWidget::Explorar()
{
    vector<ParEscaneo> par = this->robot->Escanear(&this->escena);
    for(int i = 0; i < par.size();i++)
        this->robot->mapa.push_back(par.at(i));
    cob = this->robot->CalcularCobertura(&this->escena, &this->robot->mapa);
    numEscaneos++;

    cout << "cobertura:" << cob << endl;
    cout << "numEscaneos:" << numEscaneos << endl;
}

string GLWidget::ExploracionMovil_Simple(int IMax, float alpha, float dmin)
{
    qant = qact;
    this->qact = this->robot->pionero->ExplorarSRT(&this->escena,this->qact,IMax,alpha,dmin);
    int entera = this->qact.getX();
    int decimal = this->qact.getX() - entera;
    entera = entera % 20;
    this->qact.setX(entera+ decimal);
    entera = this->qact.getY();
    decimal = this->qact.getY() - entera;
    entera = entera % 20;
    this->qact.setY(entera + decimal);
    stringstream ss;
    ss << "X:" << qact.getX() << " Y:" << qact.getY() << " Z:" << qact.getZ() << endl;

    return ss.str();
}
void GLWidget::CaminarMovil()
{
    indexMovil = (indexMovil + 1) % rutaMovil.size();
    this->repaint();
}

void GLWidget::MoverMovil()
{
    //rutaMovil.clear();
    this->robot->pionero->Mover(this->qact);
    this->robot->TrasladarRobot(this->qact.getX(), this->qact.getY(),this->qact.getZ());
//    this->robot->pionero->Conectar(qant,qact);
//    for(int i = 0; i < this->robot->pionero->camino.size();i++)
//        rutaMovil.push_back(this->robot->pionero->camino.at(i));
//    indexMovil = 0;

//    connect(temporizadorMovil,SIGNAL(timeout()),this,SLOT(CaminarMovil()));
//    temporizadorMovil->start();
//    animacion_3D = true;
    cout << "termino" << endl;
//    this->robot->TrasladarRobot(this->qact.getX(), this->qact.getY(), this->qact.getZ());

}
