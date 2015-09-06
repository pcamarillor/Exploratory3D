#include "objeto3D.h"
#include <qgl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <QString>
#include <QStringList>
#include <QProcess>

using namespace std;

typedef carve::poly::Edge<3> edge_t;
typedef carve::poly::Face<3> face_t;
typedef carve::geom::vector<3> vec_t;

Objeto3D::Objeto3D(void)
{
    numPoligonos = 0;
    numVertices = 0;
    offSetX = 0.0f;
    offSetY = 0.0f;
    offSetZ = 0.0f;
    theta_ant = 0.0f;
    this->pintarPuntos = false;
}


Objeto3D::~Objeto3D(void)
{
}

void Objeto3D::agregarVertice(float _x, float _y, float _z)
{
    punto3d pto(_x,_y,_z);
    vertices.push_back(pto);
}

void Objeto3D::agregarPoligono(unsigned short _a, unsigned short _b, unsigned short _c)
{
    Poligono poli(_a, _b,_c);
    poligonos.push_back(poli);
}

void Objeto3D::agregarPoligono(std::vector<int> esquinas)
{
    Poligono poli(esquinas);
    poligonos.push_back(poli);
}

void Objeto3D::setNumPoligonos(int n)
{
    this->numPoligonos = n;
}
void Objeto3D::setNumVertices(int n)
{
    this->numVertices = n;
}

int Objeto3D::getNumPoligonos()
{
    return this->numPoligonos;
}

int Objeto3D::getNumVertices()
{
    return this->numVertices;
}

void Objeto3D::Dibujar()
{
    int l_index;
    float p1[3], p2[3], p3[3], *normal;
    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index = 0;l_index < this->getNumPoligonos();l_index++)
    {
        p1[0] = this->vertices[ this->poligonos[l_index].getA() ].getX();
        p1[1] = this->vertices[ this->poligonos[l_index].getA() ].getY();
        p1[2] = this->vertices[ this->poligonos[l_index].getA() ].getZ();


        p2[0] = this->vertices[ this->poligonos[l_index].getB() ].getX();
        p2[1] = this->vertices[ this->poligonos[l_index].getB() ].getY();
        p2[2] = this->vertices[ this->poligonos[l_index].getB() ].getZ();

        p3[0] = this->vertices[ this->poligonos[l_index].getC() ].getX();
        p3[1] = this->vertices[ this->poligonos[l_index].getC() ].getY();
        p3[2] = this->vertices[ this->poligonos[l_index].getC() ].getZ();

        normal = CalcularNormal(p1, p2, p3);
        glNormal3f(*(normal + 0), *(normal + 1), *(normal + 2));

        //----------------- FIRST VERTEX -----------------
        // Coordinates of the first vertex
        glVertex3f( this->vertices[ this->poligonos[l_index].getA() ].getX(),
                this->vertices[ this->poligonos[l_index].getA() ].getY(),
                this->vertices[ this->poligonos[l_index].getA() ].getZ()); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Coordinates of the second vertex
        //float x= this->vertex[ this->polygon[l_index].b ].x;

        glVertex3f( this->vertices[ this->poligonos[l_index].getB() ].getX(),
                this->vertices[ this->poligonos[l_index].getB()].getY(),
                this->vertices[ this->poligonos[l_index].getB() ].getZ());

        //----------------- THIRD VERTEX -----------------
        // Coordinates of the Third vertex
        glVertex3f( this->vertices[ this->poligonos[l_index].getC()].getX(),
                this->vertices[ this->poligonos[l_index].getC() ].getY(),
                this->vertices[ this->poligonos[l_index].getC()].getZ());
    }
    glEnd();
}


void Objeto3D::DibujarAC()
{
    Poligono p;
    punto3d pto, *tmp;
    std::vector<carve::poly::Vertex<3> > tet_verts;
    std::vector<const vertex_t *> corners;
    carve::poly::Vertex<3> vertex_tmp;
    this->caras_poliedro.clear();

    for(int i = 0; i < this->numVertices; i++)
    {
        pto = this->vertices.at(i);
        tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(pto.getX(), pto.getY(), pto.getZ())));
    }

    for(int i = 0; i < this->getNumPoligonos(); i++)
    {
        corners.clear();
        p = this->poligonos.at(i);
        for(int j = 0; j < p.getEsquinas().size(); j++)
        {
            vertex_tmp = tet_verts[p.getEsquinas().at(j)];
            corners.push_back(&tet_verts[p.getEsquinas().at(j)]);
        }
        this->caras_poliedro.push_back(face_t(corners));

    }

    carve::poly::Polyhedron  tetrahedron(this->caras_poliedro);

    if(this->pintarPuntos)
    {

        this->GenerarConfiguracionesCandidatas();

        glPointSize(5.f);
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_POINTS);

        for(int i = 0; i < this->configuracionesCandidatas.size();i++)
        {
            glVertex3f(this->configuracionesCandidatas.at(i).getX(),
                       this->configuracionesCandidatas.at(i).getY(),
                       this->configuracionesCandidatas.at(i).getZ());

        }
        glEnd();
    }

    this->DibujarPoliedro(&tetrahedron);
}

