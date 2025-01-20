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

    carregarArquivos();
    this->window = dynamic_cast<Window*>(this->displayFile[0]);
    //imprimirObjetos();
}

void DisplayFile::aplicarClipping(bool isPerspectiva){
    Ponto *zmin;
    Ponto *zmax;
    // Definição do volume de visualização
    // zmin = VRP->z/2 por questões estéticas. No valor inteiro o clipping parece muito artificial
    if(isPerspectiva){
        zmin = new Ponto(0,0,this->window->VRP->zWin/2);
        zmax = new Ponto(0,0,this->window->VRP->zWin+1);
    }else{
        zmin = new Ponto(0,0,this->window->zmin->zWin+this->window->zmax->zWin);
        zmax = new Ponto(0,0,this->window->zmax->zWin);
    }
    for (int i = 1; i < this->displayFile.length(); i++) {
        for (Aresta* aresta : this->displayFile[i]->arestas) {
            aresta->clipping(this->window->pontos[0]->xWin,
                             this->window->pontos[2]->xWin,
                             this->window->pontos[0]->yWin,
                             this->window->pontos[2]->yWin,
                             zmin->z,
                             zmax->z);
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

void DisplayFile::carregarArquivos() {
    // Obter o diretório do executável
    QString executavelPath = QCoreApplication::applicationDirPath();

    // Subir três níveis para acessar o diretório do projeto
    QString pastaProjeto = QDir(executavelPath).filePath("../../../");

    // Caminho para a pasta "objetos"
    QString pastaObjetos = QDir(pastaProjeto).filePath("objetos");

    // Obter todos os arquivos .obj na pasta
    QDir dir(pastaObjetos);
    QStringList filtros;
    filtros << "*.obj"; // Apenas arquivos .obj
    QFileInfoList listaArquivos = dir.entryInfoList(filtros, QDir::Files);

    // Iterar sobre os arquivos
    for (const QFileInfo& arquivoInfo : listaArquivos) {
        QString arquivoPath = arquivoInfo.absoluteFilePath();

        QFile file(arquivoPath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Erro ao abrir o arquivo:" << file.errorString();
            qWarning() << "Caminho do arquivo tentado:" << arquivoPath;
            continue;
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
        QString nomeObjeto = arquivoInfo.baseName(); // Nome do arquivo sem extensão
        Objeto* obj = new Objeto(nomeObjeto, pontosDuplicados, arestas);
        this->displayFile.append(obj);

        qDebug() << "Objeto '" << nomeObjeto << "' adicionado ao DisplayFile com"
                 << pontosDuplicados.size() << "pontos e"
                 << arestas.size() << "arestas.";

        file.close();
    }
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
