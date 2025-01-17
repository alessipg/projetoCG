#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(float x = 0, float y = 0, float z = 0);
    float x;
    float y;
    float z;
    float xWin; //coordenadas virtuais
    float yWin; //
    float zWin;
    float w;
    float wWin;//
    int cor;
    bool rc[6];//clipping
    void calcularOutcode(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) ;
};

#endif // PONTO_H
