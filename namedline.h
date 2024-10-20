#ifndef NAMEDLINE_H
#define NAMEDLINE_H

#include "NamedObject.h"
#include <QLine>

class NamedLine : public NamedObject {
public:
    NamedLine(const QString& name, const QLine& line); // Declarar o construtor

    void draw(QPainter& painter) const override;

private:
    QLine line;
};

#endif // NAMEDLINE_H
