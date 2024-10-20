#include "PolygonWidget.h"
#include <QPainter>

PolygonWidget::PolygonWidget(QWidget *parent) : QWidget(parent) {
    setFixedSize(400, 400); // Define o tamanho fixo do widget
}

PolygonWidget::~PolygonWidget() {
    qDeleteAll(objects); // Deleta todos os objetos da lista
}

void PolygonWidget::addPoint(const QString& name, const QPoint& point) {
    objects.append(new NamedPoint(name, point)); // Adiciona um ponto
}

void PolygonWidget::addLine(const QString& name, const QLine& line) {
    objects.append(new NamedLine(name, line)); // Adiciona uma linha
}

void PolygonWidget::addPolygon(const QString& name, const QPolygon& polygon) {
    objects.append(new NamedPolygon(name, polygon)); // Adiciona um polígono
}

void PolygonWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white); // Preenche o fundo com branco

    for (const NamedObject* obj : objects) {
        obj->draw(painter);  // Chama o método draw() de cada objeto
    }
}
