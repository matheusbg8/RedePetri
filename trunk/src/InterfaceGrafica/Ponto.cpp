#include "Ponto.h"
#include <cmath>

template<class T>
double Ponto<T>::m_2prec = 1e-9;

template<class Tipo>
Tipo Ponto<Tipo>::mod(const Tipo& n) const
{
    if(n<0)
        return -n;
    return n;
}

template<class Tipo>
Ponto<Tipo>::Ponto(const QPoint &ponto)
{
    define((Tipo)ponto.x() , (Tipo)ponto.y());
}

template<class Tipo>
Ponto<Tipo>::Ponto(const Tipo &x , const Tipo &y)
{
    define(x, y);
}

template<class Tipo>
Ponto<Tipo>::Ponto(const Ponto &ponto)
{
    define(ponto.x(),ponto.y());
}

template<class Tipo>
const Ponto<Tipo> & Ponto<Tipo>::define(const Tipo &x, const Tipo &y)
{
    m_x = x;
    m_y = y;
    return *this;
}

template<class Tipo>
const Tipo & Ponto<Tipo>::x() const
{
    return m_x;
}


template<class Tipo>
const Tipo & Ponto<Tipo>::y() const
{
    return m_y;
}

template<class Tipo>
void Ponto<Tipo>::setX(const Tipo & x)
{
    m_x = x;
}

template<class Tipo>
void Ponto<Tipo>::setY(const Tipo &y)
{
    m_y = y;
}

template<class Tipo>
const Ponto<Tipo> & Ponto<Tipo>::operator = (const Ponto &ponto)
{
    return define(ponto.m_x, ponto.m_y);
}


template<class Tipo>
const Ponto<Tipo>& Ponto<Tipo>::operator +=( const Ponto & ponto)
{
    m_x += ponto.m_x;
    m_y += ponto.m_y;
    return *this;
}


template<class Tipo>
const Ponto<Tipo>& Ponto<Tipo>::operator -=( const Ponto & ponto)
{
    m_x -= ponto.m_x;
    m_y -= ponto.m_y;
    return *this;
}

template<class Tipo>
const Ponto<Tipo>& Ponto<Tipo>::operator +=( const Tipo & val)
{
    m_x += val;
    m_y += val;
    return *this;
}

template<class Tipo>
const Ponto<Tipo>& Ponto<Tipo>::operator -=( const Tipo &val)
{
    m_x -= val;
    m_y -= val;
    return *this;
}

template<class Tipo>
const Ponto<Tipo>& Ponto<Tipo>::operator *=( const Tipo &val)
{
    m_x *= val;
    m_y *= val;
    return *this;
}

template<class Tipo>
const Ponto<Tipo>& Ponto<Tipo>::operator /=( const Tipo &val)
{
    m_x /= val;
    m_y /= val;
    return *this;
}

template<class Tipo>
Ponto<Tipo> Ponto<Tipo>::operator +( const Ponto &ponto) const
{
    Ponto p(*this);
    return p += ponto;
}

template<class Tipo>
Ponto<Tipo> Ponto<Tipo>::operator -( const Ponto &ponto) const
{
    Ponto p(*this);
    return p -= ponto;
}


template<class Tipo>
Ponto<Tipo> Ponto<Tipo>::operator -() const
{
    Ponto p(-m_x , -m_y);
    return p;
}

template<class Tipo>
Ponto<Tipo> Ponto<Tipo>::operator +( const Tipo & val) const
{
    Ponto p(*this);
    return p += val;
}

template<class Tipo>
Ponto<Tipo> Ponto<Tipo>::operator -( const Tipo & val) const
{
    Ponto p(*this);
    return p -= val;
}

template<class Tipo>
Ponto<Tipo> Ponto<Tipo>::operator *( const Tipo & val) const
{
    Ponto p(*this);
    return p *= val;
}

template<class Tipo>
Ponto<Tipo> Ponto<Tipo>::operator /( const Tipo & val) const
{
    Ponto p(*this);
    return p /= val;
}

template<class Tipo>
bool Ponto<Tipo>::operator ==( const Ponto &ponto) const
{
    return mod(m_x - ponto.m_x) + mod(m_y - ponto.m_y) < m_2prec;
}

template<class Tipo>
bool Ponto<Tipo>::operator !=( const Ponto &ponto) const
{
    return ! ( (*this) == ponto);
}

template<class Tipo>
Tipo Ponto<Tipo>::mod2() const
{
    return m_x*m_x + m_y*m_y;
}

template<class Tipo>
Tipo Ponto<Tipo>::mod() const
{
    return sqrt(mod2());
}


template<class Tipo>
/**
 * @brief Retorna um vetor unitario.
 *
 * @return Vetor unitario.
 */
Ponto<Tipo> Ponto<Tipo>::uni() const
{
    float md = mod();
    if(md == 0.f) cout << "Problema Divisao por zero calculando vet Unitario" << endl;
    Ponto r(m_x/md, m_y/md);
    return r;
}


template<class Tipo>
/**
 * @brief Retorna um vetor ortogonal
 * ao ponto(vetor) e ao eixo Z positivo, no sentido Horario y|_ x.
 *
 * @return Ponto - Vetor ortogonal
 */
Ponto<Tipo> Ponto<Tipo>::ortoHorario() const
{
/*
    x1 y1 0
    0  0  1
    i  j  k

    i =  y1
    j = -x1
    k =  0
*/


    Ponto r(m_y, -m_x);
    return r;
}

template<class Tipo>
/**
 * @brief Retorna um vetor ortogonal
 * ao ponto(vetor) e ao eixo Z negativo, no sentido Anti-Horario y|_ x.
 *
 * @return Ponto - Vetor ortogonal.
 */
Ponto<Tipo> Ponto<Tipo>::ortoAntiHorario()const
{
    Ponto r(-m_y, m_x);
    return r;

}

template<class Tipo>
QPoint Ponto<Tipo>::toQPoint()
{
    return QPoint((int) m_x , (int) m_y);
}

template< class T >
ostream & operator << (ostream &os , const Ponto <T> &ponto)
{
    return (os << '(' <<  ponto.m_x << ',' << ponto.m_y << ')');
}

template< class T >
Ponto<T> operator +( const T & val, const Ponto<T>& p)
{
    Ponto<T> np(val,val);
    return np += p;
}

template< class T >
Ponto<T> operator -( const T & val, const Ponto<T>& p)
{
    Ponto<T> np(val,val);
    return np -= p;
}

template< class T >
Ponto<T> operator *( const T & val, const Ponto<T>& p)
{
    Ponto<T> np(p);
    return np *= val;
}

template<class T>
T distancia2(const Ponto<T> &a, const Ponto<T> &b)
{
    T dx = a.m_x - b.m_x,
      dy = a.m_y - b.m_y;

    return dx*dx + dy*dy;
}

template<class T>
T distancia(const Ponto<T> &a, const Ponto<T> &b)
{
    return sqrt(distancia2(a,b));
}

template<class T>
T distanciaH(const Ponto<T> &a, const Ponto<T> &b)
{
    return sqrt(distanciaH2(a,b));
}

template<class T>
T distanciaH2(const Ponto<T> &a, const Ponto<T> &b)
{
    T dx = a.m_x - b.m_x;
    return dx*dx;
}

template<class T>
T distanciaV(const Ponto<T> &a, const Ponto<T> &b)
{
    return sqrt(distanciaV2(a,b));
}

template<class T>
T distanciaV2(const Ponto<T> &a, const Ponto<T> &b)
{
    T dy = a.m_y - b.m_y;
    return dy*dy;
}
