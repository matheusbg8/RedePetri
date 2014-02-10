#ifndef ESCUTAMOUSE_H
#define ESCUTAMOUSE_H

#include "Observer.h"

class EscutaMouse: public Observer
{
public:
    EscutaMouse();

    void adiciona();
    void remove();
};

#endif // ESCUTAMOUSE_H
