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
    Matriz operator*(const Matriz& matriz) const;

    void imprimir() const;
    int getLinhas() const;
    int getColunas() const;
    float& operator()(int i, int j);
    static Matriz perspectiva(float d);
    static Matriz rotacaoX(float angulo);
    static Matriz rotacaoZ(float angulo);
    static Matriz rotacaoY(float angulo);
    static Matriz translacao2D(float dx, float dy);
    static Matriz escalonamento2D(float sx, float sy);
    static Matriz gerarIdentidade(int linhas, int colunas);
    static Matriz translacao(float dx, float dy, float dz);
    static Matriz escalonamento(float sx, float sy, float sz);

};

#endif
