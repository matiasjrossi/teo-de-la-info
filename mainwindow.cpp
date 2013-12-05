#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTabWidget>
#include "calculator.h"
#include "progressdialog.h"
#include "resultados.h"
#include <QLabel>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Calculator *calc = new Calculator();
    ProgressDialog *dialog = new ProgressDialog("Simulando", "Espere mientras se realiza la simulación...", this);
    connect(calc, SIGNAL(finished()), dialog, SLOT(accept()));
    calc->start();
    dialog->exec();
    ui->setupUi(this);
    QTabWidget *widget = new QTabWidget(this);
    setCentralWidget(widget);
    widget->addTab(new Resultados(calc, widget), "Resultados");
    QProcess *process = new QProcess(this);
    dialog = new ProgressDialog("Graficando", "Espere mientras se procesan los gráficos...", this);
    connect(process, SIGNAL(finished(int)), dialog, SLOT(accept()));
    process->start("gnuplot.exe", QStringList("plotscript.plot"));
    dialog->exec();
    QLabel *label=new QLabel();
    label->setPixmap(QPixmap("estacionaria_bond.png"));
    widget->addTab(label, "Distribución estacionaria James Bond");
    label = new QLabel();
    label->setPixmap(QPixmap("estacionaria_drno.png"));
    widget->addTab(label, "Distribución estacionaria Doctor No");
    label = new QLabel();
    label->setPixmap(QPixmap("escape.png"));
    widget->addTab(label, "Probabilidad de escape");
    label = new QLabel();
    label->setPixmap(QPixmap("tiempo_bond.png"));
    widget->addTab(label, "Tiempo promedio de James Bond");
    label = new QLabel();
    label->setPixmap(QPixmap("tiempo_drno.png"));
    widget->addTab(label, "Tiempo promedio de Doctor No");
    label = new QLabel();
    label->setPixmap(QPixmap("correlacion_cruzada.png"));
    widget->addTab(label, "Correlación cruzada");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
