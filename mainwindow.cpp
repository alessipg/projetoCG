#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Conectar o botão ao slot passando o texto como parâmetro
    //não consegui usar a interface do QTCreator para passar parâmetros
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
    connect(ui->btnTransformar, &QPushButton::clicked, this, [=](){
        QString inputText = ui->cmdTrans->toPlainText();
        ui->frame->transformarObjeto(inputText);
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


MainWindow::~MainWindow() {
    delete ui;
}
