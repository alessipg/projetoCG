#include "displayfile.h"

DisplayFile::DisplayFile() {
}

void DisplayFile::gerarObjetos() {
/*  Para fazer o dynamic cast, deve se utilizar ponteiros, então todo o programa foi alterado.
 *  Agora todo obj de classe que herda de Objeto pode ser alocado no df, desde que tenha
 *  destrutor adequado.
 */

    QList<Ponto*> pontos0 = {
        new Ponto(0,0),
        new Ponto(500, 0),
        new Ponto(500, 450),
        new Ponto(0, 450)
    };
    QList<Aresta*> arestas0 = {
        new Aresta(pontos0[0], pontos0[1]),
        new Aresta(pontos0[1], pontos0[2]),
        new Aresta(pontos0[2], pontos0[3]),
        new Aresta(pontos0[3], pontos0[0])
    };
    Window* obj0 = new Window{"Window", pontos0, arestas0};
    this->displayFile.append(obj0);

    // Linha
    QList<Ponto*> pontos1 = {
        new Ponto(100, 200),
        new Ponto(200, 200)
    };
    QList<Aresta*> arestas1 = {
        new Aresta(pontos1[0], pontos1[1])
    };
    Objeto* obj1 = new Objeto{"Linha", pontos1, arestas1};
    this->displayFile.append(obj1);

    // Triângulo
    QList<Ponto*> pontos2 = {
        new Ponto(50, 50),
        new Ponto(200, 200),
        new Ponto(200, 200),
        new Ponto(300, 50),
        new Ponto(300, 50),
        new Ponto(50, 50)
    };
    QList<Aresta*> arestas2 = {
        new Aresta(pontos2[0], pontos2[1]),
        new Aresta(pontos2[2], pontos2[3]),
        new Aresta(pontos2[4], pontos2[5])
    };
    Objeto* obj2 = new Objeto{"Triângulo", pontos2, arestas2};
    this->displayFile.append(obj2);

    // Quadrado
    QList<Ponto*> pontos3 = {
        new Ponto(100, 100),
        new Ponto(100, 200),
        new Ponto(100, 200),
        new Ponto(200, 200),
        new Ponto(200, 200),
        new Ponto(200, 100),
        new Ponto(200, 100),
        new Ponto(100, 100),
    };
    QList<Aresta*> arestas3 = {
        new Aresta(pontos3[0], pontos3[1]),
        new Aresta(pontos3[2], pontos3[3]),
        new Aresta(pontos3[4], pontos3[5]),
        new Aresta(pontos3[6], pontos3[7])
    };
    Objeto* obj3 = new Objeto{"Quadrado", pontos3, arestas3};
    this->displayFile.append(obj3);
}

void DisplayFile::aplicarClipping(){
    for(int i = 1;i<this->displayFile.length();i++){
            for (Aresta* aresta : this->displayFile[i]->arestas) {
                aresta->clipping(this->displayFile[0]->pontos[0]->xWin,
                                 this->displayFile[0]->pontos[2]->xWin,
                                 this->displayFile[0]->pontos[0]->yWin,
                                 this->displayFile[0]->pontos[2]->yWin);
            }

    }
}

void DisplayFile::transformada(Matriz composta){
    for(Objeto* obj : this->displayFile){
        obj->transformarPontosWin(composta);
    }
}

DisplayFile::~DisplayFile() {
    for (auto obj : displayFile) {
        delete obj;
    }
    displayFile.clear();
}
