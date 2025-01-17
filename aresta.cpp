#include "aresta.h"
#include <qdebug.h>
#include <iostream>
Aresta::Aresta(Ponto *a, Ponto *b): a(a), b(b), desenha(true){
}

bool Aresta::clipping(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
    // Calcula os outcodes dos extremos da aresta
    a->calcularOutcode(xmin, xmax, ymin, ymax, zmin, zmax);
    b->calcularOutcode(xmin, xmax, ymin, ymax, zmin, zmax);

    int outcodeA = (a->rc[0] << 5) | (a->rc[1] << 4) | (a->rc[2] << 3) | (a->rc[3] << 2) | (a->rc[4] << 1) | a->rc[5];
    int outcodeB = (b->rc[0] << 5) | (b->rc[1] << 4) | (b->rc[2] << 3) | (b->rc[3] << 2) | (b->rc[4] << 1) | b->rc[5];

    while (true) {
        // Caso 1: Totalmente dentro do volume de clipping
        if ((outcodeA | outcodeB) == 0) {
            desenha = true;
            return true;
        }

        // Caso 2: Totalmente fora do volume de clipping
        if ((outcodeA & outcodeB) != 0) {
            desenha = false;
            return false;
        }

        // Determina o ponto fora do volume de clipping
        int outcodeOut = outcodeA ? outcodeA : outcodeB;
        Ponto* p = (outcodeOut == outcodeA) ? a : b;

        // Calcula os deltas para as direções
        float dx = b->xWin - a->xWin;
        float dy = b->yWin - a->yWin;
        float dz = b->zWin - a->zWin;

        // Realiza o recorte para cada caso
        if (outcodeOut & 0b100000) {
            // Acima (y > ymax)
            float t = (ymax - p->yWin) / dy;
            p->xWin += t * dx;
            p->zWin += t * dz;
            p->yWin = ymax;
        } else if (outcodeOut & 0b010000) {
            // Abaixo (y < ymin)
            float t = (ymin - p->yWin) / dy;
            p->xWin += t * dx;
            p->zWin += t * dz;
            p->yWin = ymin;
        } else if (outcodeOut & 0b001000) {
            // Direita (x > xmax)
            float t = (xmax - p->xWin) / dx;
            p->yWin += t * dy;
            p->zWin += t * dz;
            p->xWin = xmax;
        } else if (outcodeOut & 0b000100) {
            // Esquerda (x < xmin)
            float t = (xmin - p->xWin) / dx;
            p->yWin += t * dy;
            p->zWin += t * dz;
            p->xWin = xmin;
        } else if (outcodeOut & 0b000010) {
            // Frente (z > zmax)
            float t = (zmax - p->zWin) / dz;
            p->xWin += t * dx;
            p->yWin += t * dy;
            p->zWin = zmax;
        } else if (outcodeOut & 0b000001) {
            // Atrás (z < zmin)
            float t = (zmin - p->zWin) / dz;
            p->xWin += t * dx;
            p->yWin += t * dy;
            p->zWin = zmin;
        }

        // Recalcula o outcode do ponto ajustado
        p->calcularOutcode(xmin, xmax, ymin, ymax, zmin, zmax);
        outcodeA = (a->rc[0] << 5) | (a->rc[1] << 4) | (a->rc[2] << 3) | (a->rc[3] << 2) | (a->rc[4] << 1) | a->rc[5];
        outcodeB = (b->rc[0] << 5) | (b->rc[1] << 4) | (b->rc[2] << 3) | (b->rc[3] << 2) | (b->rc[4] << 1) | b->rc[5];
    }
}



