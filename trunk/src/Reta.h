#ifndef RETA_H
#define RETA_H

#include "Utilidades.h"

class Reta
{
private:
    rPonto m_p;
    rPonto m_v;

/* eq simetrica
 * (x -x0)/vx = (y - y0)/vy
 * x = x0 + vx * (y - y0) / vy
 * y = y0 + vy * (x - x0) / vx
*/

/* eq parametrica
 * x = x0 + vx*t
 * y = y0 + vy*t
*/

public:

    Reta();

    void defineReta2P(const rPonto &p1,const rPonto &p2);
    void defineRetaPV(const rPonto &p,const rPonto &v);



};

#endif // RETA_H
