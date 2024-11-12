/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "frameprincipal.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    FramePrincipal *frame;
    QPushButton *btnTriangulo;
    QPushButton *btnQuadrado;
    QPushButton *btnLinha;
    QPushButton *btnTransformar;
    QTextEdit *cmdTrans;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new FramePrincipal(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(250, 80, 499, 450));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        frame->setProperty("Width", QVariant(0));
        btnTriangulo = new QPushButton(centralwidget);
        btnTriangulo->setObjectName("btnTriangulo");
        btnTriangulo->setGeometry(QRect(130, 80, 83, 29));
        btnQuadrado = new QPushButton(centralwidget);
        btnQuadrado->setObjectName("btnQuadrado");
        btnQuadrado->setGeometry(QRect(130, 120, 83, 29));
        btnLinha = new QPushButton(centralwidget);
        btnLinha->setObjectName("btnLinha");
        btnLinha->setGeometry(QRect(130, 160, 83, 29));
        btnTransformar = new QPushButton(centralwidget);
        btnTransformar->setObjectName("btnTransformar");
        btnTransformar->setGeometry(QRect(130, 470, 83, 29));
        cmdTrans = new QTextEdit(centralwidget);
        cmdTrans->setObjectName("cmdTrans");
        cmdTrans->setGeometry(QRect(30, 270, 191, 131));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 230, 191, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 410, 131, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 430, 131, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 450, 131, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnTriangulo->setText(QCoreApplication::translate("MainWindow", "Tri\303\242ngulo", nullptr));
        btnQuadrado->setText(QCoreApplication::translate("MainWindow", "Quadrado", nullptr));
        btnLinha->setText(QCoreApplication::translate("MainWindow", "Linha", nullptr));
        btnTransformar->setText(QCoreApplication::translate("MainWindow", "Transformar", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Insira tranforma\303\247oes desejadas:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ex: R 0.2,1.8 3", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Ex: T 4,2.5", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Ex: E 3.4,0.3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