void Objeto3D::TransformarPuntos()
{
    int op;
    float theta;
    punto3d pto;
    float x,y,z;
    if(this->ordenRotacion.size()> 0)
    {
        cout << "no debo entrar aca" << endl;
        for(int i = 0; i < this->ordenRotacion.size();i++)
        {
            op = this->ordenRotacion.at(i);
            theta = this->angulosRotacion.at(i);
            this->Rotar(theta, op);
        }
    }
    for(int i = 0; i < this->vertices.size(); i++)
    {
        pto = this->vertices.at(i);
        x = pto.getX() + offSetX;
        y = pto.getY() + offSetY;
        z = pto.getZ() + offSetZ;
        pto.setX(x);
        pto.setY(y);
        pto.setZ(z);
        this->vertices[i] = pto;

    }
}

void Objeto3D::DibujarPoliedro(carve::poly::Polyhedron *p)
{
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
           // std::cout << vec << std::endl;
            glVertex3f(vec[0], vec[1], vec[2]);
        }
        glEnd();
    }
}

Objeto3D Objeto3D::CalcularOperacionBooleana(Objeto3D *B, int idOp)
{
    Poligono p;
    punto3d pto;
    Objeto3D resultado;
    std::vector<carve::poly::Vertex<3> > tet_verts;
    std::vector<const vertex_t *> corners;
    carve::poly::Vertex<3> vertex_tmp;
    this->caras_poliedro.clear();
    //ofstream salida("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/poligonos.txt");
    //salida << this->numVertices << endl;
    for(int i = 0; i < this->numVertices; i++)
    {
        pto = this->vertices.at(i);
        tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(pto.getX(), pto.getY(), pto.getZ())));
      //  salida << pto.getX() << " " << pto.getY() << " " << pto.getZ() << endl;
    }
    //salida << this->getNumPoligonos() << endl;
    for(int i = 0; i < this->getNumPoligonos(); i++)
    {
        corners.clear();
        p = this->poligonos.at(i);
      //  salida << p.getEsquinas().size() << endl;
        for(int j = 0; j < p.getEsquinas().size(); j++)
        {
            vertex_tmp = tet_verts[p.getEsquinas().at(j)];
            corners.push_back(&tet_verts[p.getEsquinas().at(j)]);
        //    salida << p.getEsquinas().at(j) << " ";
        }
        //salida << endl;
        this->caras_poliedro.push_back(face_t(corners));

    }

    carve::poly::Polyhedron A(this->caras_poliedro);
    B->caras_poliedro.clear();
    tet_verts.clear();
    //salida << B->numVertices << endl;
    for(int i = 0; i < B->numVertices; i++)
    {
        pto = B->vertices.at(i);
        tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(pto.getX(), pto.getY(), pto.getZ())));
      //  salida << pto.getX() << " " << pto.getY() << " " << pto.getZ() << endl;
    }
    //salida << B->getNumPoligonos() << endl;
    for(int i = 0; i < B->getNumPoligonos(); i++)
    {
        corners.clear();
        p = B->poligonos.at(i);
      //  salida << p.getEsquinas().size() << endl;
        for(int j = 0; j < p.getEsquinas().size(); j++)
        {
            vertex_tmp = tet_verts[p.getEsquinas().at(j)];
            corners.push_back(&tet_verts[p.getEsquinas().at(j)]);
        //    salida << p.getEsquinas().at(j) << " ";
        }
        //salida << endl;
        B->caras_poliedro.push_back(face_t(corners));

    }
    //salida.close();
    //cout << "escribo" << endl;
    carve::poly::Polyhedron B(B->caras_poliedro);
    carve::poly::Polyhedron * is_poly;
    //cout << "comienza operacion booleana ..." << endl;
//        switch(idOp)
//        {
//            case 1:
//                //1: intersección
//                system("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/EjemploCarveInt.exe");
//            break;
//            case 2:
//            break;
//            case 3:
//                //Diferencia
//                system("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/EjemploCarveDif.exe");
//            break;
//        }
   // cout << "antes"  << endl;
    switch(idOp)
    {
        case 1:
            //1: intersección
            is_poly = carve::csg::CSG().compute(&A,&B,carve::csg::CSG::INTERSECTION);
        break;
        case 2:
            is_poly = carve::csg::CSG().compute(&A,&B,carve::csg::CSG::UNION);
            //2: union
        break;
        case 3:
            //Diferencia
            is_poly = carve::csg::CSG().compute(&A, &B, carve::csg::CSG::A_MINUS_B);
        break;
    }
    //cout << "despues"  << endl;
//    cout << "termina operacion booleana" << endl;
//    ifstream entrada("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/salida.txt");
//    string cad;
//    float mx,my, mz;
//    entrada >> cad;
//    int nVert = std::stoi(cad);
//    resultado.setNumVertices(nVert);
//    for(int i = 0; i < nVert;i++)
//    {
//        entrada >> cad;
//        mx = std::stof(cad);
//        entrada >> cad;
//        my = std::stof(cad);
//        entrada >> cad;
//        mz = std::stof(cad);
//        resultado.agregarVertice(mx, my, mz);

//    }

