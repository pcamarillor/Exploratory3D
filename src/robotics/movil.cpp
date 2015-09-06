#include "movil.h"


movil::movil(Escena *esc)
{
    llantaD.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/llantaDer.ac");
    llantaI.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/llantaIzq.ac");
    body.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/body.ac");
    tapa.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/tapa.ac");
    sensores.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/bolitas.ac");
    sensor.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/sensorMovil.ac");
    bounding.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/bounding.ac");
    rinD.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/rinD.ac");
    rinI.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/rinI.ac");
    x = 0.0f;
    y = 0.0f;
    theta = 0.0f;
    indexNodoActual = 0;
    punto3d p(0,0,2.9);
    this->arbol_srt = NULL;
    this->Mover(p);
    hayArbol = false;
    this->escenario = esc;
    //Aprendizaje para la conexión entre los nodos
    ///this->roadMap = this->AprendizajePRM(30,1000,8);

}

movil::movil()
{
    llantaD.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/llantaDer.ac");
    llantaI.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/llantaIzq.ac");
    body.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/body.ac");
    //llantaFr.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/llantaFrente.ac");
    tapa.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/tapa.ac");
    sensor.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/sensorMovil.ac");
    rinD.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/rinD.ac");
    rinI.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/rinI.ac");
    sensores.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/bolitas.ac");
    bounding.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/movil/bounding.ac");
    x = 0.0f;
    y = 0.0f;
    theta = 0.0f;
    indexNodoActual = 0;
    punto3d p(0,0,2.93783);
    this->arbol_srt = NULL;
    this->Mover(p);
    hayArbol = false;
}

void movil::Dibujar()
{

    if(hayArbol)
        arbol_srt->Dibujar();

    this->MaterialPlasticoRojo();
    body.DibujarAC();
    tapa.DibujarAC();
    this->MaterialLLanta();
    llantaI.DibujarAC();
    llantaD.DibujarAC();
    //llantaFr.DibujarAC();
     this->MaterialOro();
    rinD.DibujarAC();
    rinI.DibujarAC();
    sensores.DibujarAC();
//    bounding.DibujarAC();
//    sensor.DibujarAC();

}

/* El método SRT en el móvil, funciona para mover el sistema robótico completo
 * y ampliar la cobertura de exploración. Es por lo anterior, que el método solo
 * regresa una posición, que representa la posición del último nodo que se ha
 * agregado al SRT.
*/
punto3d movil::ExplorarSRT(Escena *escenario, punto3d qact, int IMax, float alpha, float dmin)
{
    punto3d qcand;
    vector<ParEscaneo> S;
    vector<vector<ParEscaneo>> otras;
    Linea radio;
    float trandX;
    bool esValida = false;
    srand(time(NULL));
    this->arbol_srt = new SRT();
    this->escenario = escenario;
    cout << "inicia" << endl;
    S = this->Sensar(escenario);
    for(int i = 0; i < S.size();i++)
    {
        S.at(i).x = this->x;
        S.at(i).y = this->y;
        S.at(i).theta = this->theta;
    }
    arbol_srt->AgregarConfiguracion(qact,S);

    esValida = false;

    for(int i = 0; i < IMax;i++)
    {
        trandX = rand() % 360;
        radio = arbol_srt->RADIO2D(S,trandX, this->x, this->y);
        qcand = arbol_srt->DESPLAZAR2D(&radio,alpha);

        esValida = arbol_srt->VALIDA(qact, qcand, dmin, S, otras);
        this->Mover(qcand);
        esValida = !this->estaEnColision(escenario);
        if(esValida)
        {
            break;
        }
    }

    if(esValida)
    {
        otras.push_back(S);
        cout << "termina" << endl;
        return qcand;
    }
    else
        return qact;
}

punto3d movil::GenerarNodoAleatorio()
{
    punto3d qcand;
    qcand.setX(this->generarAleatorioDouble(-20,20));
    qcand.setY(this->generarAleatorioDouble(-20,20));
    qcand.setZ(2.93783);
    qcand.angulo = 0.0f;
    return qcand;

}

