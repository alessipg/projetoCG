#include "displayfile.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QDir>
#include <QCoreApplication>
DisplayFile::DisplayFile() {
}

void DisplayFile::gerarObjetos() {
/*  Para fazer o dynamic cast, deve se utilizar ponteiros, então todo o programa foi alterado.
 *  Agora todo obj de classe que herda de Objeto pode ser alocado no df, desde que tenha
 *  destrutor adequado.
 */

    QList<Ponto*> pontos0 = {
        new Ponto(0,0,0),
        new Ponto(500, 0,0),
        new Ponto(500, 450,0),
        new Ponto(0, 450,0)
    };
    QList<Aresta*> arestas0 = {
        new Aresta(pontos0[0], pontos0[1]),
        new Aresta(pontos0[1], pontos0[2]),
        new Aresta(pontos0[2], pontos0[3]),
        new Aresta(pontos0[3], pontos0[0])
    };
    Window* obj0 = new Window{"Window", pontos0, arestas0};
    this->displayFile.append(obj0);
    /*
    // Linha
    QList<Ponto*> pontos1 = {
        new Ponto(100, 200),
        new Ponto(200, 200)
    };
    QList<Aresta*> arestas1 = {
        new Aresta(pontos1[0], pontos1[1])
    };
    Objeto* obj1 = new Objeto{"Linha", pontos1, arestas1};
    this->displayFile.append(obj1);

    // Triângulo
    QList<Ponto*> pontos2 = {
        new Ponto(50, 50),
        new Ponto(300, 50),
        new Ponto(300, 50),
        new Ponto(200, 200),
        new Ponto(200, 200),
        new Ponto(50, 50)
    };
    QList<Aresta*> arestas2 = {
        new Aresta(pontos2[0], pontos2[1]),
        new Aresta(pontos2[2], pontos2[3]),
        new Aresta(pontos2[4], pontos2[5])
    };
    Objeto* obj2 = new Objeto{"Triângulo", pontos2, arestas2};
    this->displayFile.append(obj2);
    */
    // Quadrado
    QList<Ponto*> pontos3 = {
        // Frente (Z = 0)
        new Ponto(100, 100, 0),  // Ponto 0
        new Ponto(200, 100, 0),  // Ponto 1
        new Ponto(200, 100, 0),  // Ponto 2
        new Ponto(200, 200, 0),  // Ponto 3
        new Ponto(200, 200, 0),  // Ponto 4
        new Ponto(100, 200, 0),  // Ponto 5
        new Ponto(100, 200, 0),  // Ponto 6
        new Ponto(100, 100, 0),  // Ponto 7

        // Trás (Z = -100)
        new Ponto(100, 100, -100),  // Ponto 8
        new Ponto(200, 100, -100),  // Ponto 9
        new Ponto(200, 100, -100),  // Ponto 10
        new Ponto(200, 200, -100),  // Ponto 11
        new Ponto(200, 200, -100),  // Ponto 12
        new Ponto(100, 200, -100),  // Ponto 13
        new Ponto(100, 200, -100),  // Ponto 14
        new Ponto(100, 100, -100),  // Ponto 15

        // Conexões entre frente e trás
        new Ponto(100, 100, 0),    // Ponto 16
        new Ponto(100, 100, -100), // Ponto 17
        new Ponto(200, 100, 0),    // Ponto 18
        new Ponto(200, 100, -100), // Ponto 19
        new Ponto(200, 200, 0),    // Ponto 20
        new Ponto(200, 200, -100), // Ponto 21
        new Ponto(100, 200, 0),    // Ponto 22
        new Ponto(100, 200, -100)  // Ponto 23
    };

    QList<Aresta*> arestas3 = {
        // Arestas da frente
        new Aresta(pontos3[0], pontos3[1]),
        new Aresta(pontos3[2], pontos3[3]),
        new Aresta(pontos3[4], pontos3[5]),
        new Aresta(pontos3[6], pontos3[7]),

        // Arestas de trás
        new Aresta(pontos3[8], pontos3[9]),
        new Aresta(pontos3[10], pontos3[11]),
        new Aresta(pontos3[12], pontos3[13]),
        new Aresta(pontos3[14], pontos3[15]),

        // Conexões entre frente e trás
        new Aresta(pontos3[16], pontos3[17]),
        new Aresta(pontos3[18], pontos3[19]),
        new Aresta(pontos3[20], pontos3[21]),
        new Aresta(pontos3[22], pontos3[23])
    };

    Objeto* obj3 = new Objeto{"Cubo", pontos3, arestas3};
    this->displayFile.append(obj3);

    carregarArquivo();

    //imprimirObjetos();
}

void DisplayFile::aplicarClipping(){
    // Aqui está aplicando em todos os objetos do displayfile, talvez
    // tenha que mudar isso lá na frente
    for(int i = 1;i<this->displayFile.length();i++){
            for (Aresta* aresta : this->displayFile[i]->arestas) {
                aresta->clipping(this->displayFile[0]->pontos[0]->xWin,
                                 this->displayFile[0]->pontos[2]->xWin,
                                 this->displayFile[0]->pontos[0]->yWin,
                                 this->displayFile[0]->pontos[2]->yWin);
            }

    }
}

