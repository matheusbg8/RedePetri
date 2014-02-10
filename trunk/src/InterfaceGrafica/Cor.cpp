#include "Cor.h"

Cor::Cor(float r , float g  , float b )
{
    vr = r;
    vg = g;
    vb = b;
}

Cor::Cor(const Cor &cor)
{
    vr = cor.vr;
    vg = cor.vg;
    vb = cor.vb;
}

float Cor::r() const
{
    return vr;
}

void Cor::r(float val)
{
    if(val >=0 && val <= 1.0)
        vr = val;
    else
        cout << "Cor::Erro tom de cor vermelha inválida" << endl;
}

float Cor::g() const
{
    return vg;
}

void Cor::g(float val)
{
    if(val >= 0.0 && val <= 1.0)
    {
        vg = val;
    }else
    {
        cout << "Cor::Erro tom de cor verde inválida" << endl;
    }
}

float Cor::b() const
{
    return vb;
}

void Cor::b(float val)
{
    if(val >= 0.0 && val <= 1.0)
    {
        vb = val;
    }else
    {
        cout << "Cor::Erro tom de cor azul inválida" << endl;
    }
}

void Cor::set(float r, float g, float b)
{
    this->r(r);
    this->g(g);
    this->b(b);
}

const Cor Cor::vermelho(1.0,0.0,0.0);
const Cor Cor::verde(0.0,1.0,0.0);
const Cor Cor::azul(0.0,0.0,1.0);
const Cor Cor::amarelo(1.0,1.0,0.0);
const Cor Cor::preto(0.0,0.0,0.0);
const Cor Cor::branco(1.0,1.0,1.0);
const Cor Cor::magenta(1.0,0.0,1.0);
const Cor Cor::ciano(0.0,1.0,1.0);

ostream & operator << (ostream &os , Cor & cor)
{
    os << '(' << cor.vr << ',' << cor.vg << ',' << cor.vb << ')';
    return os;
}
