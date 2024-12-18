#ifndef OBJETO_H
#define OBJETO_H
#include <ponto.h>
#include <QList>
#include <QString>
#include <aresta.h>
#include <matriz.h>
#include <QDebug>
#include <iostream>
#include <matriz.h>

class Objeto
{
public:
    Objeto(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas);
    QString nome;
    QList<Ponto*> pontos;
    QList<Aresta*> arestas;
    Ponto centro;
    void transformarPontos(Matriz composta);
    void transformarPontosWin(Matriz composta);
    void ajustarSNC();
    void clipping(float xmin, float xmax, float ymin, float ymax);
    Ponto* calcularCentro();
    virtual ~Objeto();
};

#endif // OBJETO_H
