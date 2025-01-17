#ifndef WINDOW_H
#define WINDOW_H
#include <objeto.h>

class Window : public Objeto
{
public:
    Window(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas);
    ~Window();
    Ponto *VRP;
    Ponto *viewUp;
    Ponto *VPN;
    Ponto *COP;
    Ponto *zmin;
    Ponto *zmax;
    float getLargura();
    float getAltura();
    float getProfundidade();
    float getDistanciaFocal();
};

#endif // WINDOW_H
