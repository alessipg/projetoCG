#include "objeto.h"

Objeto::Objeto(QString nome, QList<Ponto> pontos, QList<Aresta> arestas):
    nome(nome),pontos(pontos),arestas(arestas){}
