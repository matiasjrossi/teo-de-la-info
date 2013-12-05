#ifndef SIMULADORMONTECARLO_H
#define SIMULADORMONTECARLO_H

#include <vector>
#include <fstream>

class Simulador;

using namespace std;

class SimuladorMonteCarlo
{
public:
    SimuladorMonteCarlo();
    vector<double> distribucionEstacionaria(Simulador sim, double epsilon, ofstream &log);
    double probabilidadEscape(Simulador perseguidor, Simulador escapador, double epsilon, ofstream &log);
    double demoraPromedio(Simulador sim, double epsilon, ofstream &log);
    double correlacionCruzada(Simulador perseguidor, Simulador escapador, double epsilon, ofstream &log);
    unsigned getIteraciones();
private:
    double sumaDiferenciaVectores(const vector<double> &v1, const vector<double> &v2);
    unsigned iteraciones;
};

#endif // SIMULADORMONTECARLO_H
