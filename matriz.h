#ifndef MATRIZ_H
#define MATRIZ_H

#include <iterator>

template <typename T>
class Matriz
{
public:
    Matriz() : n(), mat() {};
    Matriz(int n);
    Matriz( T *data, int n );
    Matriz(const Matriz &that);
    Matriz<T>& operator =(const Matriz<T> &that);
    ~Matriz();
    void setN(int n);
    const int &getN() const;
    void set(int fila, int columna, T val);
    const T &get(int fila, int columna) const;

private:
    int n;
    T *mat;
};

template <typename T>
Matriz<T>::Matriz(int n)
{
    this->n = n;
    this->mat = new T[n*n];
}

template <typename T>
Matriz<T>::Matriz(T *data, int n)
{
    this->n = n;
    this->mat = new T[n*n];
    for ( int i=0;i<n*n;++i )
        this->mat[i] = data[i];
}

template <typename T>
Matriz<T>::Matriz(const Matriz &that)
{
    this->n = that.getN();
    this->mat = new T[n*n];
    for (int i=0;i<n*n;i++)
        this->mat[i] = that.mat[i];
}

template <typename T>
Matriz<T>& Matriz<T>::operator =(const Matriz<T> &that)
{
    this->setN(that.getN());
    for (int i=0;i<n*n;i++)
        this->mat[i] = that.mat[i];
    return *this;
}

template <typename T>
Matriz<T>::~Matriz()
{
    delete[] this->mat;
}

template <typename T>
void Matriz<T>::setN ( int n )
{
    delete[] this->mat;
    this->n = n;
    this->mat = new T[n*n];
}

template <typename T>
const int &Matriz<T>::getN() const
{
    return this->n;
}

template <typename T>
void Matriz<T>::set(int fila, int columna, T val)
{
    this->mat[fila*(this->n)+columna] = val;
}

template <typename T>
const T &Matriz<T>::get(int fila, int columna) const
{
    return this->mat[fila*n+columna];
}

#endif // MATRIZ_H
