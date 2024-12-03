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

    void rotinaWindow();//window e redundante
    void centralizarWindow(Window *inputWindow); //window
    void corrigirRotacaoWindow(Window *inputWindow);//window
    void calcularCoordenadasViewPort(Window *inputWindow);//window
    void escalonarPontos();//window
    void setupWindow();//window
    void rotinaAtualizacaoWindow();//window
    void transformarWindow(const QString &inputText);

};

#endif // WINDOW_H
