#include "window.h"

Window::Window(QString nome, QList<Ponto> pontos, QList<Aresta> arestas) : Objeto(nome,pontos,arestas){
    centro.x = (pontos[0].x + pontos[2].x)/2;
    centro.y = (pontos[0].y + pontos[2].y)/2;
    altura = pontos[1].y - pontos[0].y;
    largura = pontos[2].x - pontos[1].x;
}
