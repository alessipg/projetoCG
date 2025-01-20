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
    bool isPerspectiva;
    Objeto *objCentro;
    Objeto *objAtual;
    Window *window;
    DisplayFile df;
    void pipeline();
    void escalonarPontos();
    void centralizarWindow();
    void ajustarPosicionamento();
    Objeto* getObjetoByName(const QString& nome);
    void paintEvent(QPaintEvent *event) override;
    void processarEntrada(const QString inputText);
    void corrigirRotacaoWindow(Window *inputWindow);
    void calcularCoordenadasViewPort(Window *inputWindow);
    explicit FramePrincipal(QWidget *parent = nullptr);
    std::tuple<double, double, double> calcularAngulos(Ponto p, Ponto vUp, Ponto centro);
public slots:
    void transformarObjeto(char op,double v1,double v2,double v3,char eixo, char centro);
};

#endif // FRAMEPRINCIPAL_H
