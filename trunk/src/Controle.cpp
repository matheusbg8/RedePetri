#include "Controle.h"
#include <cstring>
#include <cstdio>


void Controle::comando(char *cmd)
{
    if(strcmp(cmd, "dimensiona_rede"))
    {
        printf("dimensionando rede...\n");
    }else if(strcmp(cmd, "novo_arco"))
    {
        printf("Criando novo arco...\n");
    }else if(strcmp(cmd, "exclui"))
    {
        printf("Excluindo...\n");
    }else if(strcmp(cmd, "novo_lugar"))
    {
        printf("Criando novo lugar...\n");
    }else if(strcmp(cmd, "nova_transicao"))
    {
        printf("Criando nova transicao...\n");
    }
}

Controle::Controle()
{
}
