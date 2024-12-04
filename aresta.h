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
    bool clipping(float xmin, float xmax, float ymin, float ymax);
};

#endif // ARESTA_H
