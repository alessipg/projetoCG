#include "matriz.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <QDebug>

using namespace std;

// Construtor
Matriz::Matriz(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    dados.resize(linhas, vector<float>(colunas, 0));
}

// Retornar número de linhas
int Matriz::getLinhas() const {
    return linhas;
}

// Retornar número de colunas
int Matriz::getColunas() const {
    return colunas;
}

// Acesso aos elementos da matriz
float& Matriz::operator()(int i, int j) {
    return dados[i][j];
}

// Sobrecarga do operador *
Matriz Matriz::operator*(const Matriz& matriz) const {
    if (colunas != matriz.getLinhas()) {
        throw invalid_argument("Erro: dimensões incompatíveis.");
    }

    Matriz resultado(linhas, matriz.getColunas());

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < matriz.getColunas(); j++) {
            for (int k = 0; k < colunas; k++) {
                resultado(i, j) += dados[i][k] * matriz.dados[k][j];
            }
        }
    }

    return resultado;
}


Matriz Matriz::gerarIdentidade(int linhas, int colunas) {

    Matriz identidade(linhas, colunas);

    for(int i=0; i < linhas; i++){
        for(int j=0; j < colunas; j++) {
            if(i==j) {
                identidade(i,j) = 1;
            } else {
                identidade(i,j) = 0;
            }
        }
    }

    return identidade;
}

Matriz Matriz::translacao(float dx, float dy) {
    //implementei sem utilizar matrizes, a Helena vai alterar essa abordagem
    /*qDebug() << "Movendo o objeto com deslocamento:" << p.x << p.y;
    for (Ponto &ponto : this->pontos) {
        ponto.x += p.x;
        ponto.y += p.y;
        qDebug() << "Novo ponto:" << ponto.x << ponto.y;
    }*/

    //implementaçao com matrizes
    Matriz matrizTransl(3,3);
    matrizTransl = Matriz::gerarIdentidade(3,3);

    matrizTransl(0,2) = dx;
    matrizTransl(1,2) = dy;

    return matrizTransl;
}

Matriz Matriz::rotacao(Ponto p, float rad) {

    Matriz matrizRot(3,3);
    matrizRot = Matriz::gerarIdentidade(3,3);

    matrizRot(0,0) = cos(rad);
    matrizRot(0,1) = -sin(rad);
    matrizRot(1,0) = sin(rad);
    matrizRot(1,1) = cos(rad);

    return matrizRot;
}

Matriz Matriz::escalonamento(float sx, float sy) {

    Matriz matrizEsc(3,3);
    matrizEsc = Matriz::gerarIdentidade(3,3);

    matrizEsc(0,0) = sx;
    matrizEsc(1,1) = sy;

    return matrizEsc;
}


/*Matriz Matriz::gerarComposta() {

}*/


// Função para imprimir a matriz
void Matriz::imprimir() const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            cout << dados[i][j] << " ";
        }
        cout << endl;
    }
}
