#include "frameprincipal.h"
#include <iostream>
#include <math.h>
#include <mainwindow.h>
FramePrincipal::FramePrincipal(QWidget *parent)
    : QFrame{parent}
{
    df.gerarObjetos();
    this->setupWindow();
    this->rotinaWindow();
}

/*void processarEntrada(const QString &inputText) {
}*/

/*Esse método funciona para qualquer objeto, basta ter
 * todas as arestas definidas. Pensei em tratar, por exemplo, o caso do quadrado
 * adicionando 2 construtores: 1 recebendo os 4 pontos e o outro transformando os
 * 2 pontos recebidos em 4, já que teria que calcular toda vez que fosse desenhado.
*/
void FramePrincipal::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);

    //inverte o eixo Y
    painter.translate(0, height()); // Move o ponto de origem para o canto inferior esquerdo
    std::cout << "HEIGHT = "<<height() << endl;
    painter.scale(1, -1);           // Inverte o eixo Y
    painter.setPen(QPen(Qt::red, 2));

    for (Objeto &obj : df.displayFile) {
        if (obj.nome == objetoAlvo) {
            for (Aresta aresta : obj.arestas) {
                painter.drawLine(aresta.a->xWin, aresta.a->yWin, aresta.b->xWin, aresta.b->yWin);
                //qDebug() << "a " << aresta.a->x <<aresta.a->y << "b"<<aresta.b->x<< aresta.b->y;
            }
            this->objAtual = &obj;
            break;
        }
    }
}


void FramePrincipal::desenharObjeto(const QString &buttonText) {
    qDebug().noquote() << "Desenhando objeto:" << buttonText;
    // armazena o nome do obj que será desenhado
    objetoAlvo = buttonText;
    update();

}

void FramePrincipal::transformarObjeto(const QString &inputText) {

    qDebug().noquote() << "Input:" << inputText;

    static QRegularExpression pattern(R"((\w)\s(-?\d+(\.\d+)?),(-?\d+(\.\d+)?)(?:\s(-?\d+(\.\d+)?))?)");
    QStringList lines = inputText.split('\n');
    std::reverse(lines.begin(), lines.end()); // Inverte a ordem das linhas

    Matriz composta(3, 3);
    composta = Matriz::gerarIdentidade(3,3);

    //dx e dy devem ser as coordenadas do ponto (?)
    composta = composta * Matriz::translacao(-this->objAtual->pontos[0].x, -this->objAtual->pontos[0].y);
    //composta.imprimir();

    std::vector<std::pair<float, float>> translacoes;

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
                std::cout << "rotaçao"<<endl;
                composta.imprimir();
            } else if (op == "T") {
                /*composta = Matriz::translacao(v1, v2) * composta;*/
                translacoes.emplace_back(v1,v2);
                std::cout << "translacao"<<endl;
                composta.imprimir();
            } else if (op == "E") {
                composta =Matriz::escalonamento(v1, v2)* composta;
                std::cout << "escala"<<endl;
                composta.imprimir();
            } else {
                qDebug() << "Operação desconhecida:" << op;
            }
        } else {
            qDebug() << "A string de entrada não corresponde ao formato esperado.";
        }
    }

    composta = Matriz::translacao(this->objAtual->pontos[0].x, this->objAtual->pontos[0].y) * composta;

    for (int i = 0; i < translacoes.size(); ++i) {
        composta = Matriz::translacao(translacoes[i].first, translacoes[i].second) * composta;
    }

    this->objAtual->transformarPontos(composta);

    this->rotinaAtualizacaoWindow();

    update(); // Atualiza o widget
}

