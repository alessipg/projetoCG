#include "frameprincipal.h"
#include <iostream>
FramePrincipal::FramePrincipal(QWidget *parent)
    : QFrame{parent}
{
    df.gerarObjetos();
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
    painter.scale(1, -1);           // Inverte o eixo Y
    painter.setPen(QPen(Qt::red, 2));

    for (Objeto &obj : df.displayFile) {
        if (obj.nome == objetoAlvo) {
            for (Aresta aresta : obj.arestas) {
                painter.drawLine(aresta.a->x, aresta.a->y, aresta.b->x, aresta.b->y);
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

    update(); // Atualiza o widget
}
