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
#define XMAX 480
#define YMIN 20
#define YMAX 430

#define LARGURA_VP (XMAX - XMIN)
#define ALTURA_VP (YMAX - YMIN)


class FramePrincipal : public QFrame
{
    Q_OBJECT
public:
    explicit FramePrincipal(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    DisplayFile df;
    void processarEntrada(const QString inputText);
    void centralizarWindow();
    void corrigirRotacaoWindow(Window *inputWindow);
    void calcularCoordenadasViewPort(Window *inputWindow);
    void escalonarPontos();
    void rotinaWindow();
    double anguloViewUp();
    Window *window;
    //objeto que foi escolhido para ser desenhado
    QString objetoAlvo;
    //salva o objeto que está desenhado para aplicar a mudança de posição
    //provavelmente quando trabalharmos com mais de um obj na cena isso não funcionará
    Objeto *objAtual;
    bool isWindow;
    Objeto* getObjetoByName(const QString& nome);
public slots:
    //void transformarWindow(const QString &inputText);
    void desenharObjeto(const QString &buttonText);
    void transformarObjeto(const QString &inputText);
};

#endif // FRAMEPRINCIPAL_H
