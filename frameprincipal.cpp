#include "frameprincipal.h"
#include <iostream>
#include <math.h>


FramePrincipal::FramePrincipal(QWidget *parent)
    : QFrame{parent}
{
    df.gerarObjetos();
    //ponteiro para window no displayfile, mais facil de realizar as manipulações
    this->window = dynamic_cast<Window*>(df.displayFile[0]);
    this->isPerspectiva = false;
    this->objAtual = this->window;
    this->objCentro = this->window;
    ajustarPosicionamento();
    this->objAtual = this->window;
    this->objCentro = this->getObjetoByName("Charizard");
    //chamada necessária após toda transformação
    pipeline();
}

Objeto* FramePrincipal::getObjetoByName(const QString& nome) {
    for (Objeto* obj : df.displayFile) {
        if (obj->nome == nome) {
            return obj;
        }
    }
    return nullptr;
}

void FramePrincipal::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::cyan,1));

    //desenhando a viewport
    for(Aresta* aresta: window->arestas){
        painter.drawLine(aresta->a->xWin, aresta->a->yWin, aresta->b->xWin, aresta->b->yWin);
    }

    for (Objeto *obj : df.displayFile) {
        //if (obj->nome == objetoAlvo) {
            for (Aresta *aresta : obj->arestas) {
                if(aresta->desenha){
                    //qDebug() <<aresta->desenha<< "a " << aresta->a->xWin <<aresta->a->yWin << "b"<<aresta->b->xWin<< aresta->b->yWin;
                    painter.drawLine(aresta->a->xWin, aresta->a->yWin, aresta->b->xWin, aresta->b->yWin);
                }
            }
            //break;
        //}
    }
}

void FramePrincipal::transformarObjeto(char op,double v1, double v2, double v3, char eixo, char centro) {

    if (eixo == 0) {
        switch(centro){
            case 'S':
                this->objCentro = this->objAtual;
                break;
            case 'P':
                this->objCentro = getObjetoByName("Porygon");
                break;
            case 'C':
                this->objCentro = getObjetoByName("Charizard");
                break;
            default:
                return;
        }
    }

    std::cout<<this->objAtual->nome.toStdString()<<" "<<this->objCentro->nome.toStdString()<<endl;
    Matriz composta(4, 4);
    composta = Matriz::gerarIdentidade(4, 4);
    // Move o objeto para a origem para realizar transformações
    composta = Matriz::translacao(
                   -this->objCentro->medio->x,
                   -this->objCentro->medio->y,
                   -this->objCentro->medio->z
                   ) * composta;

    float translacaoX = 0;
    float translacaoY = 0;
    float translacaoZ = 0;

    if (op == 'T') {  // Translação
        translacaoX += v1;
        translacaoY += v2;
        translacaoZ += v3;

    } else if (op == 'E') {  // Escala
        composta = Matriz::escalonamento(v1, v2, v3) * composta;

    } else if (op == 'R') {  // Rotação
        if (eixo == 'X') {
            composta = Matriz::rotacaoX(v1) * composta;
        } else if (eixo == 'Y') {
            composta = Matriz::rotacaoY(v1) * composta;
        } else if (eixo == 'Z') {
            composta = Matriz::rotacaoZ(v1) * composta;
        }
    }

    // Retorna o ponto original + translações solicitadas
    composta = Matriz::translacao(
                   this->objCentro->medio->x + translacaoX,
                   this->objCentro->medio->y + translacaoY,
                   this->objCentro->medio->z + translacaoZ
                   ) * composta;

    // Aplica as alterações às coordenadas do objeto
    this->objAtual->transformarPontos(composta);

    // Chama a transformada de viewport
    pipeline();
}
void FramePrincipal::ajustarPosicionamento(){
    objAtual = getObjetoByName("Charizard");
    transformarObjeto('T',180,100,200,0,'S');
    transformarObjeto('E',10,10,10,0,'S');
    transformarObjeto('R',180,0,0,'Y','S');

    objAtual = getObjetoByName("Porygon");
    transformarObjeto('T',380,30,200,0,'S');
    transformarObjeto('E',1.3,1.3,1.3,0,'S');
    transformarObjeto('R',180,0,0,'Y','S');
}

