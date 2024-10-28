#ifndef ARESTA_H
#define ARESTA_H
#include <ponto.h>
class Aresta
{
public:
    Aresta(Ponto *a, Ponto *b);
    Ponto *a;
    Ponto *b;
};

#endif // ARESTA_H
