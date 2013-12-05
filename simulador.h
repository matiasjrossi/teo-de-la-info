#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <utility>
#include "matriz.h"
using namespace std;

class Simulador
{
public:
    Simulador(Matriz<double> mat, int inic, pair<int,int> fin);
    void nextStep();
    bool gano();
    int getEstado();
    void setEstado(int estado);
    int getCantidadEstados();
private:
    Matriz<double> mat;
    int estado;
    int estadoAnterior;
    pair<int,int> fin;
};

#endif // SIMULADOR_H
