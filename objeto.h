#ifndef OBJETO_H
#define OBJETO_H
#include <ponto.h>
#include <QList>
#include <QString>
#include <aresta.h>
class Objeto
{
public:
    Objeto(QString nome, QList<Ponto> pontos, QList<Aresta> arestas);
    QString nome;
    QList<Ponto> pontos;
    QList<Aresta> arestas;
};

#endif // OBJETO_H
