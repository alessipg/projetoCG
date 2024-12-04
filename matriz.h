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
    static Matriz translacao(float dx, float dy);
    static Matriz rotacao(Ponto ponto, float angulo);
    static Matriz escalonamento(float sx, float sy);
    static Matriz gerarViewport();

    void imprimir() const;
};

#endif
