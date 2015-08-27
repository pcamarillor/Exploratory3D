#ifndef POLIGONO_H
#define POLIGONO_H
#include <vector>

class Poligono
{
public:
    Poligono(void);
    Poligono(unsigned short _a, unsigned short _b, unsigned short _c);
    Poligono(std::vector<int> vertices);
    ~Poligono(void);
    unsigned short getA();
    unsigned short getB();
    unsigned short getC();

    void setA(unsigned short _a);
    void setB(unsigned short _b);
    void setC(unsigned short _c);
    std::vector<int> getEsquinas();

private:
    unsigned short a,b,c;
    int num_vertices;
    std::vector<int> esquinas;
};
#endif // POLIGONO_H