void movil::EncontrarKVecinos(Grafo *miGrafo, int actual, int kVecinos, float distanciaTolerada)
{
    int k = 0;
    Arista a1, a2;
    QList<int> posiblesVecinos; //Almacena el indice en la lista de vertices, donde se localizan los posibles vecinos
    float distancia = 0.0f;

    //Se seleccionan todos los vecinos mas cercanos (con distancoiaTolerada, como parámetro de cercania)
    for(int i = 0; i < miGrafo->vertices.size(); i++)
    {
        distancia = miGrafo->vertices.at(actual)->configuracion.Distanica(&miGrafo->vertices.at(i)->configuracion);
        if (distancia <= distanciaTolerada && distancia > 0)
            posiblesVecinos.push_back(i);

    }

    //Se agregan los k-vecinos que cumplan el metodo local
    while (k <= kVecinos && posiblesVecinos.size() > 0)
    {
        if (this->MetodoLocal(miGrafo->vertices.at(actual), miGrafo->vertices.at(posiblesVecinos.at(0))))
        {
            a1.origen = miGrafo->vertices.at(actual);
            a1.destino =  miGrafo->vertices.at(posiblesVecinos.at(0));

            a2.origen = miGrafo->vertices.at(posiblesVecinos.at(0));
            a2.destino = miGrafo->vertices.at(actual);
            miGrafo->vertices.at(actual)->addAdyacente(miGrafo->vertices.at(posiblesVecinos.at(0)),a1);
            miGrafo->vertices.at(posiblesVecinos.at(0))->addAdyacente(miGrafo->vertices.at(actual),a2);

            miGrafo->aristas.append(a1);
            miGrafo->aristas.append(a2);
        }

        k++;
        posiblesVecinos.removeAt(0);
    }
}

bool movil::MetodoLocal(vertice *origen, vertice *destino)
{
    //Se comprueba la validez del método local, que es una linea recta
    //del orgien, al destino
    return this->Brensenham(origen->configuracion, destino->configuracion);
}

void movil::Conectar(punto3d qini, punto3d qfin)
{
    //Se realiza la conexión entre dos puntos,
    //mediante una consulta al roadmap
    vertice *inicio = new vertice(qini);
    vertice *fin = new vertice(qfin);
    this->roadMap->agregarVertice(inicio);
    this->roadMap->agregarVertice(fin);
    int indexInicio = this->roadMap->EncontrarIndexVertice(inicio);
    int indexFin = this->roadMap->EncontrarIndexVertice(fin);
    this->EncontrarKVecinos(this->roadMap,indexInicio,30,8);
    this->EncontrarKVecinos(this->roadMap,indexFin,30,8);

    QList<vertice> ruta = this->roadMap->Dijkstra(inicio, fin);
    punto3d q1;
    this->puntosRuta.clear();

    for(int i = 0; i < ruta.size();i++)
    {
        q1 = ruta.at(i).configuracion;
        this->puntosRuta.push_back(q1);
    }
}

Grafo* movil::AprendizajePRM(int numNodos = 50, int kVecinos = 6, float distancia = 10)
{
    Grafo *miGrafo = new Grafo();
    int _numNodosGenerados = 0;
    punto3d qcand;
    vertice* tmp;
    int indexVerticeNuevo;
    srand(time(NULL));

    for (int i = 1; i <= numNodos; i++)
    {
        cout << "i:" << i << endl;
         qcand = this->GenerarNodoAleatorio();
         this->Mover(qcand);
        _numNodosGenerados++;
        while (this->estaEnColision(this->escenario))
        {
            qcand = this->GenerarNodoAleatorio();
            this->Mover(qcand);
            _numNodosGenerados++;
        }

        //Si está libre de colisión, se agrega al grafo
        tmp = miGrafo->agregarVerticeQ(qcand);
        indexVerticeNuevo = miGrafo->EncontrarIndexVertice(tmp);
        //Se encuentran los k vecinos
        this->EncontrarKVecinos(miGrafo, indexVerticeNuevo, kVecinos, distancia);
    }

    return miGrafo;

}

vector<ParEscaneo> movil::Sensar(Escena* esc)
{
    Objeto3D inter;
    ParEscaneo tmp;
    vector<ParEscaneo> resultado;
    for(int i = 0; i < esc->getNumObjetos();i++)
    {
        tmp.obstaculos = sensor.CalcularOperacionBooleana(&esc->objetos.at(i),1);
        inter = inter.CalcularOperacionBooleana(&tmp.obstaculos,2);
    }

    tmp.fronteraLibre = sensor.CalcularOperacionBooleana(&inter, 3);
    tmp.obstaculos = inter;
    resultado.push_back(tmp);
    return resultado;
}

