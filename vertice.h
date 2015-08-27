#ifndef VERTICE_H
#define VERTICE_H

#include <QList>
#include "punto3d.h"
#include "arista.h"
#include "vertice.h"
class vertice
{
public:
    vertice();
    vertice(punto3d q);
    QList<vertice*> adyacentes;
    QList<Arista> conexiones;

    vertice *predecesor;
    punto3d configuracion;
    float costoHastaAhora;
    float costoEstimado;
    float costoTotalEstimado;
    bool visitado;


    void addAdyacente(vertice *v, Arista a);
    void addAdyacente(vertice *v);
    void addConexion(Arista a);

    bool esIgual(vertice * otro);
};

#endif // VERTICE_H
