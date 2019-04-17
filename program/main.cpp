#include <cstdio>
#include <string>
#include <iostream>

#include "lista.h"

int main(int argc, char* argv[]){
    Candidato c1("Joao da Silva", 765.87,1,23);
    Candidato c2("Manuel da Silva", 722.87,2,3);
    Candidato c3("Maria da Silva", 622.87,0,2);
    Candidato c4("Joana da Silva", 627.83,1,2);
    Candidato c5("Mario da Silva", 657.93,5,1);
    ListaEncadeada<Candidato> L;

    L.Adiciona(c1,0);
    L.Consulta(0).get_nome() == c1.get_nome();

    L.Adiciona(c2,0);
    L.Consulta(0).get_nome() == c2.get_nome();
    L.Consulta(1).get_nome() == c1.get_nome();

    L.Adiciona(c3,1);
    L.Consulta(0).get_nome() == c2.get_nome();
    L.Consulta(1).get_nome() == c3.get_nome();
    L.Consulta(2).get_nome() == c1.get_nome();

    L.Adiciona(c4,3);
    L.Consulta(0).get_nome() == c2.get_nome();
    L.Consulta(1).get_nome() == c3.get_nome();
    L.Consulta(2).get_nome() == c1.get_nome();
    L.Consulta(3).get_nome() == c4.get_nome();

    return 0;
}


