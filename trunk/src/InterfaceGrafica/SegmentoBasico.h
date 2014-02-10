#ifndef SEGMENTOBASICO_H
#define SEGMENTOBASICO_H

#include "Utilidades.h"
#include "RetanguloBasico.h"

class SegmentoBasico
{
private:
    rPonto m_ini;
    rPonto m_fim;
public:
    SegmentoBasico(const rPonto &ini , const rPonto& fim);

    bool temIntercecao( const SegmentoBasico& seg) const;
    float intercecaoS( const SegmentoBasico& s) const;
    rPonto intercecao( const SegmentoBasico& seg) const;
    rPonto intercecao( const RetanguloBasico& r) const;

    void setInicio(const rPonto &inicio);
    void setFim(const rPonto &fim);

    const rPonto inicio() const;
    const rPonto fim() const;

    const float comprimento() const;

};

#endif // SEGMENTOBASICO_H


//#include "InterfaceGrafica/SegmentoBasico.h"


//int main()
//{
//    SegmentoBasico sVermelho1(rPonto(1,4),rPonto(5,6)), sVermelho2(rPonto(1,6),rPonto(5,1)),
//            sVerde1(rPonto(0,0),rPonto(9,9)) , sVerde2(rPonto(3,9), rPonto(8,0)),
//            sAzul1(rPonto(3,6), rPonto(7,8)) , sAzul2(rPonto(6,4), rPonto(6,9)),
//            sRosa1(rPonto(4,0), rPonto(9,4)) , sRosa2(rPonto(5,2), rPonto(9,2)),
//            sLaranja1(rPonto(2,3),rPonto(9,3)), sLaranja2(rPonto(5,0), rPonto(5,4));


//    cout << "Vermelho " << sVermelho1.intercecao(sVermelho2) << endl
//         << "Verde " << sVerde1.intercecao(sVerde2) << endl
//         << "Azul " << sAzul1.intercecao(sAzul2) << endl
//         << "Rosa " << sRosa1.intercecao(sRosa2) << endl
//         << "Laranja " << sLaranja1.intercecao(sLaranja2) << endl
//         << "Azul x Rosa " << sAzul1.intercecao(sRosa1) << endl;


//}

//// Saida esperada
////Vermelho (2.14286,4.57143)
////Verde (5.14286,5.14286)
////Azul (6,7.5)
////Rosa (6.5,2)
////Laranja (5,3)
////Azul x Rosa (0,0)
