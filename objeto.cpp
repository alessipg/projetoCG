// Classe Objeto
#include "objeto.h"

Objeto::Objeto(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas) :
    nome(nome), pontos(pontos), arestas(arestas) {}



void Objeto::transformarPontos(Matriz composta){

    //std::cout << "composta"<<endl;
    //composta.imprimir();
    for (int i = 0; i < this->pontos.length(); ++i) {

        Matriz matrizPonto(3,1);
        matrizPonto(0,0) = this->pontos[i]->x;
        matrizPonto(1,0) = this->pontos[i]->y;
        matrizPonto(2,0) = this->pontos[i]->z;
        matrizPonto(3,0) = this->pontos[i]->coordW;
        // std::cout << "matriz ponto antes" << endl;
        // matrizPonto.imprimir();
        matrizPonto = composta * matrizPonto;

        this->pontos[i]->x = matrizPonto(0,0);
        this->pontos[i]->y = matrizPonto(1,0);
        this->pontos[i]->z = matrizPonto(2,0);
        this->pontos[i]->coordW = matrizPonto(3,0);
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
        matrizPonto(2,0) = this->pontos[i]->zWin;
        matrizPonto(3,0) = this->pontos[i]->coordWWin;
        //std::cout << "matriz ponto antes" << endl;
        //matrizPonto.imprimir();
        matrizPonto = composta * matrizPonto;

        this->pontos[i]->xWin = matrizPonto(0,0);
        this->pontos[i]->yWin = matrizPonto(1,0);
        this->pontos[i]->zWin = matrizPonto(2,0);
        this->pontos[i]->coordWWin = matrizPonto(3,0);
        //std::cout << "matriz ponto depois" << endl;
        //matrizPonto.imprimir();
    }
}
void Objeto::ajustarSNC(){
    for(Ponto *p : this->pontos){
        p->xWin = p->x;
        p->yWin = p->y;
        p->zWin = p->z;

    }
}
void Objeto::clipping(float xmin,float xmax, float ymin, float ymax){
    //orientacoes iguais ao dos slides
    //rc[0] cima
    //rc[1] baixo
    //rc[2] direita
    //rc[3] esquerda
    for(Ponto* p : this->pontos){
        //set rc
        if(p->xWin>xmax)
            p->rc[0]=true;
        else if(p->xWin<xmin)
            p->rc[1]=true;
        if(p->yWin>ymax)
            p->rc[2]=true;
        else if(p->yWin<ymin)
            p->rc[3]=true;
    }
    for (Aresta* a :this->arestas){
        a->desenha = 0;//PAREI AQUI, LIMPA MAS N VOLTA
        for(int i = 0;i<4;i++){
            a->desenha+=a->a->rc[i]&&a->b->rc[i];
        }
    }

}

Objeto::~Objeto() {
    // Libera a memória dos pontos e arestas gerenciados
    qDeleteAll(pontos);
    qDeleteAll(arestas);
}
