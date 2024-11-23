#ifndef WINDOW_H
#define WINDOW_H
#include <objeto.h>

class Window : public Objeto
{
public:
    Window(QString nome, QList<Ponto> pontos, QList<Aresta> arestas);
    Ponto centro;

    float altura;
    float largura;
};

#endif // WINDOW_H