//    entrada >> cad;
//    int nFaces;
//    nFaces = std::stoi(cad);
//    int nEsquinas;
//    int indiceEsquina;
//    vector<int> esquinas;
//    for(int i = 0; i < nFaces;i++)
//    {
//        entrada >> cad;
//        nEsquinas = std::stoi(cad);
//        for(int j = 0; j < nEsquinas;j++)
//        {
//            entrada >> cad;
//            indiceEsquina = std::stoi(cad);
//            esquinas.push_back(indiceEsquina);
//        }
//        resultado.agregarPoligono(esquinas);
//    }
//    cout << resultado << endl;
//    system("PAUSE");
    vertex_t vertice;
    vertex_t *ptr;
    face_t cara;
    int posicion_vertice;
    std::vector<int> ref;
    resultado.setNumVertices(is_poly->vertices.size());
    for(int i = 0; i < is_poly->vertices.size();i++)
    {
        vertice = is_poly->vertices.at(i);
        resultado.agregarVertice(vertice.v[0], vertice.v[1], vertice.v[2]);
    }
    resultado.setNumPoligonos(is_poly->faces.size());
    for(int i = 0; i < is_poly->faces.size(); i++)
    {
        cara = (face_t)is_poly->faces.at(i);
        ref.clear();
        for(int j  = 0; j < cara.nVertices();j++)
        {
            ptr = (vertex_t*)cara.vertex(j);
            posicion_vertice = this->BuscarVertice(ptr, is_poly);
            if(posicion_vertice >= 0)
            {
                ref.push_back(posicion_vertice);
            }
            else
            {
                cout << "nunca debe pasar" << endl;
                system("PAUSE");
            }

        }
        resultado.agregarPoligono(ref);

    }
    return resultado;

}

int Objeto3D::BuscarVertice(vertex_t *ptr, carve::poly::Polyhedron *poli)
{
    int respuesta = -1;
    vertex_t tmp;
    for(int i = 0; i < poli->vertices.size();i++)
    {
        tmp = poli->vertices.at(i);
        if(tmp.v[0] == ptr->v[0] && tmp.v[1] == ptr->v[1] && tmp.v[2] == ptr->v[2])
            return i;
    }
    return respuesta;
}

