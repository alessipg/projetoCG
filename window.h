#ifndef WINDOW_H
#define WINDOW_H
#include <objeto.h>

class Window : public Objeto
{
public:
    Window(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas);
    ~Window();
    Ponto *centro;
    Ponto *viewUp;
    float altura;
    float largura;
    float getLargura();
    float getAltura();
};

#endif // WINDOW_H
