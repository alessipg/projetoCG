#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DESLOCAMENTO 10

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame->setStyleSheet("background-color: rgb(255, 255, 255)");
    QButtonGroup *eixos = new QButtonGroup(this);
    QButtonGroup *centros = new QButtonGroup(this);
    eixos->addButton(ui->rotX);
    eixos->addButton(ui->rotY);
    eixos->addButton(ui->rotZ);

    centros->addButton(ui->rotCharizard);
    centros->addButton(ui->rotPorygon);
    centros->addButton(ui->rotSi);

    centros->setExclusive(true);
    eixos->setExclusive(true);

    //TRANSLACOES
    connect(ui->xMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',ui->valorT->value(),0,0,0,checkCentro());
    });
    connect(ui->xMenos, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',-ui->valorT->value(),0,0,0,checkCentro());
    });
    connect(ui->yMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,ui->valorT->value(),0,0,checkCentro());
    });
    connect(ui->yMenos, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,-ui->valorT->value(),0,0,checkCentro());
    });
    connect(ui->zMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,0,ui->valorT->value(),0,checkCentro());
    });
    connect(ui->zMenos, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('T',0,0,-ui->valorT->value(),0,checkCentro());
    });

    //ESCALA
    connect(ui->xEscMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',ui->valorE->value(),1,1,0,checkCentro());
    });
    connect(ui->yEscMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',1,ui->valorE->value(),1,0,checkCentro());
    });
    connect(ui->zEscMais, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',1,1,ui->valorE->value(),0,checkCentro());
    });
    connect(ui->allEscala, &QPushButton::clicked, this, [=](){
        ui->frame->transformarObjeto('E',ui->valorE->value(),ui->valorE->value(),ui->valorE->value(),0,checkCentro());
    });


    //ROTACAO
    connect(ui->rotMais, &QPushButton::clicked, this, [=](){
        char eixo = checkEixo();
        if(eixo == -1){
            ui->statusbar->showMessage("Selecione um eixo para rotacionar",5000);
        }
        else
            ui->frame->transformarObjeto('R',ui->valorR->value(),0,0,eixo,checkCentro());
    });
    connect(ui->rotMenos, &QPushButton::clicked, this, [=](){
        char eixo = checkEixo();
        if(eixo == -1)
            ui->statusbar->showMessage("Selecione um eixo para rotacionar",5000);
        else
            ui->frame->transformarObjeto('R',-ui->valorR->value(),0,0,eixo,checkCentro());
    });
    connect(ui->btnOrtogonal, &QRadioButton::clicked, this, [=]() {
        ui->frame->isPerspectiva = false;
        ui->frame->pipeline();
    });
    connect(ui->btnPerspectiva, &QRadioButton::clicked, this, [=]() {
        ui->frame->isPerspectiva = true;
        ui->frame->pipeline();
    });

    connect(ui->rbWindow, &QRadioButton::clicked, this, [=](bool checked) {
        if (checked) {
            ui->frame->objAtual = ui->frame->getObjetoByName("Window");  // Focus on the Charizard object
        }
    });

    connect(ui->rbCharizard, &QRadioButton::clicked, this, [=](bool checked) {
        if (checked) {
            ui->frame->objAtual = ui->frame->getObjetoByName("Charizard");  // Focus on the Charizard object
        }
    });

    connect(ui->rbPorygon, &QRadioButton::clicked, this, [=](bool checked) {
        if (checked) {
            ui->frame->objAtual = ui->frame->getObjetoByName("Porygon");  // Focus on the Porygon object
        }
    });

    connect(ui->rotPorygon, &QRadioButton::clicked, this, [=](bool checked) {
        if (checked) {
            ui->frame->objCentro = ui->frame->getObjetoByName("Porygon");  // Focus on the Porygon object
        }
    });

    connect(ui->rotCharizard, &QRadioButton::clicked, this, [=](bool checked) {
        if (checked) {
            ui->frame->objCentro = ui->frame->getObjetoByName("Charizard");  // Focus on the Porygon object
        }
    });

    connect(ui->rotSi, &QRadioButton::clicked, this, [=](bool checked) {
        if (checked) {
            ui->frame->objCentro = ui->frame->objAtual;  // Focus on the Porygon object
        }
    });



}

char MainWindow::checkCentro(){
    if(ui->rotSi->isChecked())
        return 'S';
    else if(ui->rotCharizard->isChecked())
        return 'C';
    else if(ui->rotPorygon->isChecked())
        return 'P';
    else return -1;
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
