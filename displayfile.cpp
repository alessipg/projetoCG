#include "displayfile.h"
#include <QList>
DisplayFile::DisplayFile() {
}

void DisplayFile::gerarObjetos(){
    //linha
    QList<Ponto> pontos1={Ponto(100,200),Ponto(200,200)};
    QList<Aresta> arestas1 = {Aresta(&pontos1[0], &pontos1[1])};
    Objeto obj1 = {"Linha",pontos1,arestas1};
    this->displayFile.append(obj1);
    //triangulo
    QList<Ponto> pontos2={Ponto(50,50),Ponto(200,200),Ponto(300,50)};
    QList<Aresta> arestas2 = {Aresta(&pontos2[0], &pontos2[1]),Aresta(&pontos2[0], &pontos2[2]),Aresta(&pontos2[1], &pontos2[2])};
    Objeto obj2 = {"Triângulo",pontos2,arestas2};
    this->displayFile.append(obj2);

    QList<Ponto> pontos3={Ponto(100,200),Ponto(200,200)};
    QList<Aresta> arestas3 = {Aresta(&pontos3[0], &pontos3[1])};
    Objeto obj3 = {"Quadrado",pontos3,arestas3};
    this->displayFile.append(obj3);
}