void DisplayFile::transformada(Matriz composta){
    for(Objeto* obj : this->displayFile){
        obj->transformarPontosWin(composta);
    }
}
void DisplayFile::alinhamento(Matriz composta){
    for(Objeto* obj : this->displayFile){
        obj->alinharPontosWin(composta);
    }
}

DisplayFile::~DisplayFile() {
    for (auto obj : displayFile) {
        delete obj;
    }
    displayFile.clear();
}

void DisplayFile::carregarArquivo() {
    // Obter o diretório do executável
    QString executavelPath = QCoreApplication::applicationDirPath();

    // Subir três níveis para acessar o diretório do projeto
    QString pastaProjeto = QDir(executavelPath).filePath("../../../");

    // Caminho para a pasta "objetos"
    QString pastaObjetos = QDir(pastaProjeto).filePath("objetos");

    // Caminho completo para o arquivo .obj
    QString arquivoPath = QDir(pastaObjetos).filePath("charizard.obj");

    QFile file(arquivoPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir o arquivo:" << file.errorString();
        qWarning() << "Caminho do arquivo tentado:" << arquivoPath;
        return;
    }

    QList<Ponto*> vertices; // Lista de vértices únicos
    QList<Ponto*> pontosDuplicados; // Lista de pontos duplicados para arestas
    QList<Aresta*> arestas; // Lista de arestas

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);

        if (parts.isEmpty()) continue;

        if (parts[0] == "v") {
            // Leitura de vértices
            float x = parts[1].toFloat();
            float y = parts[2].toFloat();
            float z = parts[3].toFloat();
            vertices.append(new Ponto(x, y, z));
        } else if (parts[0] == "f") {
            // Criar lista de pontos duplicados para esta face
            QList<Ponto*> faceVertices;
            for (int i = 1; i < parts.size(); ++i) {
                QString vertexData = parts[i];
                int vertexIndex = vertexData.split("/")[0].toInt() - 1; // Índices começam em 1 no .obj

                if (vertexIndex < 0 || vertexIndex >= vertices.size()) {
                    qWarning() << "Índice de vértice inválido:" << vertexIndex;
                    continue;
                }

                // Criar um novo ponto duplicado com base no vértice original
                Ponto* pontoDuplicado = new Ponto(vertices[vertexIndex]->x,
                                                  vertices[vertexIndex]->y,
                                                  vertices[vertexIndex]->z);
                faceVertices.append(pontoDuplicado);

                // Criar uma aresta conectando ao ponto anterior
                if (i > 1) {
                    Ponto* pontoAnterior = new Ponto(faceVertices[i - 2]->x,
                                                    faceVertices[i - 2]->y,
                                                    faceVertices[i - 2]->z);
                    Ponto* pontoAtual = new Ponto(faceVertices[i - 1]->x,
                                                  faceVertices[i - 1]->y,
                                                  faceVertices[i - 1]->z);
                    arestas.append(new Aresta(pontoAnterior, pontoAtual));
                    pontosDuplicados.append(pontoAnterior);
                    pontosDuplicados.append(pontoAtual);
                }
            }

            // Fechar a face se for um polígono (opcional)
            if (faceVertices.size() > 2) {
                Ponto* primeiroPonto = new Ponto(faceVertices.first()->x,
                                                faceVertices.first()->y,
                                                faceVertices.first()->z);
                Ponto* ultimoPonto = new Ponto(faceVertices.last()->x,
                                               faceVertices.last()->y,
                                               faceVertices.last()->z);
                arestas.append(new Aresta(ultimoPonto, primeiroPonto));
                pontosDuplicados.append(primeiroPonto);
                pontosDuplicados.append(ultimoPonto);
            }
        }
    }

    // Criar o objeto e adicioná-lo ao DisplayFile
    Objeto* obj = new Objeto("Pokemon", pontosDuplicados, arestas);
    this->displayFile.append(obj);

    qDebug() << "Objeto 'Pokemon' adicionado ao DisplayFile com"
             << pontosDuplicados.size() << "pontos e"
             << arestas.size() << "arestas.";

    file.close();
}



void DisplayFile::imprimirObjetos() const {
    int objetoIndex = 0;

    for (const Objeto* obj : displayFile) {
        qDebug() << "Objeto" << objetoIndex++ << ":" << obj->nome;

        // Imprimir pontos
        qDebug() << "  Pontos:";
        int pontoIndex = 0;
        for (const Ponto* ponto : obj->pontos) {
            qDebug() << "    Ponto" << pontoIndex++ << ": ("
                     << ponto->x << "," << ponto->y << "," << ponto->z << ")";
        }
        qDebug() << "  Pontos:";
        pontoIndex = 0;
        for (const Ponto* ponto : obj->pontos) {
            qDebug() << "    Ponto" << pontoIndex++ << ": ("
                     << ponto->x << "," << ponto->y << "," << ponto->z << ")";
            if (ponto == obj->medio) {
                qDebug() << "      -> Este é o ponto médio!";
            }
        }

        // Imprimir arestas
        qDebug() << "  Arestas:";
        int arestaIndex = 0;
        for (const Aresta* aresta : obj->arestas) {
            qDebug() << "    Aresta" << arestaIndex++ << ": ("
                     << "Ponto1: (" << aresta->a->x << ","
                     << aresta->a->y << ","
                     << aresta->a->z << "), "
                     << "Ponto2: (" << aresta->b->x << ","
                     << aresta->b->y << ","
                     << aresta->b->z <<"))";
        }
    }
}



