#ifndef FRAMEPRINCIPAL_H
#define FRAMEPRINCIPAL_H

#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QTextEdit>
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <iostream>

#include <aresta.h>
#include <displayfile.h>
#include <matriz.h>
#include <window.h>

#define XMIN 20
#define XMAX 570
#define YMIN 20
#define YMAX 511

#define LARGURA_VP (XMAX - XMIN)
#define ALTURA_VP (YMAX - YMIN)

class FramePrincipal : public QFrame
{
    Q_OBJECT
public:
    explicit FramePrincipal(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    DisplayFile df;
    Window *window;
    void processarEntrada(const QString inputText);
    void centralizarWindow();
    void corrigirRotacaoWindow(Window *inputWindow);
    void calcularCoordenadasViewPort(Window *inputWindow);
    void escalonarPontos();
    void pipeline();
    void ajustarPosicionamento();
    //salva o objeto que está desenhado para aplicar a mudança de posição
    //provavelmente quando trabalharmos com mais de um obj na cena isso não funcionará
    Objeto *objCentro;
    Objeto *objAtual;
    bool isPerspectiva;
    Objeto* getObjetoByName(const QString& nome);
    std::tuple<double, double, double> calcularAngulos(Ponto p, Ponto vUp, Ponto centro);
public slots:
    //void transformarWindow(const QString &inputText);
    void transformarObjeto(char op,double v1,double v2,double v3,char eixo, char centro);
};

#endif // FRAMEPRINCIPAL_H