void Objeto3D::Load3DS (char *p_filename)
{
    int i; //Index variable

    FILE *l_file; //File pointer

    unsigned short l_chunk_id; //Chunk identifier
    unsigned int l_chunk_lenght; //Chunk lenght

    unsigned char l_char; //Char variable
    unsigned short l_qty; //Number of elements in each chunk

    unsigned short l_face_flags; //Flag that stores some face information
    float xt, yt, zt;
    unsigned short at, bt, ct;
    if ((l_file=fopen (p_filename, "rb"))== NULL) {
        std::cout <<"No se encontro el archivo " << p_filename << std::endl;
        return;
    }

    while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
    {
        //getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

        fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
        //printf("ChunkID: %x\n",l_chunk_id);
        fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
        //printf("ChunkLenght: %x\n",l_chunk_lenght);

        switch (l_chunk_id)
        {
        //----------------- MAIN3DS -----------------
        // Description: Main chunk, contains all the other chunks
        // Chunk ID: 4d4d
        // Chunk Lenght: 0 + sub chunks
        //-------------------------------------------
        case 0x4d4d:
            break;

            //----------------- EDIT3DS -----------------
            // Description: 3D Editor chunk, objects layout info
            // Chunk ID: 3d3d (hex)
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
        case 0x3d3d:
            break;

            //--------------- EDIT_OBJECT ---------------
            // Description: Object block, info for each object
            // Chunk ID: 4000 (hex)
            // Chunk Lenght: len(object name) + sub chunks
            //-------------------------------------------
        case 0x4000:
            i=0;
            do
            {
                fread (&l_char, 1, 1, l_file);
                //p_object->name[i]=l_char;
                i++;
            }while(l_char != '\0' && i<20);
            break;

            //--------------- OBJ_TRIMESH ---------------
            // Description: Triangular mesh, contains chunks for 3d mesh info
            // Chunk ID: 4100 (hex)
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
        case 0x4100:
            break;

            //--------------- TRI_VERTEXL ---------------
            // Description: Vertices list
            // Chunk ID: 4110 (hex)
            // Chunk Lenght: 1 x unsigned short (number of vertices)
            //             + 3 x float (vertex coordinates) x (number of vertices)
            //             + sub chunks
            //-------------------------------------------
        case 0x4110:
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
          //  p_object->vertices_qty = l_qty;
            this->setNumVertices(l_qty);
            std::cout << "num vertices:" << l_qty << std::endl;
            //printf("Number of vertices: %d\n",l_qty);
            for (i = 0; i < l_qty; i++)
            {

                fread (&xt, sizeof(float), 1, l_file);
                //xt = p_object->vertex[i].x;
                //printf("Vertices list x: %f\n",p_object->vertex[i].x);

                fread (&yt, sizeof(float), 1, l_file);
                //yt = p_object->vertex[i].y;
                //printf("Vertices list y: %f\n",p_object->vertex[i].y);

                fread (&zt, sizeof(float), 1, l_file);
                //zt = p_object->vertex[i].z;
                //printf("Vertices list z: %f\n",p_object->vertex[i].z);

                this->agregarVertice(xt,yt,zt);
             //   std::cout << "x:" << xt << " y:" << yt << " z:" << zt << std::endl;
                //Insert into the database

            }
            break;

            //--------------- TRI_FACEL1 ----------------
            // Description: Polygons (faces) list
            // Chunk ID: 4120 (hex)
            // Chunk Lenght: 1 x unsigned short (number of polygons)
            //             + 3 x unsigned short (polygon points) x (number of polygons)
            //             + sub chunks
            //-------------------------------------------
        case 0x4120:
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
          //  p_object->polygons_qty = l_qty;
            this->setNumPoligonos(l_qty);
         //   std::cout << "num poligonos:" << l_qty << std::endl;
            //printf("Number of polygons: %d\n",l_qty);
            for (i=0; i<l_qty; i++)
            {
                fread (&at, sizeof (unsigned short), 1, l_file);
                //at = p_object->polygon[i].a;

                //printf("Polygon point a: %d\n",p_object->polygon[i].a);
                fread (&bt, sizeof (unsigned short), 1, l_file);
                //bt = p_object->polygon[i].b;
                //printf("Polygon point b: %d\n",p_object->polygon[i].b);
                fread (&ct, sizeof (unsigned short), 1, l_file);
                //ct = p_object->polygon[i].c;
                //printf("Polygon point c: %d\n",p_object->polygon[i].c);
                fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
                //printf("Face flags: %x\n",l_face_flags);
                this->agregarPoligono(at, bt, ct);
              //  std::cout << "a: " << at << " b:" << bt << " c:" << ct << std::endl;
            }
            break;

            //------------- TRI_MAPPINGCOORS ------------
            // Description: Vertices list
            // Chunk ID: 4140 (hex)
            // Chunk Lenght: 1 x unsigned short (number of mapping points)
            //             + 2 x float (mapping coordinates) x (number of mapping points)
            //             + sub chunks
            //-------------------------------------------
            //----------- Skip unknow chunks ------------
            //We need to skip all the chunks that currently we don't use
            //We use the chunk lenght information to set the file pointer
            //to the same level next chunk
            //-------------------------------------------
        default:
            fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
    }

    fclose (l_file); // Closes the file stream

}

void Objeto3D::LoadAC3D(char *p_filename)
{
    ifstream fichero(p_filename);
    float x,y,z;

    std::vector<int> referencia;
    int numCorners = 0;
    std::string cad;


    if(fichero.bad())
    {
        cout << "No se puede abrir el archivo" << endl;
        cin.get();
        return;
    }

    while(!fichero.eof())
    {
       fichero >> cad;
       if(cad.compare("numvert") == 0)
       {

           fichero >> cad;
           this->numVertices = std::stoi(cad);
           for(int i = 0; i < this->numVertices; i++)
           {
               fichero >> cad;
               x = std::stof(cad);
               fichero >> cad;
               y = std::stof(cad);
               fichero >> cad;
               z = std::stof(cad);
               this->agregarVertice(x,y,z);
           }
       }
       if(cad.compare("numsurf") == 0)
       {
            fichero >> cad;

            this->numPoligonos = std::stoi(cad);
            for(int i = 0; i < this->numPoligonos; i++)
            {
                do
                {
                    fichero >> cad;
                }while(cad.compare("refs") != 0);
                //Lectura de cada pol铆gono
                fichero >> cad;
                numCorners = std::stoi(cad);
                referencia.clear();
                for(int j = 0; j < numCorners; j++)
                {
                    fichero >> cad;
                    referencia.push_back(std::stoi(cad));
                    fichero >> cad;
                    fichero >> cad;
                }
                this->agregarPoligono(referencia);
            }
       }
       if(cad.compare("loc") == 0)
       {
           fichero >> cad;
           this->offSetX = std::stof(cad);
           fichero >> cad;
           this->offSetY = std::stof(cad);
           fichero >> cad;
           this->offSetZ = std::stof(cad);
         //  cout << "Traslado a x:" << x << " y:" << y << " z:" << z << endl;

       }
    }
    fichero.close();
   // cout << "Archivo leido exitosamente " << p_filename << endl;

   this->Trasladar(0 ,0 ,0);
}

void Objeto3D::toPoliedro()
{
    Poligono p;
    punto3d pto;
    std::vector<carve::poly::Vertex<3> > tet_verts;
    std::vector<const vertex_t *> corners;
    carve::poly::Vertex<3> vertex_tmp;
    this->caras_poliedro.clear();
    for(int i = 0; i < this->numVertices; i++)
    {
        pto = this->vertices.at(i);
     //   cout << pto;
        tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(pto.getX(), pto.getY(), pto.getZ())));
    }
   // cout << "numero de poligonos:" << this->getNumPoligonos() << endl;
    for(int i = 0; i < this->getNumPoligonos(); i++)
    {
        corners.clear();
        p = this->poligonos.at(i);
       // cout << "numero de esquinas:" << p.getEsquinas().size() << endl;
        for(int j = 0; j < p.getEsquinas().size(); j++)
        {
           // vertex_tmp = tet_verts[p.getEsquinas().at(j)];
            corners.push_back(&tet_verts[p.getEsquinas().at(j)]);
         //   cout << p.getEsquinas().at(j) << endl;
         //   cout << vertex_tmp.v[0] << " " << vertex_tmp.v[1] << " " << vertex_tmp.v[2] << endl;
        }
     //   cout << "termino una cara:" << endl;
        this->caras_poliedro.push_back(face_t(corners));

    }
    //cout << "termino" << endl;
}




