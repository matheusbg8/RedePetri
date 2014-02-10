#ifndef DNODO_H
#define DNODO_H

#include <QString>
#include "CirculoBasico.h"

class DNodo : public Circulo
{
    QString m_valor;
    int m_id;

public:
    DNodo(int id,QString nome, QString valor);

    void setValor(QString valor);
    QString valor();

    void setNodoID(int id);
    int nodoId();

    // Iterface opcional Circulo
    void desenha();

};

#endif // DNODO_H
