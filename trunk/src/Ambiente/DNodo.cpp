#include "DNodo.h"

DNodo::DNodo(int id, QString nome, QString valor)
{
    setNome(nome);
    setValor(valor);
    setNodoID(id);
}

void DNodo::setValor(QString valor)
{
    m_valor = valor;
}

QString DNodo::valor()
{
    return m_valor;
}

void DNodo::setNodoID(int id)
{
    m_id = id;
}

int DNodo::nodoId()
{
    return m_id;
}

void DNodo::desenha()
{
    desenhaTexto(m_valor, rPonto(-10,-15));
    Circulo::desenha();
}


