#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H


#include "Grafo.h"
#include "Matriz.h"
#include "GerenciadorElementos.h"

class GrafoMatriz//: public Grafo
{
private:
protected:
    Matriz <int> matriz;
    GerenciadorElementos<VerticeGrafo> elementos;

public:
    GrafoMatriz();



};

#endif // GRAFOMATRIZ_H
