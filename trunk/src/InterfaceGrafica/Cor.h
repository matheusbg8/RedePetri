#ifndef COR_H
#define COR_H

#include <iostream>
using namespace std;

/**
 * @brief
 *  Esta classe foi criada para gerenciar as cores
 * dos desenhos.
 */
class Cor
{
private:
    float vr;
    float vg;
    float vb;
public:    
    Cor(float r = 0.0 , float g = 0.0 , float b = 0.0);
    Cor(const Cor &cor);

    float r() const;
    void r(float val);
    float g() const;
    void g(float val);
    float b() const;
    void b(float val);

    void set(float r, float g, float b);

    static const Cor verde;
    static const Cor vermelho;
    static const Cor azul;
    static const Cor amarelo;
    static const Cor preto;
    static const Cor branco;
    static const Cor magenta;
    static const Cor ciano;

    friend ostream& operator << (ostream &os , Cor & cor);
};

ostream & operator << (ostream &os , Cor & cor);


#endif // COR_H