void FramePrincipal::transformarWindow(const QString &inputText) {

    qDebug().noquote() << "Input:" << inputText;

    static QRegularExpression pattern(R"((\w)\s(-?\d+(\.\d+)?),(-?\d+(\.\d+)?)(?:\s(-?\d+(\.\d+)?))?)");
    QStringList lines = inputText.split('\n');
    std::reverse(lines.begin(), lines.end()); // Inverte a ordem das linhas

    Matriz composta(3, 3);
    composta = Matriz::gerarIdentidade(3,3);

    //dx e dy devem ser as coordenadas do ponto (?)
    composta = composta * Matriz::translacao(-window->centro.x, -window->centro.y);
    //composta.imprimir();

    std::vector<std::pair<float, float>> translacoes;

    for (const QString &line : lines) {
        QRegularExpressionMatch match = pattern.match(line);

        if (match.hasMatch()) {
            QString op = match.captured(1);      // Operação (ex: "R", "T", "E")
            float v1 = match.captured(2).toFloat(); // Primeiro valor (ex: "1.5")
            float v2 = match.captured(4).toFloat(); // Segundo valor (ex: "2.3")
            float angulo = match.captured(6).isEmpty() ? 0 : match.captured(6).toFloat(); // Ângulo (opcional)
            //qDebug().noquote() << op << v1 << v2 << angulo;

            if (op == "R") {
                composta = Matriz::rotacao(window->centro, angulo) * composta;
                std::cout << "rotaçao"<<endl;
                composta.imprimir();
            } else if (op == "T") {
                /*composta = Matriz::translacao(v1, v2) * composta;*/
                translacoes.emplace_back(v1,v2);
                std::cout << "translacao"<<endl;
                composta.imprimir();
            } else if (op == "E") {
                composta =Matriz::escalonamento(v1, v2)* composta;
                std::cout << "escala"<<endl;
                composta.imprimir();
            } else {
                qDebug() << "Operação desconhecida:" << op;
            }
        } else {
            qDebug() << "A string de entrada não corresponde ao formato esperado.";
        }
    }

    composta = Matriz::translacao(window->centro.x, window->centro.y) * composta;

    for (int i = 0; i < translacoes.size(); ++i) {
        composta = Matriz::translacao(translacoes[i].first, translacoes[i].second) * composta;
    }

    window->transformarPontos(composta);
    window->centro.x = (window->pontos[0].x + window->pontos[2].x)/2;
    window->centro.y = (window->pontos[0].y + window->pontos[2].y)/2;
    window->altura = window->pontos[1].y - window->pontos[0].y;
    window->largura = window->pontos[2].x - window->pontos[1].x;
    /*
    for(Ponto &pt : window->pontos){
        pt.xWin = pt.x;
        pt.yWin = pt.y;
    }

    */
    std::cout << "PONTO 0 x "<< window->pontos[0].x<< " e y "<< window->pontos[0].y<<endl;
    std::cout << "PONTO 2 x "<< window->pontos[2].x<< " e y "<< window->pontos[2].y<<endl;
    std::cout << "CENTRO x "<< window->centro.x<< " e y "<< window->centro.y<<endl;
    this->rotinaAtualizacaoWindow();

    update(); // Atualiza o widget
}

/* void FramePrincipal::transformarWindow(const QString &inputText) {

    qDebug().noquote() << "Input:" << inputText;

        static QRegularExpression pattern(R"((\w)\s(-?\d+(\.\d+)?),(-?\d+(\.\d+)?)(?:\s(-?\d+(\.\d+)?))?)");
        QStringList lines = inputText.split('\n');
        std::reverse(lines.begin(), lines.end()); // Inverte a ordem das linhas

        Matriz composta(3, 3);
        composta = Matriz::gerarIdentidade(3,3);



            //dx e dy devem ser as coordenadas do ponto (?)
            composta = composta * Matriz::translacao(-this->objAtual->pontos[0].xWin, -this->objAtual->pontos[0].yWin);
            //composta.imprimir();

            std::vector<std::pair<float, float>> translacoes;

            for (const QString &line : lines) {
                QRegularExpressionMatch match = pattern.match(line);

                if (match.hasMatch()) {
                    QString op = match.captured(1);      // Operação (ex: "R", "T", "E")
                    float v1 = match.captured(2).toFloat(); // Primeiro valor (ex: "1.5")
                    float v2 = match.captured(4).toFloat(); // Segundo valor (ex: "2.3")
                    float angulo = match.captured(6).isEmpty() ? 0 : -match.captured(6).toFloat(); // Ângulo (opcional)
                    //qDebug().noquote() << op << v1 << v2 << angulo;

                    if (op == "R") {
                        composta = Matriz::rotacao(Ponto(v1, v2), angulo) * composta;
                        std::cout << "rotaçao"<<endl;
                        composta.imprimir();
                    } else if (op == "T") {
                        //composta = Matriz::translacao(v1, v2) * composta;
                        translacoes.emplace_back(v1,v2);
                        std::cout << "translacao"<<endl;
                        composta.imprimir();
                    } else if (op == "E") {
                        composta =Matriz::escalonamento(v1, v2)* composta;
                        std::cout << "escala"<<endl;
                        composta.imprimir();
                    } else {
                        qDebug() << "Operação desconhecida:" << op;
                    }
                } else {
                    qDebug() << "A string de entrada não corresponde ao formato esperado.";
                }
            }

            composta = Matriz::translacao(this->objAtual->pontos[0].xWin, this->objAtual->pontos[0].yWin) * composta;

            for (int i = 0; i < translacoes.size(); ++i) {
                composta = Matriz::translacao(-translacoes[i].first, -translacoes[i].second) * composta;
            }

            this->objAtual->transformarPontos(composta);


    this->rotinaAtualizacaoWindow();

    update(); // Atualiza o widget
}
*/

