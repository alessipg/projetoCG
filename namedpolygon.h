#ifndef NAMEDPOLYGON_H
#define NAMEDPOLYGON_H

#include "NamedObject.h"
#include <QPolygon>

class NamedPolygon : public NamedObject {
public:
    NamedPolygon(const QString& name, const QPolygon& polygon); // Declarar o construtor

    void draw(QPainter& painter) const override;

private:
    QPolygon polygon;
};

#endif // NAMEDPOLYGON_H
