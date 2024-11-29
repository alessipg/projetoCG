#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(float x = 0, float y = 0);
    float x;
    float y;
    float coordW;
    float xWin; //coordenadas virtuais
    float yWin; //
    float coordWWin;//
    int cor;
};

#endif // PONTO_H
