#include "grafo.h"
#include "vertice.h"
Grafo::Grafo()
{

}

vertice *Grafo::agregarVerticeQ(punto3d q)
{
    vertice *v = new vertice(q);
    this->vertices.push_back(v);
    return v;
}

void Grafo::agregarVertice(vertice *v)
{
    this->vertices.push_back(v);
}
void Grafo::agregarArco(vertice *o, vertice *d)
{
    Arista a(o,d);
    this->aristas.push_back(a);
}

void Grafo::agregarArco(Arista a)
{
    this->aristas.push_back(a);
}

vertice* Grafo::elementoConMenorCosto(QList<vertice*> *lista)
{
    vertice *regreso = lista->front();
    for(int i = 0; i < lista->size(); i++)
    {
        if (lista->at(i)->costoTotalEstimado < regreso->costoTotalEstimado)
            regreso = lista->at(i);
    }
    return regreso;
}
vertice* Grafo::EncontrarVertice(vertice *buscado)
{
    for(int i = 0; i < this->vertices.size();i++)
    {
        if(vertices.at(i)->esIgual(buscado))
            return vertices.at(i);
    }
    return NULL;
}

int Grafo::EncontrarIndexVertice(vertice *buscado)
{
    for(int i = 0; i < this->vertices.size();i++)
    {
        if(vertices.at(i)->esIgual(buscado))
            return i;
    }
    return -1;
}
QList<vertice> Grafo::AEstrella(vertice *ini, vertice*fin)
{
    QList<vertice*> nodosAbiertos;
    QList<vertice*> nodosCerrados;
    QList<Arista> aristas;

    vertice* meta = this->EncontrarVertice(fin);
    vertice* inicio = this->EncontrarVertice(ini);

    Heuristica *h = new Heuristica(meta);
    vertice* actual = NULL;
    vertice* destinoi;
    int costoDestinoi;
    bool tentative_is_better;
    bool llego = false;
    QList<vertice> ruta;
    /*************INCIALIZACIÓN DE VARIABLES**************/
    inicio->costoHastaAhora = 0;// función g
    inicio->costoEstimado = h->calcularHeuristica(inicio);//función f = g + h; g = 0; => f = h
    inicio->predecesor = NULL;
    nodosAbiertos.clear();
    nodosCerrados.clear();
    /*****************************************************/

    nodosAbiertos.push_back(inicio);
    ruta.push_back(*inicio);
    /************CICLO PRINCIPAL**************************/
    while (nodosAbiertos.size() > 0)
    {

        actual = elementoConMenorCosto(&nodosAbiertos);
        nodosAbiertos.removeAll(actual);
        if(nodosAbiertos.size() == 0 && !llego)
        {
            nodosAbiertos.push_back(meta);
            llego = true;
        }
        nodosCerrados.push_back(actual);
        aristas = actual->conexiones;
        Arista ai;
        for(int i = 0; i < aristas.size();i++)
        {
            destinoi = aristas.at(i).destino;
            if (aristas.at(i).destino->esIgual(meta))
            {
                cout << "Llego a la meta desde el origen:" << aristas.at(i).origen->configuracion << endl;
                costoDestinoi = 0;
            }
//            if (nodosCerrados.contains(aristas.at(i).destino))
//                continue;
            ai = aristas.at(i);
            costoDestinoi = actual->costoHastaAhora + ai.peso();
            if (!nodosAbiertos.contains(aristas.at(i).destino) && !llego)
            {
                nodosAbiertos.push_back(aristas.at(i).destino);
                tentative_is_better = true;
            }
            else if (costoDestinoi <= aristas.at(i).destino->costoHastaAhora)
            {
                tentative_is_better = true;
            }
            else
            {
                tentative_is_better = false;
            }
            tentative_is_better = true;
            if (tentative_is_better)
            {
                aristas.at(i).destino->predecesor = actual;
                if(aristas.at(i).destino->esIgual(meta))
                {
                    cout << "se agrega predecesor a la meta:" << actual->configuracion << endl;
                    system("PAUSE");
                }
                aristas.at(i).destino->costoHastaAhora = costoDestinoi;
                aristas.at(i).destino->costoTotalEstimado = costoDestinoi + h->calcularHeuristica(destinoi);
            }
        }//Fin del foreach que recorre todas las aristas del nodo actual

    }//Fin de while que verifica que la lista de nodos abiertos no este vacía.

    vertice* nodo = meta;
    cout << "comienzo a generar ruta" << endl;
    while (nodo != NULL)
    {
        ruta.push_back(*nodo);
        cout << "predecesor:" << nodo->configuracion << endl;
        nodo = nodo->predecesor;
    }
    return ruta;
}

