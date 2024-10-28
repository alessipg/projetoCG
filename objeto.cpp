// Classe Objeto
#include "objeto.h"
#include <QDebug>
#include <iostream>

Objeto::Objeto(QString nome, QList<Ponto> pontos, QList<Aresta> arestas) :
    nome(nome), pontos(pontos), arestas(arestas) {}

//implementei sem utilizar matrizes, a Helena vai alterar essa abordagem
void Objeto::translacao(Ponto p) {
    qDebug() << "Movendo o objeto com deslocamento:" << p.x << p.y;
    for (Ponto &ponto : this->pontos) {
        ponto.x += p.x;
        ponto.y += p.y;
        qDebug() << "Novo ponto:" << ponto.x << ponto.y;
    }
}
