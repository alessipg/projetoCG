// Classe Objeto
#include "objeto.h"

Objeto::Objeto(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas) :
    nome(nome), pontos(pontos), arestas(arestas) {
    // Inicialize com os valores do primeiro ponto
    double menorX = pontos[0]->x;
    double maiorX = pontos[0]->x;
    double menorY = pontos[0]->y;
    double maiorY = pontos[0]->y;
    double menorZ = pontos[0]->z;
    double maiorZ = pontos[0]->z;

    // Encontre os valores mínimos e máximos
    for (Ponto *p : pontos) {
        if (p->x < menorX) menorX = p->x;
        if (p->x > maiorX) maiorX = p->x;

        if (p->y < menorY) menorY = p->y;
        if (p->y > maiorY) maiorY = p->y;

        if (p->z < menorZ) menorZ = p->z;
        if (p->z > maiorZ) maiorZ = p->z;
    }

    // Calcula o ponto médio
    double medioX = (menorX + maiorX) / 2;
    double medioY = (menorY + maiorY) / 2;
    double medioZ = (menorZ + maiorZ) / 2;

    // Cria o ponto médio e adiciona à lista de pontos
    Ponto *medio = new Ponto(medioX, medioY, medioZ);
    this->pontos.append(medio);
    this->medio = medio;
}

Objeto::Objeto(){
    this->nome = "Default";
    this->pontos = QList<Ponto*>();
    this->arestas = QList<Aresta*>();
}
void Objeto::transformarPontos(Matriz composta){
    //std::cout<<this->nome.toStdString()<<endl;
    //std::cout << "composta"<<endl;
    //composta.imprimir();
    for (int i = 0; i < this->pontos.length(); ++i) {

        Matriz matrizPonto(4,1);
        matrizPonto(0,0) = this->pontos[i]->x;
        matrizPonto(1,0) = this->pontos[i]->y;
        matrizPonto(2,0) = this->pontos[i]->z;
        matrizPonto(3,0) = this->pontos[i]->w;
        //std::cout << "matriz ponto antes" << endl;
        //matrizPonto.imprimir();
        matrizPonto = composta * matrizPonto;

        this->pontos[i]->x = matrizPonto(0,0);
        this->pontos[i]->y = matrizPonto(1,0);
        this->pontos[i]->z = matrizPonto(2,0);
        this->pontos[i]->w = matrizPonto(3,0);
        //std::cout << "matriz ponto depois" << endl;
        //matrizPonto.imprimir();
    }
}

void Objeto::transformarPontosWin(Matriz composta){ //exatamente igual à acima, apenas para as
    //coordenadas virtuais.
    //std::cout << "composta"<<endl;
    //composta.imprimir();
    for (int i = 0; i < this->pontos.length(); ++i) {
        Matriz matrizPonto(3,1);
        matrizPonto(0,0) = this->pontos[i]->xWin;
        matrizPonto(1,0) = this->pontos[i]->yWin;
        matrizPonto(2,0) = this->pontos[i]->wWin;
        //std::cout << "matriz ponto antes" << endl;
        //matrizPonto.imprimir();
        matrizPonto = composta * matrizPonto;

        this->pontos[i]->xWin = matrizPonto(0,0);
        this->pontos[i]->yWin = matrizPonto(1,0);
        this->pontos[i]->wWin = matrizPonto(2,0);
        //std::cout << "matriz ponto depois" << endl;
        //matrizPonto.imprimir();
    }
}
void Objeto::   alinharPontosWin(Matriz composta){ //exatamente igual à acima, apenas para as
    //coordenadas virtuais.
    //std::cout << "composta"<<endl;
    //composta.imprimir();
    for (int i = 0; i < this->pontos.length(); ++i) {
        Matriz matrizPonto(4,1);
        matrizPonto(0,0) = this->pontos[i]->xWin;
        matrizPonto(1,0) = this->pontos[i]->yWin;
        matrizPonto(2,0) = this->pontos[i]->zWin;
        matrizPonto(3,0) = this->pontos[i]->wWin;
        //std::cout << "matriz ponto antes" << endl;
        //matrizPonto.imprimir();
        matrizPonto = composta * matrizPonto;

        if (matrizPonto(3,0) != 0) {
            this->pontos[i]->xWin = matrizPonto(0,0) /= matrizPonto(3,0);
            this->pontos[i]->yWin = matrizPonto(1,0) /= matrizPonto(3,0);
            this->pontos[i]->zWin = matrizPonto(2,0);
            this->pontos[i]->wWin = matrizPonto(3,0) /= matrizPonto(3,0);
         } else {
             // Opcional: Tratar o caso para evitar que NaN seja propagado
             this->pontos[i]->xWin = 0;
             this->pontos[i]->yWin = 0;
             this->pontos[i]->zWin = 0;
             this->pontos[i]->wWin = 1;
         }

        //std::cout << "matriz ponto depois" << endl;
        //matrizPonto.imprimir();
    }
}
void Objeto::ajustarSCN(){
    for(Ponto *p : this->pontos){
        p->xWin = p->x;
        p->yWin = p->y;
        p->zWin = p->z;
        p->wWin = 1;
    }
}

Objeto::~Objeto() {
    // Libera a memória dos pontos e arestas gerenciados
    qDeleteAll(pontos);
    qDeleteAll(arestas);
}
