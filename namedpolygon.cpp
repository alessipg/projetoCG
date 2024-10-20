#include "NamedPolygon.h"

NamedPolygon::NamedPolygon(const QString& name, const QPolygon& polygon)
    : NamedObject(name), polygon(polygon) {}

void NamedPolygon::draw(QPainter& painter) const {
    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);
    painter.drawPolygon(polygon);
    painter.drawText(polygon.boundingRect().center() + QPoint(10, -10), name);
}
