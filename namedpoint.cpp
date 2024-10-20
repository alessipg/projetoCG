#include "NamedPoint.h"

NamedPoint::NamedPoint(const QString& name, const QPoint& point)
    : NamedObject(name), point(point) {}

void NamedPoint::draw(QPainter& painter) const {
    painter.setPen(Qt::red);
    painter.drawEllipse(point, 5, 5);
    painter.drawText(point + QPoint(10, -10), name);
}
