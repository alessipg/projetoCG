#ifndef MATRIZ_H
#define MATRIZ_H
#define PI 3.141592654
#include <vector>
#include "ponto.h"

using namespace std;

class Matriz {
private:
    vector<vector<float>> dados;
    int linhas, colunas;

public:
    Matriz(int linhas, int colunas);

    int getLinhas() const;
    int getColunas() const;

    float& operator()(int i, int j);
    Matriz operator*(const Matriz& matriz) const;

    static Matriz gerarIdentidade(int linhas, int colunas);
    static Matriz translacao(float dx, float dy, float dz);
    static Matriz rotacaoX(Ponto ponto, float angulo);
    static Matriz rotacaoY(Ponto ponto, float angulo);
    static Matriz rotacaoZ(Ponto ponto, float angulo);
    static Matriz escalonamento(float sx, float sy, float sz);
    static Matriz gerarViewport();

    void imprimir() const;
};

#endif
