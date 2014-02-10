#ifndef ESCUTAEVENTOMOUSE_H
#define ESCUTAEVENTOMOUSE_H

#include <list>
#include "mouseevento.h"

using namespace std;

/// @todo - Talvez não seja necessario esta classe
class EscutaEventoMouse
{
protected:
    list<EscutaEventoMouse*> m_escutas;
public:

    EscutaEventoMouse();

//    virtual void mouseSolto(MouseEvento *mouseEvento);

};

#endif // ESCUTAEVENTOMOUSE_H
