#include "ponto.h"
#include <iostream>
Ponto::Ponto(float x, float y, float z) : x(x), y(y), z(z), xWin(x), yWin(y), zWin(z), w(1), wWin(1) {
    for (int i = 0; i < 6; i++) {
        rc[i] = true;
    }
}

void Ponto::calcularOutcode(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
    rc[0] = yWin > ymax; // Acima
    rc[1] = yWin < ymin; // Abaixo
    rc[2] = xWin > xmax; // Direita
    rc[3] = xWin < xmin; // Esquerda
    rc[4] = zWin > zmax; // Frente
    rc[5] = zWin < zmin; // Atrás
}
