#include <QApplication>
#include "PolygonWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PolygonWidget widget;
    widget.setWindowTitle("Lista de Objetos Geométricos");
    widget.resize(600, 600);

    // add obj
    widget.addPoint("Ponto A", QPoint(50, 50));
    widget.addLine("Reta B", QLine(QPoint(50, 200), QPoint(300, 300)));
    QPolygon poly;
    poly << QPoint(150, 150) << QPoint(200, 100) << QPoint(250, 150) << QPoint(200, 200);
    widget.addPolygon("Polígono C", poly);

    widget.show();

    return app.exec();
}
