#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
using namespace std;

class Matriz {
private:
    vector<vector<float>> dados;
    int linhas, colunas;

public:
    Matriz(int linhas, int colunas);

    float& operator()(int i, int j);

    int getLinhas() const;
    int getColunas() const;

    Matriz operator*(const Matriz& matriz) const;

    void imprimir() const;
};

#endif
