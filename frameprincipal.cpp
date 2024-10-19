#include "frameprincipal.h"

FramePrincipal::FramePrincipal(QWidget *parent)
    : QFrame{parent}
{
    df.gerarObjetos();
}
/*Esse método funciona para qualquer objeto, basta ter
 * todas as arestas definidas. Pensei em tratar, por exemplo, o caso do quadrado
 * adicionando 2 construtores: 1 recebendo os 4 pontos e o outro transformando os
 * 2 pontos recebidos em 4, já que teria que calcular toda vez que fosse desenhado.
*/
void FramePrincipal::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    //inverte o eixo Y
    painter.translate(0, height()); // Move o ponto de origem para o canto inferior esquerdo
    painter.scale(1, -1);           // Inverte o eixo Y
    painter.setPen(QPen(Qt::red, 2));

    for (Objeto &obj : df.displayFile) {
        if (obj.nome == objetoAlvo) {
            for (Aresta aresta : obj.arestas) {
                painter.drawLine(aresta.a.x, aresta.a.y, aresta.b.x, aresta.b.y);
                qDebug() << "a " << aresta.a.x <<aresta.a.y << "b"<<aresta.b.x<< aresta.b.y;
            }
            break;
        }
    }
}
void FramePrincipal::desenharObjeto(const QString &buttonText) {
    qDebug().noquote() << "Desenhando objeto:" << buttonText;
    //armazena o nome do obj que será desenhado
    objetoAlvo = buttonText;
    update();
}
