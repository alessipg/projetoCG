#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H
#include <QList>
#include "objeto.h"

class DisplayFile
{
public:
    DisplayFile();
    void gerarObjetos();
    QList<Objeto> displayFile;
};

#endif // DISPLAYFILE_H
