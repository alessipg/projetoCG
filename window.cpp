#include "window.h"

Window::Window(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas) : Objeto(nome,pontos,arestas){
    Ponto *centro = new Ponto((pontos[0]->x + pontos[2]->x)/2,
                      (pontos[0]->y + pontos[2]->y)/2);
    this->pontos.append(centro);
    this->centro = centro;

    Ponto *viewUp = new Ponto(this->centro->x,this->centro->y+1);
    this->pontos.append(viewUp);
    this->viewUp = viewUp;
    altura = pontos[1]->y - pontos[0]->y;
    largura = pontos[2]->x - pontos[1]->x;
}
/*
 * 3---------------------2
 * |          |          |
 * |          |          |
 * |          5          |
 * |----------4----------| 450
 * |          |          |
 * |          |          |
 * |          |          |
 * 0---------------------1
 *           500
 */
float Window::getLargura(){
    return sqrt(pow(this->pontos[1]->x-this->pontos[0]->x,2)
                +pow(this->pontos[1]->y-this->pontos[0]->y,2));
}
float Window::getAltura(){
    return sqrt(pow(this->pontos[3]->x-this->pontos[0]->x,2)
                +pow(this->pontos[3]->y-this->pontos[0]->y,2));

}
Window::~Window() {
    this->pontos.removeOne(centro);  // Remove centro de pontos
    this->pontos.removeOne(viewUp); // Remove viewUp de pontos
    delete centro;  // Libera o centro
    delete viewUp;  // Libera o viewUp
}
