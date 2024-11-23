// Classe Objeto
#include "objeto.h"

Objeto::Objeto(QString nome, QList<Ponto> pontos, QList<Aresta> arestas) :
    nome(nome), pontos(pontos), arestas(arestas) {}

void Objeto::transformarPontos(Matriz composta){

    std::cout << "composta"<<endl;
    composta.imprimir();
    for (int i = 0; i < this->pontos.length(); ++i) {

        Matriz matrizPonto(3,1);
        matrizPonto(0,0) = this->pontos[i].x;
        matrizPonto(1,0) = this->pontos[i].y;
        matrizPonto(2,0) = this->pontos[i].coordW;
        std::cout << "matriz ponto antes" << endl;
        matrizPonto.imprimir();
        matrizPonto = composta * matrizPonto;

        this->pontos[i].x = matrizPonto(0,0);
        this->pontos[i].y = matrizPonto(1,0);
        this->pontos[i].coordW = matrizPonto(2,0);
        std::cout << "matriz ponto depois" << endl;
        matrizPonto.imprimir();
    }
}

void Objeto::transformarPontosWin(Matriz composta){ //exatamente igual à acima, apenas para as
                                                    //coordenadas virtuais.
    std::cout << "composta"<<endl;
    composta.imprimir();
    for (int i = 0; i < this->pontos.length(); ++i) {

        Matriz matrizPonto(3,1);
        matrizPonto(0,0) = this->pontos[i].xWin;
        matrizPonto(1,0) = this->pontos[i].yWin;
        matrizPonto(2,0) = this->pontos[i].coordWWin;
        std::cout << "matriz ponto antes" << endl;
        matrizPonto.imprimir();
        matrizPonto = composta * matrizPonto;

        this->pontos[i].xWin = matrizPonto(0,0);
        this->pontos[i].yWin = matrizPonto(1,0);
        this->pontos[i].coordWWin = matrizPonto(2,0);
        std::cout << "matriz ponto depois" << endl;
        matrizPonto.imprimir();
    }
}
