#ifndef ARESTA_H
#define ARESTA_H
#include <ponto.h>
#include <iostream>
class Aresta
{
public:
    Aresta(Ponto *a, Ponto *b);
    Ponto *a;
    Ponto *b;
    bool desenha;
    int cor;
    bool clipping(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
};

#endif // ARESTA_H
