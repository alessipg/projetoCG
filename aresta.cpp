#include "aresta.h"
#include <qdebug.h>
Aresta::Aresta(Ponto *a, Ponto *b): a(a), b(b), desenha(true){
}

bool Aresta::clipping(float xmin, float xmax, float ymin, float ymax) {
    // Clipping de Linhas


    // Calcula os outcodes dos extremos da aresta
    a->calcularOutcode(xmin, xmax, ymin, ymax);
    b->calcularOutcode(xmin, xmax, ymin, ymax);

    int outcodeA = (a->rc[0] << 3) | (a->rc[1] << 2) | (a->rc[2] << 1) | a->rc[3];
    int outcodeB = (b->rc[0] << 3) | (b->rc[1] << 2) | (b->rc[2] << 1) | b->rc[3];

    while (true) {
        // Caso 1: Totalmente dentro
        if ((outcodeA | outcodeB) == 0) {
            desenha = true;
            return true;
        }

        // Caso 2: Totalmente fora
        if ((outcodeA & outcodeB) != 0) {
            desenha = false;
            return false;
        }

        // Identifica o ponto fora da janela e aplica o recorte
        int outcodeOut = outcodeA ? outcodeA : outcodeB;
        Ponto* p = (outcodeOut == outcodeA) ? a : b;

        // Calcula o coeficiente angular
        float m = (a->xWin != b->xWin) ? (b->yWin - a->yWin) / (b->xWin - a->xWin) : 0;

        if (outcodeOut & 0b1000) {
            // Acima
            p->xWin += (1 / m) * (ymax - p->yWin);
            p->yWin = ymax;
        } else if (outcodeOut & 0b0100) {
            // Abaixo
            p->xWin += (1 / m) * (ymin - p->yWin);
            p->yWin = ymin;
        } else if (outcodeOut & 0b0010) {
            // Direita
            p->yWin += m * (xmax - p->xWin);
            p->xWin = xmax;
        } else if (outcodeOut & 0b0001) {
            // Esquerda
            p->yWin += m * (xmin - p->xWin);
            p->xWin = xmin;
        }

        // Recalcula o outcode do ponto ajustado
        p->calcularOutcode(xmin, xmax, ymin, ymax);
        outcodeA = (a->rc[0] << 3) | (a->rc[1] << 2) | (a->rc[2] << 1) | a->rc[3];
        outcodeB = (b->rc[0] << 3) | (b->rc[1] << 2) | (b->rc[2] << 1) | b->rc[3];
    }
}