void Objeto3D::Trasladar(float xt, float yt, float zt)
{
    punto3d vert;
    for(int i = 0; i < this->vertices.size(); i++)
    {
        vert = this->vertices.at(i);
        vert.setX(this->offSetX + vert.xo + xt);
        vert.setY(this->offSetY + vert.yo + yt);
        vert.setZ(this->offSetZ + vert.zo + zt);
        this->vertices[i] = vert;
    }
}

void Objeto3D::Trasladar_Relativa(float xt, float yt, float zt)
{
    punto3d vert;
    /*offSetX = xt;
    offSetY = yt;
    offSetZ = zt;*/
    for(int i = 0; i < this->vertices.size(); i++)
    {
        vert = this->vertices.at(i);
        vert.setX(this->offSetX + vert.getX() + xt);
        vert.setY(this->offSetY + vert.getY() + yt);
        vert.setZ(this->offSetZ + vert.getZ() + zt);
        this->vertices[i] = vert;
    }
}


float Objeto3D::getOffX()
{
    return this->offSetX;
}

float Objeto3D::getOffY()
{
    return this->offSetY;
}

float Objeto3D::getOffZ()
{
    return this->offSetZ;
}

void Objeto3D::setOffX(float _x)
{
    this->offSetX = _x;
}

void Objeto3D::setOffY(float _y)
{
    this->offSetY = _y;
}

void Objeto3D::setOffZ(float _z)
{
    this->offSetZ = _z;
}

void Objeto3D::RotarX(float rx)
{
    this->angulosRotacion.push_back(rx);
    this->ordenRotacion.push_back(0);
}

void Objeto3D::RotarY(float ry)
{
    this->angulosRotacion.push_back(ry);
    this->ordenRotacion.push_back(1);
}

void Objeto3D::RotarZ(float rz)
{
    this->angulosRotacion.push_back(rz);
    this->ordenRotacion.push_back(2);
}

void Objeto3D::ImprimirMatriz()
{
    cout << transformaciones._11 << " " << transformaciones._12 << " " << transformaciones._13 <<   " " << transformaciones._14 << endl;
    cout << transformaciones._21 << " " << transformaciones._22 << " " << transformaciones._23 <<   " " << transformaciones._24 << endl;
    cout << transformaciones._31 << " " << transformaciones._32 << " " << transformaciones._33 <<   " " << transformaciones._34 << endl;
    cout << transformaciones._41 << " " << transformaciones._42 << " " << transformaciones._43 <<   " " << transformaciones._44 << endl;
}
void Objeto3D::Rotar(float theta, int gradoLibertad)
{
//    punto3d pto;
//    float angulo;
//    cout << gradoLibertad << endl;
//    cout << theta << endl;
//    if(theta != theta_ant)
//        {
//            angulo = theta - this->theta_ant;
//    switch(gradoLibertad)
//    {
//        case 0:
////            cout << "antes:" << endl;
////            ImprimirMatriz();
//            transformaciones = carve::math::Matrix::ROT(angulo,+1.0, 0.0, 0.0)*transformaciones;
////            cout << "despues:" << endl;
////            ImprimirMatriz();
//        break;
//        case 1:
////            cout << "antes:" << endl;
////            ImprimirMatriz();
//            transformaciones = carve::math::Matrix::ROT(angulo,0.0,+1.0 , 0.0)*transformaciones;
////            cout << "despues:" << endl;
////            ImprimirMatriz();
//        break;
//        case 2:
////            cout << "antes:" << endl;
////            ImprimirMatriz();
//            transformaciones = carve::math::Matrix::ROT(angulo,0.0,0.0 , +1.0)*transformaciones;
////            cout << "despues:" << endl;
////            ImprimirMatriz();
//        break;
//    }
//    for(int i = 0; i < this->vertices.size(); i++)
//    {
//        pto = this->vertices.at(i);
//     //   cout << "antes " << pto << endl;
//        pto.TransformarPunto(&transformaciones);
//     //   cout << "despues" << pto << endl;
//        this->vertices[i] = pto;
//    }
//    theta_ant = theta;
//    }
    punto3d vert;
    float xp, yp, zp;
    float xa, ya, za;
    float ca, sa;

    float angulo;

    if(theta != theta_ant)
    {
        angulo = theta - this->theta_ant;
        cout << "theta:" << theta << endl;
        cout << "theta_ant:" << this->theta_ant << endl;
        cout << "resta:" << angulo << endl;
        ca = cos(angulo);
        sa = sin(angulo);
    switch(gradoLibertad)
    {
       case 0:
            for(int i = 0; i < this->vertices.size();i++)
            {
                vert = this->vertices.at(i);
                xa = vert.getX();
                ya = vert.getY();
                za = vert.getZ();
                xp = xa;
                yp = ya*ca - za*sa;
                zp = ya*sa + za*ca;
                vert.setX(xp);
                vert.setY(yp);
                vert.setZ(zp);
                this->vertices[i] = vert;
            }
        /*    yp = this->offSetY*cos(angulo) - this->offSetZ*sin(angulo);
            zp = this->offSetY*sin(angulo) + this->offSetZ*cos(angulo);
            this->offSetY = yp;
            this->offSetZ = zp;*/
            break;
       case 1:
            for(int i = 0; i < this->vertices.size();i++)
            {
                vert = this->vertices.at(i);
                xp = vert.getX()*cos(angulo) + vert.getZ()*sin(angulo);
                yp = vert.getY();
                zp = -vert.getX()*sin(angulo) + vert.getZ()*cos(angulo);
                vert.setX(xp);
                vert.setY(yp);
                vert.setZ(zp);
                this->vertices[i] = vert;
            }
          /*  xp = this->offSetX*cos(angulo) + this->offSetZ*sin(angulo);
            zp = -this->offSetX*sin(angulo) + this->offSetZ*cos(angulo);
            this->offSetX = xp;
            this->offSetZ = zp;*/
            break;
       case 2:
            for(int i = 0; i < this->vertices.size();i++)
            {
                vert = this->vertices.at(i);
                xa = vert.getX();
                ya = vert.getY();
                za = vert.getZ();
                xp = (xa*ca - ya*sa);
                yp = (xa*sa + ya*ca);
                zp = za;
                vert.setX(xp);
                vert.setY(yp);
                vert.setZ(zp);

                this->vertices[i] = vert;
            }
            break;
    }
    theta_ant = theta;
    }

}

