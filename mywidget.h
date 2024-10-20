#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>

class MyWidget : public QWidget {
    Q_OBJECT // Esta macro é necessária

public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(400, 400); // Define o tamanho do widget
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::white); // Preenche o fundo com branco
        painter.setPen(Qt::black); // Define a cor da linha
        painter.drawLine(50, 50, 200, 200); // Desenha a linha
    }
};

#endif // MYWIDGET_H
