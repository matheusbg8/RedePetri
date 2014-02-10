#ifndef DESENHISTA_H
#define DESENHISTA_H

class Desenhista
{

    virtual void desenhaTexto(int x, int y, const string & str, char fonte) = 0;
    virtual void redesenha() = 0;

};

#endif // DESENHISTA_H
