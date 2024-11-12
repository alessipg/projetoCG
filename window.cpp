#include "window.h"

Window::Window(QString nome, QList<Ponto> pontos, QList<Aresta> arestas) : Objeto(nome,pontos,arestas){
    centro.x = pontos[0].x/2;
    centro.y = pontos[1].y/2;
}
