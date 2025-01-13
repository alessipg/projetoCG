#include "mainwindow.h"
#include "ui_mainwindow.h"
#define DESLOCAMENTO 10

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Conectar o botão ao slot passando o texto como parâmetro
    //não consegui usar a interface do QTCreator para passar parâmetros
    connect(ui->btnPokemon, &QPushButton::clicked, this, [=]() {
        QString buttonText = ui->btnPokemon->text();
        ui->frame->desenharObjeto(buttonText);
    });
    connect(ui->btnQuadrado, &QPushButton::clicked, this, [=]() {
        QString buttonText = ui->btnQuadrado->text();
        ui->frame->desenharObjeto(buttonText);
    });
    connect(ui->btnTriangulo, &QPushButton::clicked, this, [=]() {
        QString buttonText = ui->btnTriangulo->text();
        ui->frame->desenharObjeto(buttonText);
    });
    connect(ui->btnLinha, &QPushButton::clicked, this, [=]() {
        QString buttonText = ui->btnLinha->text();
        ui->frame->desenharObjeto(buttonText);
    });

    //TRANSLACOES
    connect(ui->xMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',ui->valorT->value(),0,0,0);
    });
    connect(ui->xMenos, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',-ui->valorT->value(),0,0,0);
    });
    connect(ui->yMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,ui->valorT->value(),0,0);
    });
    connect(ui->yMenos, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,-ui->valorT->value(),0,0);
    });
    connect(ui->zMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,0,ui->valorT->value(),0);
    });
    connect(ui->zMenos, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,0,-ui->valorT->value(),0);
    });

    //ESCALA
    connect(ui->xEscMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',ui->valorE->value(),1,1,0);
    });
    connect(ui->yEscMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',1,ui->valorE->value(),1,0);
    });
    connect(ui->zEscMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',1,1,ui->valorE->value(),0);
    });
    connect(ui->allEscala, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',ui->valorE->value(),ui->valorE->value(),ui->valorE->value(),0);
    });


    //ROTACAO
    connect(ui->rotMais, &QPushButton::clicked, this, [=](){
        char eixo = checkEixo();
        if(eixo == -1)
            ui->statusbar->showMessage("Selecione um eixo para rotacionar",5);
        else
            ui->frame->transformarObjeto('R',ui->valorR->value(),0,0,eixo);
    });
    connect(ui->rotMenos, &QPushButton::clicked, this, [=](){
        char eixo = checkEixo();
        if(eixo == -1)
            ui->statusbar->showMessage("Selecione um eixo para rotacionar",5);
        else
            ui->frame->transformarObjeto('R',-ui->valorR->value(),0,0,eixo);
    });

    connect(ui->cbWindow, &QCheckBox::stateChanged, this, [=](int state) {
        //lógica para definir modificação na window ou no cenário
        if (state == Qt::Checked) {
            ui->frame->isWindow = true;
            ui->frame->objAtual = ui->frame->window;  // Foco no objeto window
        } else {
            ui->frame->isWindow = false;
            // Retorna ao último objeto alvo, caso exista
            ui->frame->objAtual = !ui->frame->objetoAlvo.isEmpty() ? ui->frame->getObjetoByName(ui->frame->objetoAlvo) : nullptr;
        }
    });

}
char MainWindow::checkEixo(){
    if(ui->rotX->isChecked())
        return 'X';
    else if(ui->rotY->isChecked())
        return 'Y';
    else if(ui->rotZ->isChecked())
        return 'Z';
    else return -1;
}

MainWindow::~MainWindow() {
    delete ui;
}
