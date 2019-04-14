#include <cstdio>
#include <string>
#include <iostream>

#include "listaseq.h"





int main(int argc, char* argv[]){
    ListaSequencial<std::string> minhalista(2);
    TipoItem<std::string> ola("Ola",1), mundo("Mundo",2);
    minhalista.Adiciona("ola");
    minhalista.Adiciona("mundo");
    minhalista.Imprime();

    return 0;
}