void FramePrincipal::pipeline(){

    for(Objeto* obj : this->df.displayFile){
        obj->ajustarSCN();
    }
    Ponto centro;
    if(this->isPerspectiva){
        centro = *window->COP;
    }else{
        centro = *window->VRP;
    }
    auto [anguloEixoX, anguloEixoY, anguloEixoZ] = calcularAngulos(*window->VPN,*window->viewUp,centro);

    Matriz composta(4,4);
    composta = Matriz::gerarIdentidade(4,4);
    composta = Matriz::translacao(-centro.x,-centro.y,-centro.z) * composta;
    composta = Matriz::rotacaoY(-anguloEixoY) * composta;
    composta = Matriz::rotacaoX(anguloEixoX) * composta;
    composta = Matriz::rotacaoZ(anguloEixoZ) * composta;
    if(this->isPerspectiva){
        composta = Matriz::perspectiva(window->getDistanciaFocal()) * composta;
    }
    composta = Matriz::escalonamento(2/window->getLargura(),2/window->getAltura(),2/window->getProfundidade())  * composta;
    df.alinhamento(composta);
    df.aplicarClipping(this->isPerspectiva);
    // transformada de VP
    Matriz composta2(3,3);
    composta2 = Matriz::gerarIdentidade(3,3);
    composta2 = Matriz::translacao2D(1,1) * composta2;
    composta2 = Matriz::escalonamento2D(0.5,0.5)* composta2;
    composta2 = Matriz::escalonamento2D(1,-1) * composta2;
    composta2 = Matriz::translacao2D(0,1) * composta2;
    composta2 = Matriz::escalonamento2D(LARGURA_VP,ALTURA_VP) * composta2;

    //translacao para o centro da vp [visualizar o clipping]
    composta2 = Matriz::translacao2D(20,20) *composta2;

    df.transformada(composta2);

    update();
}

std::tuple<double, double, double> FramePrincipal::calcularAngulos(Ponto ponto, Ponto viewUp,Ponto centro){

    Ponto *vpn = new Ponto(ponto.xWin-centro.xWin, ponto.yWin-centro.yWin, ponto.zWin-centro.zWin);
    Ponto *vUp = new Ponto(viewUp.xWin-centro.xWin, viewUp.yWin-centro.yWin, viewUp.zWin-centro.zWin);
    Objeto obj;
    obj.pontos.append(vpn);
    obj.pontos.append(vUp);
    obj.ajustarSCN();
    double anguloXZ = atan2(vpn->xWin, vpn->zWin) * 180.0 / M_PI;
    if (anguloXZ < 0) {
        anguloXZ += 360.0;
    }
    Matriz composta = Matriz::rotacaoY(-anguloXZ) * Matriz::gerarIdentidade(4,4);
    obj.alinharPontosWin(composta);
    double anguloYZ = atan2(vpn->yWin, vpn->zWin) * 180.0 / M_PI;

    // Ajusta o ângulo para o intervalo [0, 360]
    if (anguloYZ < 0) {
        anguloYZ += 360.0;
    }
    composta = Matriz::rotacaoX(anguloYZ) * Matriz::gerarIdentidade(4,4);
    obj.alinharPontosWin(composta);
    double anguloXY = atan2(vUp->xWin, vUp->yWin) * 180.0 / M_PI;

    // Ajusta o ângulo para o intervalo [0, 360]
    if (anguloXY < 0) {
        anguloXY += 360.0;
    }
    composta = Matriz::rotacaoZ(anguloXY) * Matriz::gerarIdentidade(4,4);
    obj.alinharPontosWin(composta);
    return {anguloYZ,anguloXZ,anguloXY};
}
