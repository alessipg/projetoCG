#ifndef NAMEDPOINT_H
#define NAMEDPOINT_H

#include "NamedObject.h"
#include <QPoint>

class NamedPoint : public NamedObject {
public:
    NamedPoint(const QString& name, const QPoint& point); // Declarar o construtor

    void draw(QPainter& painter) const override;

private:
    QPoint point;
};

#endif // NAMEDPOINT_H
