#include "frameprincipal.h"

FramePrincipal::FramePrincipal(QWidget *parent)
    : QFrame{parent}
{
    df.gerarObjetos();
    //ponteiro para window no displayfile, mais facil de realizar as manipulações
    this->window = dynamic_cast<Window*>(df.displayFile[0]);
    this->isPerspectiva = false;
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
    painter.setPen(QPen(Qt::blue,1));

    //desenhando a viewport
    for(Aresta* aresta: window->arestas){
        painter.drawLine(aresta->a->xWin, aresta->a->yWin, aresta->b->xWin, aresta->b->yWin);
    }

    for (Objeto *obj : df.displayFile) {
        for (Aresta *aresta : obj->arestas) {
            if(aresta->desenha){
                painter.drawLine(aresta->a->xWin, aresta->a->yWin, aresta->b->xWin, aresta->b->yWin);
            }
        }
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

    Matriz composta(4, 4);
    composta = Matriz::gerarIdentidade(4, 4);
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

    pipeline();
}
void FramePrincipal::ajustarPosicionamento(){
    // Função para ajustes dos objetos na cena
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
    // "Cópia" das coordenadas
    for(Objeto* obj : this->df.displayFile){
        obj->ajustarSCN();
    }

    // Define o ponto central a depender do tipo de projeção
    Ponto centro;
    if(this->isPerspectiva){
        centro = *window->COP;
    }else{
        centro = *window->VRP;
    }
    // Decomposição dos ângulos para obtenção dos valores
    auto [anguloEixoX, anguloEixoY, anguloEixoZ] = calcularAngulos(*window->VPN,*window->viewUp,centro);

    Matriz projecao(4,4);
    projecao = Matriz::gerarIdentidade(4,4);
    projecao = Matriz::translacao(-centro.x,-centro.y,-centro.z) * projecao;
    projecao = Matriz::rotacaoY(-anguloEixoY) * projecao;
    projecao = Matriz::rotacaoX(anguloEixoX) * projecao;
    projecao = Matriz::rotacaoZ(anguloEixoZ) * projecao;

    if(this->isPerspectiva){
        projecao = Matriz::perspectiva(window->getDistanciaFocal()) * projecao;
    }

    projecao = Matriz::escalonamento(2/window->getLargura(),2/window->getAltura(),2/window->getProfundidade())  * projecao;
    df.alinhamento(projecao);
    df.aplicarClipping(this->isPerspectiva);

    // transformada de VP
    Matriz visualizacao(3,3);
    visualizacao = Matriz::gerarIdentidade(3,3);
    visualizacao = Matriz::translacao2D(1,1) * visualizacao;
    visualizacao = Matriz::escalonamento2D(0.5,0.5)* visualizacao;
    visualizacao = Matriz::escalonamento2D(1,-1) * visualizacao;
    visualizacao = Matriz::translacao2D(0,1) * visualizacao;
    visualizacao = Matriz::escalonamento2D(LARGURA_VP,ALTURA_VP) * visualizacao;

    //translacao para o centro da vp [visualizar o clipping]
    visualizacao = Matriz::translacao2D(20,20) *visualizacao;

    df.transformada(visualizacao);

    update();
}

std::tuple<double, double, double> FramePrincipal::calcularAngulos(Ponto ponto, Ponto viewUp,Ponto centro){

    // Mesma estratégia utilizada no cálculo do viewUp em 2D, com adicional da decomposição dos ângulos
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
