#include "escena.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Escena::Escena()
{

}

Escena::~Escena()
{

}
void Escena::Abrir(char* path)
{
    ifstream fichero(path);
    string cad;
    Objeto3D *tmp;
    float x,y,z;
    char *str;
    if(fichero.bad())
    {
        cout << "No se puede abrir el archivo" << endl;
    }
    else
    {
        while(!fichero.eof())
        {
            fichero >> cad;
            cout << cad << endl;
            //La primer linea del archivo contiene la ruta del archivo .ac que contiene el objeto
            tmp = new Objeto3D();
            str = new char[cad.length()-1];
            strcpy(str, cad.c_str());
            tmp->LoadAC3D(str);

            //La siguiente linea contiene la coordenada de traslación
//            fichero >> cad;
//            x = std::stof(cad);
//            fichero >> cad;
//            y = std::stof(cad);
//            fichero >> cad;
//            z = std::stof(cad);
//            tmp->Trasladar(x,y,z);
            this->objetos.push_back(*tmp);
        }
    }
    cout << "leo bien" << endl;
    fichero.close();
   /* delete tmp;
    delete pto;
    delete str;*/

}

void Escena::Dibujar()
{
    Objeto3D obj;
    punto3d pto;
    for(int i = 0; i < this->objetos.size();i++)
    {
       obj = this->objetos.at(i);
       //pto = this->puntos.at(i);
       //obj.Trasladar(pto.getX(), pto.getY(), pto.getZ());
       obj.DibujarAC();
    }
}

int Escena::getNumObjetos()
{
    return this->objetos.size();
}