void movil::Mover(punto3d qcand)
{
    this->x = qcand.getX();
    this->y = qcand.getY();
    float angulo = qcand.angulo;
    carve::math::Matrix md = carve::math::Matrix::IDENT();
    md = md*md.TRANS(qcand.getX(), 3.48394 + qcand.getY(), 2.54466);
   // md = md*md.ROT(angulo,0,0,1);
    llantaD.TransformarPuntos(&md);
    rinD.TransformarPuntos(&md);

    carve::math::Matrix mi = carve::math::Matrix::IDENT();
    mi = mi*mi.TRANS(qcand.getX(), -3.4509 + qcand.getY(), 2.54466);
  //  mi = mi*mi.ROT(angulo,0,0,1);
    llantaI.TransformarPuntos(&mi);
    rinI.TransformarPuntos(&md);

    carve::math::Matrix m = carve::math::Matrix::IDENT();
    m = m*m.TRANS(qcand.getX(), qcand.getY(), qcand.getZ());
  //  m = m*m.ROT(angulo,0,0,1);
    body.TransformarPuntos(&m);
    bounding.TransformarPuntos(&m);
    carve::math::Matrix mt = carve::math::Matrix::IDENT();
    mt =  mt*mt.TRANS(qcand.getX(), qcand.getY(),5.22441);
   // mt =  mt*mt.ROT(angulo,0,0,1);
    tapa.TransformarPuntos(&mt);
    sensor.TransformarPuntos(&mt);
    sensores.TransformarPuntos(&mt);
}

void movil::Rotar(float angulo)
{
    carve::math::Matrix md = carve::math::Matrix::IDENT();
    md = md*md.ROT(angulo,0,0,1);
    llantaD.TransformarPuntos(&md);
    rinD.TransformarPuntos(&md);

    carve::math::Matrix mi = carve::math::Matrix::IDENT();
    mi = mi*mi.ROT(angulo,0,0,1);
    llantaI.TransformarPuntos(&mi);
    rinI.TransformarPuntos(&md);

    carve::math::Matrix m = carve::math::Matrix::IDENT();
    m = m*m.ROT(angulo,0,0,1);
    body.TransformarPuntos(&m);
    bounding.TransformarPuntos(&m);
    carve::math::Matrix mt = carve::math::Matrix::IDENT();
    mt =  mt*mt.ROT(angulo,0,0,1);
    tapa.TransformarPuntos(&mt);
    sensor.TransformarPuntos(&mt);
    sensores.TransformarPuntos(&mt);
}
bool movil::estaEnColision(Escena *esc)
{

    for(int i = 0; i < esc->getNumObjetos();i++)
    {
        inter = bounding.CalcularOperacionBooleana(&esc->objetos.at(i),1);
        if(inter.getNumPoligonos() > 0)
            return true;

//        inter = llantaD.CalcularOperacionBooleana(&esc->objetos.at(i),1);
//        if(inter.getNumPoligonos() > 0)
//            return true;

//        inter = llantaI.CalcularOperacionBooleana(&esc->objetos.at(i),1);
//        if(inter.getNumPoligonos() > 0)
//            return true;

    }

    return false;
}

void movil::MaterialEsmeralda()
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

void movil::MaterialRuby()
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

void movil::MaterialLLanta()
{
    GLfloat mat_ambient[] = {  0.05375f, 0.05f, 0.06625f, 0.82f};
    GLfloat mat_diffuse[] =  { 0.18275f, 0.17f, 0.22525f, 0.82f};
    GLfloat mat_specular[] = { 0.332741f, 0.328634f, 0.346435f, 0.82f};
    GLfloat shineness = 38.4f;


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shineness);

    glColor3f(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]); //Material esmeralda
}

void movil::MaterialOro()
{
    GLfloat mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f};
    GLfloat mat_diffuse[] =  {0.75164f, 0.60648f, 0.22648f};
    GLfloat mat_specular[] = { 0.628281f, 0.555802f, 0.366065f };
    GLfloat shineness = 0.4f;


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shineness);

    glColor3f(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]); //Material Oro
}

void movil::MaterialPlasticoRojo()
{
    GLfloat mat_ambient[] = {  0.1745f, 0.01175f, 0.01175f, 0.55f};
    GLfloat mat_diffuse[] =  {0.61424f, 0.04136f, 0.04136f, 0.55f};
    GLfloat mat_specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f};
    GLfloat shineness = 88.8f;


    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shineness);

    glColor3f(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]); //Material plastico rojo
}
vector<punto3d> movil::ConstruirRuta(RRT *miRRT, punto3d inicio, punto3d fin)
{
    vector<punto3d> miRuta;
    NodoRRT *actual = miRRT->raiz;
    NodoRRT *mejor;
    float distancia;
    float distanciaMejor;

//    while(actual->hijos.size() > 0)
//    {
//        distanciaMejor = 10000.0f;
//        for(int i = 0; i < actual->hijos.size();i++)
//        {
//            distancia = actual->hijos.at(i)->configuracion.Distanica(&fin);
//            if(distancia < distanciaMejor)
//                mejor = actual->hijos.at(i);
//        }
//        this->Brensenham(actual->configuracion,mejor->configuracion);
//        for(int i = 0; i < this->ruta.size();i++)
//                miRuta.push_back(this->ruta.at(i));

//        //miRuta.push_back(mejor->configuracion);
//        actual = mejor;
//    }
    while(actual != NULL)
    {
        miRuta.push_back(actual->configuracion);
        if(actual->hijos.size() > 0)
            actual = actual->hijos.at(0);
        else
            break;
    }
    miRuta.push_back(fin);
    return miRuta;
}

