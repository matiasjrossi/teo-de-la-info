#include "calculator.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "matriz.h"
#include "simulador.h"
#include "simuladormontecarlo.h"
using namespace std;

#include <QDebug>

Calculator::Calculator() : QThread(NULL)
{
}

void Calculator::run()
{
    double srcBond[10][10] = {
        {0,1,0,0,0,0,0,0,0,0},
        {1.0/3.0,0,1.0/3.0,0,1.0/3.0,0,0,0,0,0},
        {0,1.0/2.0,0,1.0/2.0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,1.0/2.0,0,0,0,0,1.0/2.0,0,0,0},
        {0,0,0,0,0,0,1.0,0,0,0},
        {0,0,0,0,1.0/3.0,1.0/3.0,0,1.0/3.0,0,0},
        {0,0,0,0,0,0,1.0/3.0,0,1.0/3.0,1.0/3.0},
        {0,0,0,0,0,0,0,1,0,0},
        {1.0/2.0,0,0,0,0,0,0,1.0/2.0,0,0}
    };

    double srcDrNo[10][10] = {
        {0,1,0,0,0,0,0,0,0,0},
        {0.15,0,0.15,0,0.7,0,0,0,0,0},
        {0,0.3,0,0.7,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0.3,0,0,0,0,0.7,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0.15,0.15,0,0.7,0,0},
        {0,0,0,0,0,0,0.15,0,0.15,0.7},
        {0,0,0,0,0,0,0,1,0,0},
        {0.3,0,0,0,0,0,0,0.7,0,0}
    };

    Matriz<double> matBond((double*)srcBond,10);
    Matriz<double> matDrNo((double*)srcDrNo,10);
    Simulador sBond(matBond, 0, pair<int,int>(9,0));
    Simulador sDrNo(matDrNo, 0, pair<int,int>(9,0));
    SimuladorMonteCarlo sm;


    cout << "Distribucion estacionaria para Bond:" << endl;
    ofstream logEstacionariaBond ("estacionaria_bond.log");
    vDistBond = sm.distribucionEstacionaria(sBond, 0.00001, logEstacionariaBond);
    for (vector<double>::iterator it=vDistBond.begin();it!=vDistBond.end();it++)
        cout << (int)(it-vDistBond.begin()) << ": " << ((*it)*100) << "%" << endl;
    cout << "Calculada luego de " << (vDistBondIteraciones = sm.getIteraciones()) << " iteraciones." << endl;
    cout << endl;

    cout << "Distribucion estacionaria para Dr-No:" << endl;
    ofstream logEstacionariaDrNo ("estacionaria_drno.log");
    vDistDrNo = sm.distribucionEstacionaria(sDrNo, 0.00001, logEstacionariaDrNo);
    for (vector<double>::iterator it=vDistDrNo.begin();it!=vDistDrNo.end();it++)
        cout << (int)(it-vDistDrNo.begin()) << ": " << ((*it)*100) << "%" << endl;
    cout << "Calculada luego de " << (vDistDrNoIteraciones = sm.getIteraciones()) << " iteraciones." << endl;
    cout << endl;

    ofstream logProbEscape("escape.log");
    probEscape = sm.probabilidadEscape(sBond, sDrNo, 0.00001,logProbEscape);
    cout << "Probabilidad de que Dr-No escape: "
            << probEscape*100 << "%"
            << " calculada luego de "
            << (probEscapeIteraciones = sm.getIteraciones()) << " iteraciones." << endl;

    ofstream logTiempoBond("tiempo_bond.log");
    cantPromSegundosBond = sm.demoraPromedio(sBond,0.000001,logTiempoBond);
    cout << "Tiempo promedio para Bond: " << cantPromSegundosBond
            << " calculado luego de " << (cantPromSegundosBondIteraciones = sm.getIteraciones()) << " iteraciones." << endl;

    ofstream logTiempoDrNo("tiempo_drno.log");
    cantPromSegundosDrNo = sm.demoraPromedio(sDrNo,0.000001,logTiempoDrNo);
    cout << "Tiempo promedio para Dr-No: " << cantPromSegundosDrNo
            << " calculado luego de " << (cantPromSegundosDrNoIteraciones = sm.getIteraciones()) << " iteraciones." << endl;

    ofstream logCorelacionCruzada("correlacion_cruzada.log");
    correlacionCruzada = sm.correlacionCruzada(sBond,sDrNo,0.005,logCorelacionCruzada);
    cout << "Correlacion cruzada: " << correlacionCruzada
            << " calculada luego de " << (correlacionCruzadaIteraciones = sm.getIteraciones()) << " iteraciones." << endl;

    qDebug() << "TERMINE";
}

vector<double> &Calculator::getVDistBond()
{
    return vDistBond;
}

vector<double> &Calculator::getVDistDrNo()
{
    return vDistDrNo;
}

double Calculator::getProbEscape() const
{
    return probEscape;
}

double Calculator::getCantPromSegundosBond() const
{
    return cantPromSegundosBond;
}

double Calculator::getCantPromSegundosDrNo() const
{
    return cantPromSegundosDrNo;
}

double Calculator::getCorrelacionCruzada() const
{
    return correlacionCruzada;
}

unsigned long Calculator::getVDistBondIteraciones() const
{
    return vDistBondIteraciones;
}

unsigned long Calculator::getVDistDrNoIteraciones() const
{
    return vDistDrNoIteraciones;
}

unsigned long Calculator::getCantPromSegundosBondIteraciones() const
{
    return cantPromSegundosBondIteraciones;
}

unsigned long Calculator::getCantPromSegundosDrNoIteraciones() const
{
    return cantPromSegundosDrNoIteraciones;
}

unsigned long Calculator::getProbEscapeIteraciones() const
{
    return probEscapeIteraciones;
}

unsigned long Calculator::getCorrelacionCruzadaIteraciones() const
{
    return correlacionCruzadaIteraciones;
}
