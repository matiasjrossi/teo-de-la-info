#include "simulador.h"
#include "matriz.h"
#include <cstdlib>

#include <inttypes.h>
#include <sys/timeb.h>
#include <ctime>

#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

uint64_t getMilliTime () {
    struct timeb timebuffer;
    ftime(&timebuffer);
    return timebuffer.time * 1000 + timebuffer.millitm;
}

boost::mt19937 rng(getMilliTime());
boost::uniform_01<boost::mt19937> rand01(rng);

Simulador::Simulador(Matriz<double> mat, int inic, pair<int,int> fin)
    : mat(mat), estado(inic), estadoAnterior(inic), fin(fin)
{
}

void Simulador::nextStep()
{
    //double r = (double)rand()/(double)RAND_MAX;
    double r = rand01();
    int columna=0;
    for ( ;columna<mat.getN() && r>=0;++columna )
    {
        r-=mat.get(estado,columna);
    }
    columna--;
    estadoAnterior=estado;
    estado=columna;
}

bool Simulador::gano()
{
    return ( estadoAnterior==fin.first && estado==fin.second );
}

int Simulador::getEstado()
{
    return estado;
}

void Simulador::setEstado(int estado)
{
    this->estado=estado;
    this->estadoAnterior=estado;
}

int Simulador::getCantidadEstados()
{
    return mat.getN();
}
