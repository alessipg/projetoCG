#include "frameprincipal.h"
#include <iostream>
#include <cmath>
#include <mainwindow.h>

FramePrincipal::FramePrincipal(QWidget *parent)
    : QFrame{parent}
{
    df.gerarObjetos();
    this->objAtual = nullptr;
    this->isWindow = false;
    //ponteiro para window no displayfile, mais facil de realizar as manipulações
    this->window = dynamic_cast<Window*>(df.displayFile[0]);
    //chamada necessária após toda transformação
    pipeline();
}
/*********************************************************************************************
 *              PIPELINE DE VISUALIZAÇÃO
 *  1.TRANSFORMAÇÃO DE OBJETOS COM COORDENADAS DE MUNDO
 *  2.ROTINA WINDOW
 *  2.1.COPIA COORDENADAS DE MUNDO PARA WIN (ATRIBUTOS CLASSE PONTO)
 *  2.2.GERA MATRIZ DE TRANSLAÇÃO E ROTAÇÃO PARA AJUSTE DA WINDOW COM O CARTESIANO
 *  2.3.APLICA NAS COORDENADAS WIN
 *  2.4.APLICA CLIPPING DE LINHAS (NÃO FUNCIONA PARA POLIGONOS, CASO A SE TRATAR DEPOIS DO 3D
 *      E PROVAVELMENTE TEREMOS QUE COMEÇAR A GERAR MAIS OBJETOS COM HERANÇA, VISTO QUE O CLIPPING
 *      DE LINHAS ESTÁ NA CLASSE ARESTA)
 *  2.5.ESCALA E TRANSLAÇÃO DE ACORDO COM A VIEWPORT
 *  3.ATUALIZAÇÃO DO WIDGET
 ********************************************************************************************/

Objeto* FramePrincipal::getObjetoByName(const QString& nome) {
    for (Objeto* obj : df.displayFile) {  // `objetos` é uma lista com todos os objetos da cena
        if (obj->nome == nome) {
            return obj;
        }
    }
    return nullptr;  // Retorna nullptr se não encontrar
}
/*Esse método funciona para qualquer objeto, basta ter
 * todas as arestas definidas. Pensei em tratar, por exemplo, o caso do quadrado
 * adicionando 2 construtores: 1 recebendo os 4 pontos e o outro transformando os
 * 2 pontos recebidos em 4, já que teria que calcular toda vez que fosse desenhado.
*/
void FramePrincipal::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);

/*  Com a transformada não precisa mais inverter o eixo Y, isso porque inverti o valor Y no
 *  escalonamento (não encontrei em lugar nenhum a afirmação disso ser correto), então vou
 *  manter o código aqui para caso isso atrapalhe eventualmente
 */
    //painter.translate(0, height()); // Move o ponto de origem para o canto inferior esquerdo
    //painter.scale(1, -1);           // Inverte o eixo Y
    painter.setPen(QPen(Qt::red,1));

    //desenhando window para ver se as alterações estão corretas
    for(Aresta* aresta: window->arestas){
        painter.drawLine(aresta->a->xWin, aresta->a->yWin, aresta->b->xWin, aresta->b->yWin);
        //qDebug() << "a " << aresta->a->x <<aresta->a->y << "b"<<aresta->b->x<< aresta->b->y;
    }

    for (Objeto *obj : df.displayFile) {
        if (obj->nome == objetoAlvo) {
            for (Aresta *aresta : obj->arestas) {
                if(aresta->desenha){
                    //qDebug() <<aresta->desenha<< "a " << aresta->a->xWin <<aresta->a->yWin << "b"<<aresta->b->xWin<< aresta->b->yWin;
                    painter.drawLine(aresta->a->xWin, aresta->a->yWin, aresta->b->xWin, aresta->b->yWin);
                }
            }
            this->objAtual = obj;
            break;
        }
    }
}


void FramePrincipal::desenharObjeto(const QString &buttonText) {
    qDebug().noquote() << "Desenhando objeto:" << buttonText;
    // armazena o nome do obj que será desenhado
    objetoAlvo = buttonText;
    pipeline();

}

void FramePrincipal::transformarObjeto(char op,double v1, double v2, double v3, char eixo) {
    // Se a checkbox está marcada, alteramos o objeto a ser transformado para a janela
    if (isWindow) {
        objAtual = window;
    }
    if (!objAtual) {
        qDebug() << "Sem objeto instanciado na cena";
        return;
    }
    Matriz composta(4, 4);
    composta = Matriz::gerarIdentidade(4, 4);

    // Move o objeto para a origem para realizar transformações
    composta = Matriz::translacao(
                   -this->objAtual->medio->x,
                   -this->objAtual->medio->y,
                   -this->objAtual->medio->z
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
                   this->objAtual->medio->x + translacaoX,
                   this->objAtual->medio->y + translacaoY,
                   this->objAtual->medio->z + translacaoZ
                   ) * composta;

    // Aplica as alterações às coordenadas do objeto
    this->objAtual->transformarPontos(composta);

    // Chama a transformada de viewport
    pipeline();    
}

void FramePrincipal::pipeline(){

    for(Objeto* obj : this->df.displayFile){
        obj->ajustarSCN();
    }
    // Calcular ângulos X, Y e Z
    auto [anguloEixoX, anguloEixoY, anguloEixoZ] = calcularAngulos(*window->VPN,*window->viewUp);

    Matriz composta(4,4);
    composta = Matriz::gerarIdentidade(4,4);
    composta = Matriz::translacao(-window->VRP->x,-window->VRP->y,-window->VRP->z) * composta;
    composta = Matriz::rotacaoY(-anguloEixoY) * composta;
    composta = Matriz::rotacaoX(anguloEixoX) * composta;
    composta = Matriz::rotacaoZ(anguloEixoZ) * composta;
    //composta.imprimir();
    //precisa alinhar a window com os eixos para o clipping
    //composta = Matriz::escalonamento(2/window->getLargura(),2/window->getAltura(),1)  * Matriz::gerarIdentidade(4,4);
    df.alinhamento(composta);
    //a partir daqui ignora-se o eixo Z
    df.aplicarClipping();
    // transformada de VP
    Matriz composta2(3,3);
    composta2 = Matriz::gerarIdentidade(3,3);
    composta2 = Matriz::escalonamento2D(2/window->getLargura(),2/window->getAltura())  * composta2;
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

std::tuple<double, double, double> FramePrincipal::calcularAngulos(Ponto ponto, Ponto viewUp){

    Ponto *vpn = new Ponto(ponto.xWin-window->VRP->xWin, ponto.yWin-window->VRP->yWin, ponto.zWin-window->VRP->zWin);
    Ponto *vUp = new Ponto(viewUp.xWin-window->VRP->xWin, viewUp.yWin-window->VRP->yWin, viewUp.zWin-window->VRP->zWin);
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




