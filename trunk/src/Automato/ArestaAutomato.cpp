#include "ArestaAutomato.h"

ArestaAutomato::ArestaAutomato(const char *simbulosAceitos):
    m_simbulos(simbulosAceitos)
{
    m_negado = false;
}

bool ArestaAutomato::aceitaSimbolo(char s)
{
    if(m_negado)
        return ! (m_simbulos.find(s) != string::npos);
    else
        return m_simbulos.find(s) != string::npos;
}

void ArestaAutomato::setSimbulosAceitos(const char *simbulos)
{
    if(simbulos != 0x0)
        m_simbulos = string(simbulos);
    else
        m_simbulos = string("");
}

const char *ArestaAutomato::simbulosAceitos() const
{
    return m_simbulos.c_str();
}

void ArestaAutomato::setNegado(bool negarAceitacao)
{
    m_negado = negarAceitacao;
}

ArestaGrafo *ArestaAutomato::novaAresta()
{
    return new ArestaAutomato("");
}