QList<vertice> Grafo::Dijkstra(vertice *ini, vertice* fin)
{
    for(int i = 0; i < this->vertices.size();i++)
    {
        this->vertices.at(i)->costoHastaAhora = INT_MAX;
        this->vertices.at(i)->predecesor = NULL;
    }

    int indexOrigen = this->EncontrarIndexVertice(ini);
    int indexMeta = this->EncontrarIndexVertice(fin);
    int indexMinimoCola, indexMinimoVertices;
    this->vertices.at(indexOrigen)->costoHastaAhora = 0;
    QQueue<vertice*> cola;
    vertice *u;
    float peso;
    cola.append(this->vertices.at(indexOrigen));
    while(!cola.empty())
    {
        indexMinimoCola = this->indexElementoMenor(cola);
        u = cola.at(indexMinimoCola);
        indexMinimoVertices = this->EncontrarIndexVertice(u);
        cola.removeAll(u);
        this->vertices.at(indexMinimoVertices)->visitado = true;
        for(int j = 0; j < this->vertices.at(indexMinimoVertices)->adyacentes.size(); j++)
        {
            if(!this->vertices.at(indexMinimoVertices)->adyacentes.at(j)->visitado)
            {
                peso = this->vertices.at(indexMinimoVertices)->configuracion.Distanica(&this->vertices.at(indexMinimoVertices)->adyacentes.at(j)->configuracion);
                if(this->vertices.at(indexMinimoVertices)->adyacentes.at(j)->costoHastaAhora >
                        this->vertices.at(indexMinimoVertices)->costoHastaAhora + peso)
                {
                    this->vertices.at(indexMinimoVertices)->adyacentes.at(j)->costoHastaAhora =  this->vertices.at(indexMinimoVertices)->costoHastaAhora + peso;
                    this->vertices.at(indexMinimoVertices)->adyacentes.at(j)->predecesor = this->vertices.at(indexMinimoVertices);
                    cola.append(this->vertices.at(indexMinimoVertices)->adyacentes.at(j));
                }
            }
        }

        //SE debe remover de la cola el elemento
    }

    QList<vertice> ruta;
    vertice *actual = this->vertices.at(indexMeta);
    while(actual != NULL)
    {
        ruta.push_front(*actual);
        actual = actual->predecesor;
    }
    return ruta;

}

int Grafo::indexElementoMenor(QQueue<vertice*> cola)
{
    int indexMin = 0;
    for(int i = 0; i < cola.size(); i++)
    {
        if(cola.at(i)->costoHastaAhora < cola.at(indexMin)->costoHastaAhora)
            indexMin = i;
    }
    return indexMin;
}

QList<vertice> Grafo::generarRuta(vertice *inicio, vertice *meta)
{
    QList<vertice> ruta;
    vertice* nodo = meta;
    cout << "comienzo a generar ruta" << endl;
    while (nodo != NULL)
    {
        ruta.push_back(*nodo);
        cout << "predecesor:" << nodo->configuracion << endl;
        nodo = nodo->predecesor;
    }
    ruta.push_back(*inicio);
    return ruta;
}

void Grafo::Dibujar()
{


    glBegin(GL_LINES);
    for(int i = 0; i < this->aristas.size();i++)
    {
        glVertex3f(this->aristas.at(i).origen->configuracion.getX(),
                   this->aristas.at(i).origen->configuracion.getY(),
                   this->aristas.at(i).origen->configuracion.getZ());
        glVertex3f(this->aristas.at(i).destino->configuracion.getX(),
                   this->aristas.at(i).destino->configuracion.getY(),
                   this->aristas.at(i).destino->configuracion.getZ());
    }
    glEnd();

    glPointSize(20.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < this->vertices.size();i++)
    {
        if(this->vertices.at(i)->predecesor != NULL)
        {
        glVertex3f(this->vertices.at(i)->configuracion.getX(),
                   this->vertices.at(i)->configuracion.getY(),
                   this->vertices.at(i)->configuracion.getZ());

        }
    }
    glEnd();


    glBegin(GL_LINES);
    for(int i = 0; i < this->vertices.size();i++)
    {
        if(this->vertices.at(i)->predecesor != NULL)
        {
            glVertex3f(this->vertices.at(i)->predecesor->configuracion.getX(),
                       this->vertices.at(i)->predecesor->configuracion.getY(),
                       this->vertices.at(i)->predecesor->configuracion.getZ());
            glVertex3f(this->vertices.at(i)->configuracion.getX(),
                       this->vertices.at(i)->configuracion.getY(),
                       this->vertices.at(i)->configuracion.getZ());
        }
    }
    glEnd();
}
