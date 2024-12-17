#include "window.h"

Window::Window(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas) : Objeto(nome,pontos,arestas){
    Ponto *VRP = new Ponto((pontos[0]->x + pontos[2]->x,)/2,
                      (pontos[0]->y + pontos[2]->y)/2, (pontos[0]->z + pontos[2]->z)/2);
    this->pontos.append(VRP);
    this->VRP = VRP;

    Ponto *VPN = new Ponto(this->VRP->x,this->VRP->y,this->VRP->z + 1);
    this->pontos.append(VPN);
    this->VPN = VPN;
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
    this->pontos.removeOne(VRP);  // Remove centro(VRP) de pontos
    this->pontos.removeOne(VPN); // Remove VPN de pontos
    delete VRP;  // Libera o centro(VRP)
    delete VPN;  // Libera o VPN
}
