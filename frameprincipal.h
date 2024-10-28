#ifndef FRAMEPRINCIPAL_H
#define FRAMEPRINCIPAL_H

#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <iostream>
#include <QPainter>

#include <aresta.h>
#include <displayfile.h>

class FramePrincipal : public QFrame
{
    Q_OBJECT
public:
    explicit FramePrincipal(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    DisplayFile df;
public slots:
    void desenharObjeto(const QString &buttonText);
    void transladarObjeto();
private:
    //objeto que foi escolhido para ser desenhado
    QString objetoAlvo;
    //salva o objeto que está desenhado para aplicar a mudança de posição
    //provavelmente quando trabalharmos com mais de um obj na cena, isso não funcionará
    Objeto *objAtual;
};

#endif // FRAMEPRINCIPAL_H
