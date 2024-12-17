#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(float x = 0, float y = 0);
    float x;
    float y;
    float z;
    float coordW;
    float xWin; //coordenadas virtuais
    float yWin; //
    float zWin;
    float coordWWin;//
    int cor;
    bool rc[4];//clipping
    void calcularOutcode(float xmin, float xmax, float ymin, float ymax) ;
};

#endif // PONTO_H
