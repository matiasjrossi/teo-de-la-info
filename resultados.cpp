#include "resultados.h"
#include "ui_resultados.h"

#include "calculator.h"

Resultados::Resultados(Calculator *calc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resultados)
{
    ui->setupUi(this);
    ui->escape->setText(QString("%1").arg(calc->getProbEscape()));
    vector<double> bond = calc->getVDistBond(), no = calc->getVDistDrNo();
    ui->estacionariaBond->setText(QString("<%1, %2, %3, %4, %5, %6, %7, %8, %9, %10>").
            arg(bond[0]).arg(bond[1]).arg(bond[2]).arg(bond[3]).arg(bond[4]).
            arg(bond[5]).arg(bond[6]).arg(bond[7]).arg(bond[8]).arg(bond[9]));
    ui->estacionariaNo->setText(QString("<%1, %2, %3, %4, %5, %6, %7, %8, %9, %10>").
            arg(no[0]).arg(no[1]).arg(no[2]).arg(no[3]).arg(no[4]).
            arg(no[5]).arg(no[6]).arg(no[7]).arg(no[8]).arg(no[9]));
    ui->tiempoBond->setText(QString("%1").arg(calc->getCantPromSegundosBond()));
    ui->tiempoNo->setText(QString("%1").arg(calc->getCantPromSegundosDrNo()));
    ui->corr->setText(QString("%1").arg(calc->getCorrelacionCruzada()));
    ui->iterBondEsta->setText(QString("%1").arg(calc->getVDistBondIteraciones()));
    ui->iterNoEsta->setText(QString("%1").arg(calc->getVDistDrNoIteraciones()));
    ui->iterEscape->setText(QString("%1").arg(calc->getProbEscapeIteraciones()));
    ui->iterTiempoBond->setText(QString("%1").arg(calc->getCantPromSegundosBondIteraciones()));
    ui->iterTiempoNo->setText(QString("%1").arg(calc->getCantPromSegundosDrNoIteraciones()));
    ui->iterCorr->setText(QString("%1").arg(calc->getCorrelacionCruzadaIteraciones()));
}

Resultados::~Resultados()
{
    delete ui;
}

void Resultados::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
