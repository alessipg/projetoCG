#include "displayfile.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

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
        new Ponto(0, 450,0),
    };
    QList<Aresta*> arestas0 = {
        new Aresta(pontos0[0], pontos0[1]),
        new Aresta(pontos0[1], pontos0[2]),
        new Aresta(pontos0[2], pontos0[3]),
        new Aresta(pontos0[3], pontos0[0])
    };
    Window* obj0 = new Window{"Window", pontos0, arestas0};
    this->displayFile.append(obj0);

    // Linha
    QList<Ponto*> pontos1 = {
        new Ponto(100, 200,0),
        new Ponto(200, 200,0)
    };
    QList<Aresta*> arestas1 = {
        new Aresta(pontos1[0], pontos1[1])
    };
    Objeto* obj1 = new Objeto{"Linha", pontos1, arestas1};
    this->displayFile.append(obj1);

    // Triângulo
    QList<Ponto*> pontos2 = {
        new Ponto(50, 50,0),
        new Ponto(300, 50,0),
        new Ponto(300, 50,0),
        new Ponto(200, 200,0),
        new Ponto(200, 200,0),
        new Ponto(50, 50,0)
    };
    QList<Aresta*> arestas2 = {
        new Aresta(pontos2[0], pontos2[1]),
        new Aresta(pontos2[2], pontos2[3]),
        new Aresta(pontos2[4], pontos2[5])
    };
    Objeto* obj2 = new Objeto{"Triângulo", pontos2, arestas2};
    this->displayFile.append(obj2);

    // Quadrado
    QList<Ponto*> pontos3 = {
        new Ponto(100, 100,0),
        new Ponto(200, 100,0),
        new Ponto(200, 100,0),
        new Ponto(200, 200,0),
        new Ponto(200, 200,0),
        new Ponto(100, 200,0),
        new Ponto(100, 200,0),
        new Ponto(100, 100,0),

        new Ponto(100, 100,100),
        new Ponto(200, 100,100),
        new Ponto(200, 100,100),
        new Ponto(200, 200,100),
        new Ponto(200, 200,100),
        new Ponto(100, 200,100),
        new Ponto(100, 200,100),
        new Ponto(100, 100,100),

        new Ponto(100, 100,0),
        new Ponto(200, 100,0),
        new Ponto(200, 200,0),
        new Ponto(100, 200,0),

        new Ponto(100, 100,100),
        new Ponto(200, 100,100),
        new Ponto(200, 200,100),
        new Ponto(100, 200,100)

    };
    QList<Aresta*> arestas3 = {
        new Aresta(pontos3[0], pontos3[1]),
        new Aresta(pontos3[2], pontos3[3]),
        new Aresta(pontos3[4], pontos3[5]),
        new Aresta(pontos3[6], pontos3[7]),

        new Aresta(pontos3[8], pontos3[9]),
        new Aresta(pontos3[10], pontos3[11]),
        new Aresta(pontos3[12], pontos3[13]),
        new Aresta(pontos3[14], pontos3[15]),

        new Aresta(pontos3[16], pontos3[20]),
        new Aresta(pontos3[17], pontos3[21]),
        new Aresta(pontos3[18], pontos3[22]),
        new Aresta(pontos3[19], pontos3[23])

    };

    Objeto* obj3 = new Objeto{"Quadrado", pontos3, arestas3};
    this->displayFile.append(obj3);

    carregarArquivo();

    imprimirObjetos();
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

DisplayFile::~DisplayFile() {
    for (auto obj : displayFile) {
        delete obj;
    }
    displayFile.clear();
}

void DisplayFile::carregarArquivo() {

    QFile file(QString::fromUtf8("/Users/helenarentschler/Desktop/box.obj"));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir o arquivo:";
        return;
    }

    QList<Ponto*> vertices;  // Lista de todos os vértices únicos
    QList<Aresta*> arestas;  // Lista de todas as arestas

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);

        if (parts.isEmpty()) continue;

        if (parts[0] == "v") {
            // Leitura de vértices
            float x = parts[1].toFloat();
            float y = parts[2].toFloat();
            float z = parts[3].toFloat(); // Pode ser ignorado para 2D
            vertices.append(new Ponto(x, y));
        } else if (parts[0] == "f") {
            // Construção de arestas duplicando vértices
            QList<Ponto*> faceVertices;

            for (int i = 1; i < parts.size(); ++i) {
                QString vertexData = parts[i];
                int vertexIndex = vertexData.split("/")[0].toInt() - 1; // Índices começam em 1 no .obj
                if (vertexIndex < 0 || vertexIndex >= vertices.size()) continue;

                // Duplicar o vértice para a aresta
                Ponto* pontoDuplicado = new Ponto(vertices[vertexIndex]->xWin,
                                                  vertices[vertexIndex]->yWin);
                faceVertices.append(pontoDuplicado);

                // Conectar com o próximo vértice
                if (i > 1) {
                    arestas.append(new Aresta(faceVertices[i - 2], pontoDuplicado));
                }
            }

            // Fechar a face se for um polígono
            if (!faceVertices.isEmpty()) {
                arestas.append(new Aresta(faceVertices.last(), faceVertices.first()));
            }
        }
    }

    // Criar o único Objeto e adicionar ao displayFile
    Objeto* obj = new Objeto("Pokemon", vertices, arestas);
    this->displayFile.append(obj);
    qDebug() << "Objeto 'Pokemon' adicionado ao DisplayFile.";


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
                     << ponto->xWin << "," << ponto->yWin << ")";
        }

        // Imprimir arestas
        qDebug() << "  Arestas:";
        int arestaIndex = 0;
        for (const Aresta* aresta : obj->arestas) {
            qDebug() << "    Aresta" << arestaIndex++ << ": ("
                     << "Ponto1: (" << aresta->a->xWin << ","
                     << aresta->a->yWin << "),"
                     << "Ponto2: (" << aresta->b->xWin << ","
                     << aresta->b->yWin << "))";
        }
    }
}



