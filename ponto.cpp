#include "ponto.h"

Ponto::Ponto(float x, float y, float z):x(x), y(y), z(z), xWin(x),yWin(y),coordW(1),coordWWin(1){
    for (int i = 0; i < 4; i++) {
        rc[i] = false;
    }

}

void Ponto::calcularOutcode(float xmin, float xmax, float ymin, float ymax) {
    rc[0] = yWin > ymax; // Acima
    rc[1] = yWin < ymin; // Abaixo
    rc[2] = xWin > xmax; // Direita
    rc[3] = xWin < xmin; // Esquerda
}
