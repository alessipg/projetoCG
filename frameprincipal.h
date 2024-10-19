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
private:
    QString objetoAlvo;
};

#endif // FRAMEPRINCIPAL_H
