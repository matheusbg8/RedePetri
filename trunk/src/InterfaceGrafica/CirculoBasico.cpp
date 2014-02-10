#include "CirculoBasico.h"

#include <iostream>
using namespace std;

void Circulo::inicializaCirculo()
{
    setNome(QString("Circulo %1").arg(id()));
    m_tipoDesenho = TD_CIRCULO;

}

Circulo::Circulo(Container *pai):Desenho(pai)
{
    m_raio = 15;
    rPonto p(50 , 50);
    defineCirculo(15 , p);
}

Circulo::Circulo(int raio, rPonto p, Container *pai):Desenho(pai)
{
    inicializaCirculo();
    defineCirculo(raio , p);
}

Circulo::~Circulo()
{
}

//void MCirculo::novoDesenho(Desenho *d)
//{
//    if(pai != 0x0)
//    {
//        pai->novoDesenho(d);
//    }else
//    {
//        cout << "Não é possivel criar desenhos em circulos" << endl;
//        delete d;
//    }
//}

Desenho * Circulo::novaInstancia() const
{
    return copiaCirculo();
}

Circulo *Circulo::copiaCirculo() const
{
    Circulo *c = new Circulo(m_raio, posicaoLocal());
    copiaMeusParametros(c);
    return c;
}

void Circulo::desenha()
{
//    desenhaContainer();
    rPonto glP = minhaPosicaoGlobal();
    float px = glP.x() + m_raio,
          py = glP.y() + m_raio, x , y;

//    cout << "Desenhando circulo raio " << raio << " p (" << px << " , " << py << ")" << endl;
    glBegin(GL_POLYGON);
        glColor3f(m_corFundo.r(),m_corFundo.g(),m_corFundo.b());
        for (int i = 0; i <= 100; i+=5)
        {
            x = px + m_raio*sin(2*3.1415927 * i/100.0);
            y = py + m_raio*cos(2*3.1415927 * i/100.0);
            glVertex2f(x, y);
        }
    glEnd();
    glBegin(GL_LINE_STRIP);
        glColor3f(m_corBorda.r(),m_corBorda.g(),m_corBorda.b());
        for (int i = 0; i <= 100; i+=5)
        {
            x = px + m_raio*sin(2*3.1415927 * i/100.0);
            y = py + m_raio*cos(2*3.1415927 * i/100.0);
            glVertex2f(x, y);
        }
    glEnd();

    desenhaNome();
    desenhaIdDesenho();

}

bool Circulo::contemrPonto(const rPonto &p)
{
    if(!Desenho::contemrPonto(p))
        return false;
    /*
        cout << "MCirculo::contemrPonto p (" << p.x() << " , " << p.y() << " )" << endl;
        cout << "MCirculo::contemrPonto dp(" << dPosicaoLocal.x() << " , " << dPosicaoLocal.y() << " )" << endl;
        cout << "MCirculo::contemrPonto gp(" << gp.x() << " , " << gp.y() << " )" << endl;
    */

    float cx = m_raio + m_espaco.x(), cy = m_raio + m_espaco.y(), // Posicao do raio
          px = p.x()                      , py = p.y(),                       // Ponto que esta sendo testado
          dx = cx - px                    , dy = cy - py;                     // Dif posica raio e ponto testado
    if( dx*dx + dy*dy <= m_raio*m_raio)  // Testa as distancias quadradas
        return true;
    return false;
}


/**
 * @brief
 *      Define o raio e a posição do circulo.
 * @param raio - raio
 * @param p - posição no referencial do desenho pai.
 */
void Circulo::defineCirculo(int raio, const rPonto &p)
{
    rPonto minP( p.x() - raio  , p.y() -   raio);
    int doisraio = 2*raio;
    this->m_raio = raio;
    defineDesenho(minP , doisraio, doisraio);
}

void Circulo::setCentro(const rPonto &posicao)
{
    int diametro = 2*m_raio;
//    rPonto minP(posicao.x() - raio , posicao.y() - raio);
    defineDesenho(posicao - m_raio, diametro, diametro);
}

bool Circulo::mousePrecionado(MouseEvento *e)
{
    Desenho::mousePrecionado(e);
}


bool Circulo::mouseMovendo(MouseEvento *e)
{
//    cout << "Mvendo ciculo" << endl;
//    defineCirculo(raio , e->pLocal);
//    redesenha();
    Desenho::mouseMovendo(e);
}

rPonto Circulo::getCentro()
{
    return posicaoLocal() + rPonto(m_raio, m_raio);
}

void *Circulo::getSuper()
{
    return this;
}

float Circulo::raio()
{
    return m_raio;
}


/**
 * @brief
 *  Retorna o ponto de intersecção da reta, formada
 * pelo ponto pInicialReta e o centro da circunferencia
 * , com a borda da circunferencia.
 * @param pInicialReta - Ponto inicial da reta
 * @return rPonto - Ponto de intersecção da reta com a borda
 * da circunferencia.
 */
rPonto Circulo::posicaoLigacao(const rPonto &pInicialReta)
{ // O ponto de intersecção foi encontrado multiplicado
  // o vetor unitario da reta pelo raio do ciculo, depois
  // somando seu centro.
    rPonto centro = getCentro(),
           vr = pInicialReta - centro;
    // Trata divisao por zero
    if(vr.x() > -1e-6 && vr.x() < 1e-6 &&
       vr.y() > -1e-6 && vr.y() < 1e-6)
        vr.setY(1);

    rPonto resp = centro + vr.uni() * m_raio;
    return resp;
}

