#include "Matriz.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Construtor
Matriz::Matriz(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    dados.resize(linhas, vector<float>(colunas, 0));
}

// Acesso aos elementos da matriz
float& Matriz::operator()(int i, int j) {
    return dados[i][j];
}

// Retornar número de linhas
int Matriz::getLinhas() const {
    return linhas;
}

// Retornar número de colunas
int Matriz::getColunas() const {
    return colunas;
}

// Sobrecarga do operador *
Matriz Matriz::operator*(const Matriz& matriz) const {
    if (colunas != matriz.getLinhas()) {
        throw invalid_argument("As matrizes não podem ser multiplicadas: dimensões incompatíveis.");
    }

    Matriz resultado(linhas, matriz.getColunas());

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < matriz.getColunas(); j++) {
            for (int k = 0; k < colunas; k++) {
                resultado(i, j) += dados[i][k] * matriz.dados[k][j];
            }]
        }
    }

    return resultado;
}

// Função para imprimir a matriz
void Matriz::imprimir() const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            cout << dados[i][j] << " ";
        }
        cout << endl;
    }
}