void Objeto3D::setTheta(float t)
{
     this->theta_ant = t;
}

void Objeto3D::TransformarPuntos(carve::math::Matrix* matriz)
{
     punto3d pto;
     for(int i = 0; i < this->vertices.size(); i++)
     {
         pto = this->vertices.at(i);
         pto.TransformarPunto(matriz);
         this->vertices[i] = pto;
     }
}

bool Objeto3D::ContienePunto(punto3d qcand)
{
    return this->ContienePunto(qcand.getX(), qcand.getY(), qcand.getZ());
}

 bool Objeto3D::ContienePunto(float x, float y, float z)
 {
     bool r = false;
     Objeto3D cuboUnitario, inter;
     cuboUnitario.LoadAC3D("C:/Users/Pablo/Dropbox/Tesis_Maestria/ExploracionAutonoma/build-AppExploracionAutonoma-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Debug/cubo3D.ac");
     carve::math::Matrix m = carve::math::Matrix::IDENT();
     m = m*m.TRANS(x,y,z);
     cuboUnitario.TransformarPuntos(&m);
     inter = this->CalcularOperacionBooleana(&cuboUnitario, 1);
     if(inter.getNumPoligonos() > 0)
         r = true;
     return r;
 }

 float Mod(float x, int mod)
 {
     int entera;
     float decimal;
     entera = (int)x;
     decimal = x - entera;
     entera = entera % mod;
     decimal += entera;
     return decimal;
 }
 void Objeto3D::GenerarConfiguracionesCandidatas()
 {
     Poligono p;
     punto3d pto, *tmp;
     std::vector<carve::poly::Vertex<3> > tet_verts;
     std::vector<const vertex_t *> corners;
     carve::poly::Vertex<3> vertex_tmp;
     this->caras_poliedro.clear();

     for(int i = 0; i < this->numVertices; i++)
     {
         pto = this->vertices.at(i);
         tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(pto.getX(), pto.getY(), pto.getZ())));
     }

     for(int i = 0; i < this->getNumPoligonos(); i++)
     {
         corners.clear();
         p = this->poligonos.at(i);
         for(int j = 0; j < p.getEsquinas().size(); j++)
         {
             vertex_tmp = tet_verts[p.getEsquinas().at(j)];
             corners.push_back(&tet_verts[p.getEsquinas().at(j)]);
         }
         this->caras_poliedro.push_back(face_t(corners));

     }

    carve::poly::Polyhedron  poliedro(this->caras_poliedro);

    vertex_t *ptr;
    face_t f;
    vec_t vec, centro;
    configuracionesCandidatas.clear();
    std::vector<punto3d> lista;
    int count = 0;
    float part;
    for(int j = 0; j  < poliedro.faces.size(); j++)
     {

         f = (face_t)poliedro.faces[j];
         centro = f.centroid();
//         part = centro[0] > 4 ? Mod(centro[0],4) : centro[0];
//         pto.setX(part);
//         part = centro[1] > 4 ? Mod(centro[1],4) : centro[1];
//         pto.setY(part);
//         part = centro[2] > 4 ? Mod(centro[2],4) : centro[2];
//         pto.setZ(part);
         pto.setX(centro[0]);
         pto.setY(centro[1]);
         pto.setZ(centro[2]);
         configuracionesCandidatas.push_back(pto);
         count++;
//         for(int i = 0; i < f.nVertices(); i++)
//         {
//             ptr = (vertex_t*)f.vertex(i);
//             vec = ptr->v;
//             pto.setX(vec[0]);
//             pto.setY(vec[1]);
//             pto.setZ(vec[2]);
//             configuracionesCandidatas.push_back(pto);
//             count++;
//             lista.clear();
//             lista = this->Bresenham3D(centro[0], centro[1], centro[2], vec[0],vec[1],vec[2]);
//             for(int k = 0; k < lista.size();k++)
//             {
//                 pto = lista.at(k);
//                 configuracionesCandidatas.push_back(pto);
//                 count++;
//             }
//         }
     }
 //    cout << "Total de configuraciones candidatas:" << count << endl;
 }

 punto3d Objeto3D::ObtenerCentroide()
 {
     Poligono p;
     punto3d pto, pto2;
     std::vector<carve::poly::Vertex<3> > tet_verts;
     std::vector<const vertex_t *> corners;
     carve::poly::Vertex<3> vertex_tmp;
     this->caras_poliedro.clear();

     for(int i = 0; i < this->numVertices; i++)
     {
         pto = this->vertices.at(i);
         tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(pto.getX(), pto.getY(), pto.getZ())));
     }

     for(int i = 0; i < this->getNumPoligonos(); i++)
     {
         corners.clear();
         p = this->poligonos.at(i);
         for(int j = 0; j < p.getEsquinas().size(); j++)
         {
             vertex_tmp = tet_verts[p.getEsquinas().at(j)];
             corners.push_back(&tet_verts[p.getEsquinas().at(j)]);
         }
         this->caras_poliedro.push_back(face_t(corners));

     }

    carve::poly::Polyhedron  poliedro(this->caras_poliedro);
    vec_t centro1, centro2, normal1, normal2;
    face_t f;
    float dmin = 100.00f;
    float xmean = 0.0f, ymean = 0.0f, zmean = 0.0f;
    punto3d *ptomin1, ptomin2;

    bool romper = false;

    for(int j = 0; j  < poliedro.faces.size(); j++)
     {
         f = (face_t)poliedro.faces[j];
         centro1 = f.centroid();
         xmean += abs(centro1[0]);
         ymean += abs(centro1[1]);
         zmean += abs(centro1[2]);
//         centro1 = f.centroid();
//         normal1 = f.plane_eqn.N.v;

//         f = (face_t)poliedro.faces[j + 1];
//         centro2 = f.centroid();
//         normal2 = f.plane_eqn.N.v;
//         cout << "j:" << j << endl;
//         for(int k = 0; k <= 8; k = k++)
//         {
//             pto.setX(centro1[0] + k*-normal1[0]);
//             pto.setY(centro1[1] + k*-normal1[1]);
//             pto.setZ(centro1[2] + k*-normal1[2]);

//             pto2.setX(centro2[0] + k*-normal2[0]);
//             pto2.setY(centro2[1] + k*-normal2[1]);
//             pto2.setZ(centro2[2] + k*-normal2[2]);
//             if(pto.Distanica(&pto2) < dmin)
//             {
//                 dmin = pto.Distanica(&pto2);
//                 ptomin1 = pto;
//                 ptomin2 = pto2;
//             }
//             else
//             {
//                 romper = true;
//                 break;
//             }


         //}

     }
    xmean = xmean/poliedro.faces.size();
    ymean = ymean/poliedro.faces.size();
    zmean = zmean/poliedro.faces.size();
    ptomin1 = new punto3d(xmean, ymean, zmean);
  //  cout << "punto:" << *ptomin1 << endl;
    return *ptomin1;
 }
 /* find maximum of a and b */
 #define MAX(a,b) (((a)>(b))?(a):(b))

 /* absolute value of a */
 #define ABS(a) (((a)<0) ? -(a) : (a))

 /* take sign of a, either -1, 0, or 1 */
 #define ZSGN(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)

 std::vector<punto3d> Objeto3D::Bresenham3D(int x1, int y1, int z1, const int x2, const int y2, const int z2){
     std::vector<punto3d> salida;
     punto3d pto;
     int xd, yd, zd;
     int x, y, z;
     int ax, ay, az;
     int sx, sy, sz;
     int dx, dy, dz;
     float base = 10, pot = 0;
     float den = pow(base,pot);
     dx = x2 - x1;
     dy = y2 - y1;
     dz = z2 - z1;

     ax = ABS(dx) << 1;
     ay = ABS(dy) << 1;
     az = ABS(dz) << 1;

     sx = ZSGN(dx);
     sy = ZSGN(dy);
     sz = ZSGN(dz);

     x = x1;
     y = y1;
     z = z1;

     if (ax >= MAX(ay, az))            /* x dominant */
     {
         yd = ay - (ax >> 1);
         zd = az - (ax >> 1);
         for (;;)
         {
             pto.setX(x/den);
             pto.setY(y/den);
             pto.setZ(z/den);
             salida.push_back(pto);
             if (x == x2)
             {
                 return salida;
             }

             if (yd >= 0)
             {
                 y += sy;
                 yd -= ax;
             }

             if (zd >= 0)
             {
                 z += sz;
                 zd -= ax;
             }

             x += sx;
             yd += ay;
             zd += az;
         }
     }
     else if (ay >= MAX(ax, az))            /* y dominant */
     {
         xd = ax - (ay >> 1);
         zd = az - (ay >> 1);
         for (;;)
         {
             pto.setX(x/den);
             pto.setY(y/den);
             pto.setZ(z/den);
             salida.push_back(pto);
             if (y == y2)
             {
                 return salida;
             }

             if (xd >= 0)
             {
                 x += sx;
                 xd -= ay;
             }

             if (zd >= 0)
             {
                 z += sz;
                 zd -= ay;
             }

             y += sy;
             xd += ax;
             zd += az;
         }
     }
     else if (az >= MAX(ax, ay))            /* z dominant */
     {
         xd = ax - (az >> 1);
         yd = ay - (az >> 1);
         for (;;)
         {
             pto.setX(x/den);
             pto.setY(y/den);
             pto.setZ(z/den);
             salida.push_back(pto);
             if (z == z2)
             {
                 return salida;
             }

             if (xd >= 0)
             {
                 x += sx;
                 xd -= az;
             }

             if (yd >= 0)
             {
                 y += sy;
                 yd -= az;
             }

             z += sz;
             xd += ax;
             yd += ay;
         }
     }
     return salida;
 }

 float Objeto3D::CalcularVolumen()
 {
     //TODO: Implementar el cálculo de volumen del solido
     punto3d pto, *tmp;
     std::vector<carve::poly::Vertex<3> > tet_verts;
     std::vector<const vertex_t *> corners;
     carve::poly::Vertex<3> vertex_tmp;
     this->caras_poliedro.clear();
     Poligono p;

     for(int i = 0; i < this->numVertices; i++)
     {
         pto = this->vertices.at(i);
         tet_verts.push_back(carve::poly::Vertex<3>(carve::geom::VECTOR(pto.getX(), pto.getY(), pto.getZ())));
     }

     for(int i = 0; i < this->getNumPoligonos(); i++)
     {
         corners.clear();
         p = this->poligonos.at(i);
         for(int j = 0; j < p.getEsquinas().size(); j++)
         {
             vertex_tmp = tet_verts[p.getEsquinas().at(j)];
             corners.push_back(&tet_verts[p.getEsquinas().at(j)]);
         }
         this->caras_poliedro.push_back(face_t(corners));

     }

     carve::poly::Polyhedron  tetrahedron(this->caras_poliedro);
     face_t f;
     float suma,xv, aT, L, H; //Area del i-ésimo triángulo
     vertex_t *ptr;
     vec_t vec, vSiguiente,normal, c;
     punto3d ptoMedio, centroide;
     punto3d pto1, pto2;
     punto3d vA;
     suma = 0;
     for(int i = 0; i < tetrahedron.faces.size();i++)
     {
         f = (face_t)tetrahedron.faces.at(i);
         normal = f.plane_eqn.N.v;
         c = f.centroid();
         centroide.setX(c[0]);
         centroide.setY(c[1]);
         centroide.setZ(c[2]);
         //Se forman los triangulos, para calcular el area
         aT = 0;
         for(int j = 0;j < f.nVertices();j++)
         {
             ptr = (vertex_t*)f.vertex(j);
             vec = ptr->v;
             if(j == f.nVertices() - 1)
             {
                 ptr = (vertex_t*)f.vertex(0);
                 vSiguiente = ptr->v;
             }
             else
             {
                 ptr = (vertex_t*)f.vertex(j + 1);
                 vSiguiente = ptr->v;
             }
             pto1.setX(vec[0]);
             pto1.setY(vec[1]);
             pto1.setZ(vec[2]);
             pto2.setX(vSiguiente[0]);
             pto2.setY(vSiguiente[1]);
             pto2.setZ(vSiguiente[2]);
             ptoMedio = this->PuntoMedio(pto1, pto2);

             L = this->Distancia(pto1, pto2);
             H = this->Distancia(ptoMedio, centroide);
             aT = aT + (L*H)/2;


         }
         vA.setX(normal[0]*aT);
         vA.setY(normal[1]*aT);
         vA.setZ(normal[2]*aT);

         xv = this->ProductoPunto(centroide, vA);
         suma = suma + xv;
     }
  //  cout << "volumen:" << suma/3 << endl;
     return suma/3;
 }

 punto3d Objeto3D::PuntoMedio(punto3d pto1, punto3d pto2)
 {
     punto3d salida;
     salida.setX((pto1.getX() + pto2.getX())/2);
     salida.setY((pto1.getY() + pto2.getY())/2);
     salida.setZ((pto1.getZ() + pto2.getZ())/2);
     return salida;
 }

 float Objeto3D::Distancia(punto3d pto1, punto3d pto2)
 {
     float salida;
     float potencia = 2;
     salida = sqrt(pow((pto2.getX() - pto1.getX()),potencia) +
                   pow((pto2.getY() - pto1.getY()),potencia) +
                   pow((pto2.getZ() - pto1.getZ()),potencia));
     return salida;
 }

 float Objeto3D::ProductoPunto(punto3d vector1, punto3d vector2)
 {
     float salida;
     salida = vector1.getX()*vector2.getX();
     salida = salida + vector1.getY()*vector2.getY();
     salida = salida + vector1.getZ()*vector2.getZ();
     return salida;
 }

 void Objeto3D::PintarPuntos()
 {
     this->pintarPuntos = true;
 }
