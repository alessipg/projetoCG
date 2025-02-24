#include "window.h"

Window::Window(QString nome, QList<Ponto*> pontos, QList<Aresta*> arestas) : Objeto(nome,pontos,arestas){
    Ponto *centro = new Ponto((pontos[0]->x + pontos[2]->x)/2,
                      (pontos[0]->y + pontos[2]->y)/2,0);
    this->pontos.append(centro);
    this->VRP = centro;

    //Direcao em que a window está virada
    Ponto *VPN = new Ponto((pontos[0]->x + pontos[2]->x)/2,
                        (pontos[0]->y + pontos[2]->y)/2,1);
    this->pontos.append(VPN);
    this->VPN = VPN;

    //Centro de projeção (45º)
    Ponto *COP = new Ponto((pontos[0]->x + pontos[2]->x)/2,
                           (pontos[0]->y + pontos[2]->y)/2,-225);
    this->pontos.append(COP);
    this->COP = COP;

    Ponto *viewUp = new Ponto(this->VRP->x,this->VRP->y+1,0);
    this->pontos.append(viewUp);
    this->viewUp = viewUp;
    this->medio = VRP;

    // zmin: Ponto base com o mesmo valor de VRP
    this->zmin = new Ponto(this->VRP->x, this->VRP->y, this->VRP->z - 1000);

    // zmax: Ponto com z ajustado
    this->zmax = new Ponto(this->VRP->x, this->VRP->y, this->VRP->z + 1000);

    this->pontos.append(this->zmin);
    this->pontos.append(this->zmax);
}
/*
 * 3---------------------2              |
 * |          |          |              |
 * |          |          |              |
 * |          5          |              |       225
 * |----------4----------|450       VPN-|-----------------COP
 * |          |          |              |
 * |          |          |              |
 * |          |          |              |
 * 0---------------------1              |
 *           500
 */
float Window::getLargura(){
    return sqrt(pow(this->pontos[1]->x-this->pontos[0]->x,2) +
                pow(this->pontos[1]->y-this->pontos[0]->y,2) +
                pow(this->pontos[1]->z-this->pontos[0]->z,2));
}
float Window::getAltura(){
    return sqrt(pow(this->pontos[3]->x-this->pontos[0]->x,2) +
                pow(this->pontos[3]->y-this->pontos[0]->y,2) +
                pow(this->pontos[3]->z-this->pontos[0]->z,2));

}
float Window::getProfundidade() {
    return sqrt(pow(this->zmax->x - this->zmin->x, 2) +
                pow(this->zmax->y - this->zmin->y, 2) +
                pow(this->zmax->z - this->zmin->z, 2));
}
float Window::getDistanciaFocal() {
    return sqrt(pow(this->VRP->x - this->COP->x, 2) +
                pow(this->VRP->y - this->COP->y, 2) +
                pow(this->VRP->z - this->COP->z, 2));
}
Window::~Window() {
    this->pontos.removeOne(VRP);
    this->pontos.removeOne(viewUp);
    delete VRP;
    delete viewUp;
    delete COP;
    delete zmin;
    delete zmax;
    delete medio;

}
