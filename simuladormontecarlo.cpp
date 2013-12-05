#include "simuladormontecarlo.h"
#include "simulador.h"
#include <cmath>
#include <inttypes.h>

#include <iostream>
#include <fstream>
using namespace std;

SimuladorMonteCarlo::SimuladorMonteCarlo() : iteraciones()
{
}

double SimuladorMonteCarlo::sumaDiferenciaVectores(const vector<double> &v1, const vector<double> &v2)
{
    double diferencia=0;
    for(vector<double>::const_iterator it=v1.begin();it!=v1.end();it++) {
        diferencia+=fabs(*it-v2[it-v1.begin()]);
    }
    return diferencia;
}

vector<double> SimuladorMonteCarlo::distribucionEstacionaria(Simulador sim, double epsilon, ofstream &log)
{
    vector<unsigned> prob(sim.getCantidadEstados());
    vector<double> probActual(sim.getCantidadEstados());
    vector<double> probAnterior(sim.getCantidadEstados());
    int iteraciones = 0;
    do {
        prob[sim.getEstado()]++;
        iteraciones++;
        probAnterior = probActual;
        //transformamos a probabilidad
        for ( vector<unsigned>::iterator it=prob.begin();it!=prob.end();it++ )
        {
            probActual[it-prob.begin()] = (double)*it/(double)iteraciones;
        }
        sim.nextStep();

        // sector logfile
        for ( vector<double>::iterator it=probActual.begin();it!=probActual.end();it++ )
            log << *it << " ";
        log << endl;
        // fin sector logfile
    } while (sumaDiferenciaVectores(probActual, probAnterior)>epsilon);
    this->iteraciones = iteraciones;
    return probActual;
}

double SimuladorMonteCarlo::probabilidadEscape(Simulador perseguidor, Simulador escapador, double epsilon, ofstream &log)
{
    unsigned iteraciones=0;
    unsigned escapes=0;
    double probEscape=0;
    double probEscapeAnterior=0;
    do {
        perseguidor.setEstado(0);
        escapador.setEstado(0);
        escapador.nextStep();
        while (!escapador.gano())
        {
            escapador.nextStep();
            if (escapador.getEstado()==perseguidor.getEstado())
                break;
            perseguidor.nextStep();
            if (escapador.getEstado()==perseguidor.getEstado())
                break;
        }
        iteraciones++;
        if (escapador.gano())
            escapes++;
        probEscapeAnterior=probEscape;
        probEscape=(double)escapes/(double)iteraciones;
        log << probEscape << endl;
    } while(fabs(probEscape-probEscapeAnterior)>epsilon || iteraciones<100);
    this->iteraciones = iteraciones;
    return probEscape;
}

double SimuladorMonteCarlo::demoraPromedio(Simulador sim, double epsilon, ofstream &log)
{
    unsigned iteraciones=0;
    unsigned sumSegundos=0;
    double prob=0;
    double probAnterior=0;
    do {
        sim.setEstado(0);
        while(!sim.gano())
        {
            sim.nextStep();
            sumSegundos++;
        }
        iteraciones++;
        probAnterior=prob;
        prob=(double)sumSegundos/(double)iteraciones;
        log << prob << endl;
    } while(fabs(prob-probAnterior)>epsilon || iteraciones<100);
    this->iteraciones = iteraciones;
    return prob;
}

double SimuladorMonteCarlo::correlacionCruzada(Simulador perseguidor, Simulador escapador, double epsilon, ofstream &log)
{

    double prob=0;
    double probAnterior=0;
    int pasos=10;
    do
    {
        perseguidor.setEstado(0);
        escapador.setEstado(0);
        vector<int> caminoPerseguidor (pasos);
        vector<int> caminoEscapador (pasos);
        uint64_t mult=0;
        for ( int i=0;i<pasos;i++ )
        {
            caminoEscapador[i] = escapador.getEstado();
            caminoPerseguidor[i] = perseguidor.getEstado();
            escapador.nextStep();
            perseguidor.nextStep();
        }

        for ( int a=0;a<pasos;a++ )
            for ( int b=0;b<pasos;b++ )
                mult+=caminoEscapador[a]*caminoPerseguidor[b];
        probAnterior = prob;
        prob = (double)mult/(double)(pasos*pasos);
        log << prob << endl;
        pasos+=50;
        this->iteraciones=pasos;
    } while( fabs(prob-probAnterior) > epsilon );

    return prob;

}

unsigned SimuladorMonteCarlo::getIteraciones()
{
    return iteraciones;
}
