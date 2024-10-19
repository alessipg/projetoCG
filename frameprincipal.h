#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include <QWidget>

class MainFrame : public QFrame
{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent = nullptr);
public slots:
    draw();
};

#endif // MAINFRAME_H
