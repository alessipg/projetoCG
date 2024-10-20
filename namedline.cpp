#include "NamedLine.h"

NamedLine::NamedLine(const QString& name, const QLine& line)
    : NamedObject(name), line(line) {}

void NamedLine::draw(QPainter& painter) const {
    painter.setPen(Qt::blue);
    painter.drawLine(line);
    painter.drawText(line.center() + QPoint(10, -10), name);
}
