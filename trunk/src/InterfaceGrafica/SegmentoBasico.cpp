#include "SegmentoBasico.h"

SegmentoBasico::SegmentoBasico(const rPonto &ini , const rPonto& fim)
{
    m_ini = ini;
    m_fim = fim;
}

bool SegmentoBasico::temIntercecao(const SegmentoBasico &seg) const
{

    float mix = m_ini.x(), miy = m_ini.y(),
          mfx = m_fim.x(), mfy = m_fim.y(),
          six = seg.inicio().x() , siy = seg.inicio().y(),
          sfx = seg.fim().x(),     sfy = seg.fim().y(),
          det = (sfx - six) * (mfy - miy) - (sfy - siy) * (mfx - mix);

    if(det > -1e-5 && det < 1e-5)
        return 0;

    float s = ((sfx - six) * (siy - miy) - (sfy - siy) * (six - mix)) / det,
          t = ((mfx - mix) * (siy - miy) - (mfy - miy) * (six - mix)) / det;

//    cout << "S = " << s << " T = " << t << endl;
    return s >= 0.f && s <= 1.f && t >= 0.f && t <= 1.f;
}

float SegmentoBasico::intercecaoS(const SegmentoBasico &seg) const
{
    float mix = m_ini.x(), miy = m_ini.y(),
          mfx = m_fim.x(), mfy = m_fim.y(),
          six = seg.inicio().x() , siy = seg.inicio().y(),
          sfx = seg.fim().x(),     sfy = seg.fim().y(),
          det = (sfx - six) * (mfy - miy) - (sfy - siy) * (mfx - mix);

    if(det > -1e-5 && det < 1e-5)
        return 0;

    float s = ((sfx - six) * (siy - miy) - (sfy - siy) * (six - mix)) / det,
          t = ((mfx - mix) * (siy - miy) - (mfy - miy) * (six - mix)) / det;

//    cout << "S = " << s << " T = " << t << endl;
    if(s >= 0 && s <= 1.f && t >= 0 && t <= 1)
        return s;
    else
        return -1;
}

rPonto SegmentoBasico::intercecao(const SegmentoBasico &seg) const
{
    float mix = m_ini.x(), miy = m_ini.y(),
          mfx = m_fim.x(), mfy = m_fim.y(),
          six = seg.inicio().x() , siy = seg.inicio().y(),
          sfx = seg.fim().x(),     sfy = seg.fim().y(),
          det = (sfx - six) * (mfy - miy) - (sfy - siy) * (mfx - mix);

    if(det > -1e-5 && det < 1e-5)
        return rPonto(0,0);

    float s = ((sfx - six) * (siy - miy) - (sfy - siy) * (six - mix)) / det,
          t = ((mfx - mix) * (siy - miy) - (mfy - miy) * (six - mix)) / det;

//    cout << "S = " << s << " T = " << t << endl;
    if(s >= 0.f && s <= 1.f && t >= 0.f && t <= 1.f)
        return rPonto(mix + (mfx-mix)*s, miy + (mfy-miy)*s);
    return rPonto(0,0);
}

rPonto SegmentoBasico::intercecao(const RetanguloBasico &r) const
{
    float mix = m_ini.x(), miy = m_ini.y(),
            mfx = m_fim.x(), mfy = m_fim.y();

    SegmentoBasico si(r.pontoInferiorEsquerdo(), r.pontoInferiorDireito()),
            ss(r.pontoSuperiorEsquerdo(), r.pontoSuperiorDireito()),
            sle(r.pontoSuperiorEsquerdo(),r.pontoInferiorEsquerdo()),
            sld(r.pontoSuperiorDireito() , r.pontoInferiorDireito());

    float s;
    s = intercecaoS(si);
    if(s >= 0.f && s <= 1.f)
    {
        cout << "OK si" << endl;
        return rPonto(mix + (mfx-mix)*s, miy + (mfy-miy)*s);
    }

    s = intercecaoS(ss);
    if(s >= 0.f && s <= 1.f)
    {
        cout << "OK ss" << endl;
        return rPonto(mix + (mfx-mix)*s, miy + (mfy-miy)*s);
    }

    s = intercecaoS(sle);
    if(s >= 0.f && s <= 1.f)
    {
        cout << "OK sle" << endl;
        return rPonto(mix + (mfx-mix)*s, miy + (mfy-miy)*s);
    }

    s = intercecaoS(sld);
    if(s >= 0.f && s <= 1.f)
    {
        cout << "OK sld" << endl;
        return rPonto(mix + (mfx-mix)*s, miy + (mfy-miy)*s);
    }

    return rPonto(0,0);
}

void SegmentoBasico::setInicio(const rPonto &inicio)
{
    m_ini = inicio;
}

void SegmentoBasico::setFim(const rPonto &fim)
{
    m_fim = fim;
}

const rPonto SegmentoBasico::inicio() const
{
    return m_ini;
}

const rPonto SegmentoBasico::fim() const
{
    return m_fim;
}

const float SegmentoBasico::comprimento() const
{
    return distancia(m_ini, m_fim);
}
