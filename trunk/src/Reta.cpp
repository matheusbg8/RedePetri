#include "Reta.h"

Reta::Reta()
{
}

void Reta::defineReta2P(const rPonto &p1, const rPonto &p2)
{
    m_p = p1;
    m_v = p2 - p1;
}

void Reta::defineRetaPV(const rPonto &p, const rPonto &v)
{
    m_p = p;
    m_v = v;
}
