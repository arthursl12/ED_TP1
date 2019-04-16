#include <cstdio>
#include <string>
#include <iostream>

#include "lista.h"





int main(int argc, char* argv[]){
    Candidato c1("Joao da Silva", 765.87,1,23);
    Candidato c2("Manuel da Silva", 722.87,2,3);
    ListaEncadeadaCandidato L;
    L.AdicionaInicio(c1);
    L.AdicionaInicio(c2);
    
    std::cout << "ADD" << std::endl;
    Candidato c4 = L.Consulta(0);
    std::cout << "FIM1";
    L.Consulta(1).get_nome() == c1.get_nome();
    std::cout << "FIM";

    return 0;
}