RRT* movil::CONSTRUIR_RRT(punto3d qini, punto3d qfin, int K)
{
    RRT *miRRT = new RRT();
    punto3d centro;
    centro = qini;
    NodoRRT *xaleat;

    miRRT->AgregarNodo(qini);
    int r;
    int i = 0;
    do
    {
        cout << "Iteracion:" << i << " de la construccion del rrt" << endl;
        cout << "config inicial:" << qini << endl;
        cout << "config final:" << qfin << endl;

        xaleat = miRRT->ESTADO_ALEATORIO(qini, qfin);
        cout << "nuevo estado:" << xaleat->configuracion << endl;
        r = this->EXTENDER_RRT(miRRT, xaleat);

        cout << "resp:" << r << endl;
        i++;

    }while(r != ALCANZADO && i < K);
    xaleat->configuracion = qfin;
    this->EXTENDER_RRT(miRRT,xaleat);
    miRRT->Imprimir();
//    system("PAUSE");
    return miRRT;
}
int movil::EXTENDER_RRT(RRT* miRRT, NodoRRT *x)
{
    NodoRRT *xprox = miRRT->VECINO_MAS_PROXIMO(x);
    NodoRRT *nuevo = this->NUEVO_ESTADO(x,xprox);
    //En this->ruta se encuentan los pasos para ir de x a xnuevo
    this->Mover(nuevo->configuracion);
    if(!this->estaEnColision(this->escenario))
    {
        miRRT->AgregarNodo(nuevo);
    cout << "EXTENDER" << endl;
    cout << "al que se supone q tenia q llegar:" << x->configuracion << endl;
    cout << "al que llegue:" << nuevo->configuracion << endl;
    }
    if(abs(nuevo->configuracion.getX() - x->configuracion.getX()) < 0.01 &&
       abs(nuevo->configuracion.getY() - x->configuracion.getY()) < 0.01)
        return ALCANZADO;
    else
        return AVANZADO;
    miRRT->Retornar_A_Padre();
    return ATRAPADO;
}

NodoRRT* movil::NUEVO_ESTADO(NodoRRT *x, NodoRRT *xprox)
{
    NodoRRT *xnuevo;
    //El nuevo estado debe estar entrte xprox y xnuevo, además no debe estar en colision
    srand(time(NULL));
    punto3d punto;
    int count = 0;
    punto3d pto1 = xprox->configuracion;
    punto3d pto2 = x->configuracion;

    float xaleat;
    float yaleat;

    do
    {
        xaleat = pto1.getX() > pto2.getX() ? this->generarAleatorioDouble(pto2.getX(),pto1.getX()) :
                                              this->generarAleatorioDouble(pto1.getX(),pto2.getX());
        yaleat = pto1.getY() > pto2.getY() ? this->generarAleatorioDouble(pto2.getY(),pto1.getY()) :
                                              this->generarAleatorioDouble(pto1.getY(),pto2.getY());
        punto.setX(xaleat);
        punto.setY(yaleat);
        punto.setZ(pto1.getZ());
        this->Mover(punto);
        cout << "intento de encontrar configs:" << count++ << endl;
    }while(this->estaEnColision(this->escenario) && !this->Brensenham(pto1,punto) && count < 10);
//    cout << "inicial:" << pto1<< endl;
//    cout << "final:" << pto2<< endl;
//    cout << "nuevo encontrado:" << punto << endl;
//    system("PAUSE");
    xnuevo = new NodoRRT(punto);
    return xnuevo;
}

double movil::generarAleatorioDouble(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
}

bool movil::Brensenham(punto3d pto1, punto3d pto2)
{
    int x0 = pto1.getX();
    int y0 = pto1.getY();

    int x1 = pto2.getX();
    int y1 = pto2.getY();

    int x, y, dx, dy, p, incE, incNE, stepx, stepy;
    punto3d tmp;
    this->ruta.clear();
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
          this->Mover(tmp);
          if(!this->estaEnColision(this->escenario))
            this->ruta.push_back(tmp);
          else
            return false;
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
          this->Mover(tmp);
          if(!this->estaEnColision(this->escenario))
            this->ruta.push_back(tmp);
          else
            return false;
        }
      }

    return true;
}
