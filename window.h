#ifndef WINDOW_H
#define WINDOW_H
#include <objeto.h>

class Window : public Objeto
{
public:
    Window(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas);
    ~Window();
    Ponto *VRP; // Antigo "centro", atualizado para um nome mais "correto
    Ponto *VPN; // Substitui o antigo viewUp por torná-lo obsoleto
    float altura;
    float largura;
    float getLargura();
    float getAltura();
};

#endif // WINDOW_H