void FramePrincipal::corrigirRotacaoWindow(Window *inputWindow){

    float vector1[2] = {(window->pontos[1].x+window->pontos[2].x)/2, (window->pontos[1].y+window->pontos[2].y)/2};
    float vector2[2] = {0,1};

    float dot = vector1[1];
    float mag = sqrt(vector1[0]*vector1[0]+vector1[1]*vector1[1]);
    float cosTheta = dot / mag;
    cosTheta = fmax(-1.0, fmin(1.0, cosTheta));
    float angle = acos(cosTheta)* 180 / M_PI;

    Matriz composta(3, 3);
    composta = Matriz::gerarIdentidade(3,3);
    //composta = Matriz::translacao(-(obj.pontos[0].x),-(obj.pontos[0].y)) * composta;  //Objetos devem girar em torno da window, não de si mesmos
    composta = Matriz::rotacao(window->centro,-angle) * composta;

    for (Objeto &obj : df.displayFile) {

        obj.transformarPontosWin(composta);
    }
}

void FramePrincipal::centralizarWindow(Window *inputWindow){

    Matriz matrizTransladadaWcParaOrigem(3,3);

    matrizTransladadaWcParaOrigem = Matriz::translacao(-window->centro.x,-window->centro.y);



    for (Objeto &obj : df.displayFile) {
        for(Ponto &pt : obj.pontos){ // ERRADO
            pt.xWin = pt.x;
            pt.yWin = pt.y;
        }
        obj.transformarPontosWin(matrizTransladadaWcParaOrigem);
    }
        window->centro =(0,0);

}

void FramePrincipal::escalonarPontos(){
    float newWidth = (window->largura)/2;
    float newHeight = (window->altura)/2;

    for (Objeto &obj : df.displayFile) {
        for(Ponto &pt : obj.pontos){
            pt.xWin = pt.xWin/newWidth;
            pt.yWin = pt.yWin/newHeight;
            std::cout << "ponto x e y escalonado"<< pt.xWin << " " << pt.yWin << endl;
        }
    }
}

void FramePrincipal::calcularCoordenadasViewPort(Window *inputWindow){

    for (Objeto &obj : df.displayFile) {
        for(Ponto &pt : obj.pontos){
            float Xvp = ((pt.xWin+1)/2)*(500);
            float Yvp = (1-(-(pt.yWin)+1)/2)*(400);
            pt.xWin = Xvp;
            pt.yWin = Yvp;
            //std::cout << "ALTURA E LARGURA"<< height() << " " << width() << endl;
            std::cout << "ponto x e y novos"<< pt.xWin << " " << pt.yWin << endl;
        }
    }
}

void FramePrincipal::setupWindow(){
    QList<Ponto> pontos{
        Ponto(-250,-200),
        Ponto(-250,200),
        Ponto(250,200),
        Ponto(250,-200)
    };

    QList<Aresta> arestas = {
        Aresta(&pontos[0], &pontos[1]),
        Aresta(&pontos[1], &pontos[2]),
        Aresta(&pontos[2], &pontos[3]),
        Aresta(&pontos[0], &pontos[3])
    };
    this->window = new Window("Window",pontos,arestas);
}

void FramePrincipal::rotinaWindow(){
    this->centralizarWindow(this->window);
    this->corrigirRotacaoWindow(this->window);
    this->escalonarPontos();
    this->calcularCoordenadasViewPort(this->window);
}

void FramePrincipal::rotinaAtualizacaoWindow(){
    this->centralizarWindow(this->window);
    this->corrigirRotacaoWindow(this->window);
    this->escalonarPontos();
    this->calcularCoordenadasViewPort(this->window);
}


