#ifndef TRANSICAO_H
#define TRANSICAO_H

#include <string>
#include <vector>
#include "ComponentePetri.h"

using namespace std;

class Transicao : public ComponentePetri
{
private:
    bool Sensibilizado;
    int Ciclo_Sensibilizado;
    bool Desenhado;
    short int grau;

    int lID;  /**< ID local da transição */
    string nome;
    string info;

    // Implementação da interface ComponentePetri

    TipoComponentePetri meuTipoComponentePetri();

public:

    vector < string > CondVal;
    vector < string > CondVar;

    vector < string > AcaoVal;
    vector < string > AcaoVar;

    Transicao(const Transicao &T);
    Transicao(int IDGlobal=-1, int IDLocal=-1);

    int getIDLocal() const;

    string getNome();
    void setNome(string nome);

    friend class RedePetri;
};


#endif // TRANSICAO_H
