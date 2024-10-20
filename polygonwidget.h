#ifndef POLYGONWIDGET_H
#define POLYGONWIDGET_H

#include <QWidget>
#include <QList>
#include "NamedObject.h"
#include "NamedPoint.h"
#include "NamedLine.h"
#include "NamedPolygon.h"

class PolygonWidget : public QWidget {
    Q_OBJECT

public:
    PolygonWidget(QWidget *parent = nullptr);
    ~PolygonWidget(); // Declarar o destrutor

    void addPoint(const QString& name, const QPoint& point);
    void addLine(const QString& name, const QLine& line);
    void addPolygon(const QString& name, const QPolygon& polygon);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<NamedObject*> objects;  // Lista de objetos geométricos
};

#endif // POLYGONWIDGET_H
