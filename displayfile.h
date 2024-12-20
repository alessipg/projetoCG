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
    void gerarObjetos();
    void transformada(Matriz composta);
    void aplicarClipping();
    void carregarArquivo();
    void imprimirObjetos() const;
};

#endif // DISPLAYFILE_H
