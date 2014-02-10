#ifndef PONTO_H
#define PONTO_H

#include <QPoint>
#include <iostream>
using namespace std;

template< class Tipo = float >
class Ponto
{
private:
    Tipo m_x, m_y;
    static double m_2prec; // 2 vezes a precisão desejada

    Tipo mod(const Tipo& n) const;

public:
    Ponto(const QPoint &ponto);

//    Ponto(const Tipo &x = Tipo(), const Tipo &y = Tipo());
// Antigamente esse construtor possuia atributos padrões,
// porem um erro acontece quando usa-se um operador ponto com
// um tipo primitivo (int por exemplo) o compilador utiliza esse
// construtor passando o int como 1º parametro e utiliza valor padrão
// para o segundo parametro.
// Exemplo  ( 10, 10 ) - 10 =  (10 , 10 ) - ( 10 , 0 ) = (0 ,10)
// ao invez de (0 , 0), porque el chama o construtor envez de dar erro
// de compilação.

    Ponto(const Tipo &x , const Tipo &y );

    Ponto(const Ponto &ponto = Ponto(Tipo(),Tipo()));

    const Ponto & define(const Tipo &x, const Tipo &y);

    const Tipo & x() const;

    const Tipo & y() const;

    void setX(const Tipo & x);

    void setY(const Tipo &y);


    const Ponto & operator = (const Ponto &ponto);

    const Ponto& operator +=( const Ponto & ponto);

    const Ponto& operator -=( const Ponto & ponto);


    const Ponto& operator +=( const Tipo & val);

    const Ponto& operator -=( const Tipo &val);

    const Ponto& operator *=( const Tipo &val);

    const Ponto& operator /=( const Tipo &val);

    Ponto operator +( const Ponto &ponto) const;

    Ponto operator -( const Ponto &ponto) const;


    Ponto operator -() const;

    Ponto operator +( const Tipo & val) const;

    Ponto operator -( const Tipo & val) const;

    Ponto operator *( const Tipo & val) const;

    Ponto operator /( const Tipo & val) const;

    bool operator ==( const Ponto &ponto) const;

    bool operator !=( const Ponto &ponto) const;

    Tipo mod2() const;

    Tipo mod() const;

    Ponto uni() const;

    Ponto ortoHorario() const;

    Ponto ortoAntiHorario() const;

    QPoint toQPoint();

    template<class T>
    friend ostream &operator << (ostream &os , const Ponto<T> &ponto);

    template<class T>
    friend T distancia2(const Ponto<T> &a, const Ponto<T> &b);

    template<class T>
    friend T distancia(const Ponto<T> &a, const Ponto<T> &b);

    template<class T>
    friend T distanciaH(const Ponto<T> &a, const Ponto<T> &b);

    template<class T>
    friend T distanciaH2(const Ponto<T> &a, const Ponto<T> &b);

    template<class T>
    friend T distanciaV(const Ponto<T> &a, const Ponto<T> &b);

    template<class T>
    friend T distanciaV2(const Ponto<T> &a, const Ponto<T> &b);

};

template<class T>
T distancia2(const Ponto<T> &a, const Ponto<T> &b);

template<class T>
T distancia(const Ponto<T> &a, const Ponto<T> &b);

template<class T>
T distanciaH(const Ponto<T> &a, const Ponto<T> &b);

template<class T>
T distanciaH2(const Ponto<T> &a, const Ponto<T> &b);

template<class T>
T distanciaV(const Ponto<T> &a, const Ponto<T> &b);

template<class T>
T distanciaV2(const Ponto<T> &a, const Ponto<T> &b);

#include "Ponto.cpp"


#endif // PONTO_H
