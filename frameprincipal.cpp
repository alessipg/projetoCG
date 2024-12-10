#include "frameprincipal.h"
#include <iostream>
#include <math.h>
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
    rotinaWindow();
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
    painter.setPen(QPen(Qt::red, 2));

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
    rotinaWindow();

}

void FramePrincipal::transformarObjeto(const QString &inputText) {
    if(!objAtual){
        qDebug() <<"sem objeto instanciado na cena";
        return;
    }

    //qDebug().noquote() << "Input:" << inputText;

    static QRegularExpression pattern(R"((\w)\s(-?\d+(\.\d+)?),(-?\d+(\.\d+)?)(?:\s(-?\d+(\.\d+)?))?)");
    QStringList lines = inputText.split('\n');
    std::reverse(lines.begin(), lines.end()); // Inverte a ordem das linhas

    Matriz composta(3, 3);
    composta = Matriz::gerarIdentidade(3,3);
    // se a checkbox está marcada, alteramos o obj a ser transformado para window
    if(isWindow){
        objAtual=window;
        //qDebug()<<objAtual->nome;
    }
    //dx e dy devem ser as coordenadas do ponto (?)
    composta = composta * Matriz::translacao(-this->objAtual->pontos[0]->x, -this->objAtual->pontos[0]->y);
    //composta.imprimir();

    float translacaoX = 0;
    float translacaoY = 0;

    for (const QString &line : lines) {
        QRegularExpressionMatch match = pattern.match(line);

        if (match.hasMatch()) {
            QString op = match.captured(1);      // Operação (ex: "R", "T", "E")
            float v1 = match.captured(2).toFloat(); // Primeiro valor (ex: "1.5")
            float v2 = match.captured(4).toFloat(); // Segundo valor (ex: "2.3")
            float angulo = match.captured(6).isEmpty() ? 0 : match.captured(6).toFloat(); // Ângulo (opcional)
            //qDebug().noquote() << op << v1 << v2 << angulo;

            if (op == "R") {
                composta = Matriz::rotacao(Ponto(v1, v2), angulo) * composta;
                //std::cout << "rotacao"<<endl;
                //composta.imprimir();
            } else if (op == "T") {
                /*composta = Matriz::translacao(v1, v2) * composta;*/
                translacaoX += v1;
                translacaoY += v2;
                //std::cout << "translacao"<<endl;
                //composta.imprimir();
            } else if (op == "E") {
                composta =Matriz::escalonamento(v1, v2)* composta;
                //std::cout << "escala"<<endl;
                //composta.imprimir();
            } else {
                qDebug() << "Operação desconhecida:" << op;
            }
        } else {
            qDebug() << "A string de entrada não corresponde ao formato esperado.";
        }
    }
    //retorna ponto original+translacoes solicitadas
    composta = Matriz::translacao(this->objAtual->pontos[0]->x+translacaoX,
                                  this->objAtual->pontos[0]->y+translacaoY) * composta;
    // aplica alterações em coordenadas de mundo
    this->objAtual->transformarPontos(composta);
    // chama a transformada de VP
    rotinaWindow();

    //update(); // Atualiza o widget
}

void FramePrincipal::rotinaWindow(){

    /*  Método de geração de composta com base na matriz da apostila da USP
     */


    for(Objeto* obj : this->df.displayFile){
        obj->ajustarSNC();
    }
    //angulo (viewUp,Y)
    double angulo = anguloViewUp();

    // Normalização
    Matriz composta(3,3);
    composta = Matriz::gerarIdentidade(3,3);
    composta = Matriz::translacao(-window->centro->x,-window->centro->y) * composta;
    composta = Matriz::rotacao(*window->centro,angulo) * composta;
    //precisa alinhar a window com os eixos para o clipping

    //aplicar SCN
    composta = Matriz::escalonamento(2/window->getLargura(),2/window->getAltura())  * composta;

    df.transformada(composta);

    df.aplicarClipping();
    // transformada de VP
    Matriz composta2(3,3);
    composta2 = Matriz::gerarIdentidade(3,3);
    composta2 = Matriz::translacao(1,1) * composta2;
    composta2 = Matriz::escalonamento(0.5,0.5)* composta2;
    composta2 = Matriz::escalonamento(1,-1) * composta2;
    composta2 = Matriz::translacao(0,1) * composta2;
    composta2 = Matriz::escalonamento(LARGURA_VP,ALTURA_VP) * composta2;

    //translacao para o centro da vp [visualizar o clipping]
    composta2 = Matriz::translacao(20,20) *composta2;

    df.transformada(composta2);

    update();
}

double FramePrincipal::anguloViewUp() {
    // Coleta as coordenadas do centro da janela
    double centroX = window->centro->x;
    double centroY = window->centro->y;

    // Coleta as coordenadas de viewUp
    double viewUpX = window->viewUp->x;
    double viewUpY = window->viewUp->y;

    // Calcula o vetor de deslocamento (viewUp - centro)
    double dx = viewUpX - centroX;
    double dy = viewUpY - centroY;

    // Usa atan2 para calcular o ângulo em relação ao eixo Y
    double angulo = atan2(dx, dy) * 180.0 / M_PI;

    // Ajusta o ângulo para o intervalo [0, 360]
    if (angulo < 0) {
        angulo += 360.0;
    }

    return angulo;
}
