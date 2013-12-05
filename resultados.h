#ifndef RESULTADOS_H
#define RESULTADOS_H

#include <QWidget>

namespace Ui {
    class Resultados;
}

class Calculator;

class Resultados : public QWidget {
    Q_OBJECT
public:
    Resultados(Calculator *calc, QWidget *parent = 0);
    ~Resultados();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Resultados *ui;
};

#endif // RESULTADOS_H
