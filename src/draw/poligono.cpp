#include "poligono.h"

Poligono::Poligono(void)
{
    this->num_vertices = 0;
}


Poligono::Poligono(std::vector<int> vertices)
{
    this->esquinas = vertices;
}

Poligono::Poligono(unsigned short _a, unsigned short _b, unsigned short _c)
{
    this->a = _a;
    this->b = _b;
    this->c = _c;
    this->num_vertices = 3;
}

Poligono::~Poligono(void)
{
}

unsigned short Poligono::getA()
{
    return this->a;
}
unsigned short Poligono::getB()
{
    return this->b;
}
unsigned short Poligono::getC()
{
    return this->c;
}

void Poligono::setA(unsigned short _a)
{
    this->a = _a;
}
void Poligono::setB(unsigned short _b)
{
    this->b = _b;
}
void Poligono::setC(unsigned short _c)
{
    this->c = _c;
}

std::vector<int> Poligono::getEsquinas()
{
    return this->esquinas;
}
