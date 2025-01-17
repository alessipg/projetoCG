#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H
#include <QList>
#include "objeto.h"
#include "window.h"
class DisplayFile
{
public:
    DisplayFile();
    ~DisplayFile();
    QList<Objeto*> displayFile;
    Window *window;
    void gerarObjetos();
    void transformada(Matriz composta);
    void alinhamento(Matriz composta);
    void aplicarClipping(bool isPerspectiva);
    void carregarArquivos();
    void imprimirObjetos() const;
};

#endif // DISPLAYFILE_H
