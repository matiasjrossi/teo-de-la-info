#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QThread>
#include <vector>
using namespace std;

class Calculator : public QThread
{
public:
    Calculator();
    void run();
    vector<double> &getVDistBond();
    vector<double> &getVDistDrNo();
    double getProbEscape() const;
    double getCantPromSegundosBond() const;
    double getCantPromSegundosDrNo() const;
    double getCorrelacionCruzada() const;
    unsigned long getVDistBondIteraciones() const;
    unsigned long getVDistDrNoIteraciones() const;
    unsigned long getProbEscapeIteraciones() const;
    unsigned long getCantPromSegundosBondIteraciones() const;
    unsigned long getCantPromSegundosDrNoIteraciones() const;
    unsigned long getCorrelacionCruzadaIteraciones() const;
private:
    vector<double> vDistBond;
    unsigned long vDistBondIteraciones;
    vector<double> vDistDrNo;
    unsigned long vDistDrNoIteraciones;
    double probEscape;
    unsigned long probEscapeIteraciones;
    double cantPromSegundosBond;
    unsigned long cantPromSegundosBondIteraciones;
    double cantPromSegundosDrNo;
    unsigned long cantPromSegundosDrNoIteraciones;
    double correlacionCruzada;
    unsigned long correlacionCruzadaIteraciones;
};

#endif // CALCULATOR_H
