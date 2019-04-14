#include <cstdio>
#include <string>
#include <iostream>

#include "listaseqstring.h"





int main(int argc, char* argv[]){
    ListaSequencialString minhalista(2);
    ItemString ola("Ola"), mundo("Mundo");
    minhalista.Adiciona(ola);
    minhalista.Adiciona(mundo);
    minhalista.Imprime();

    return 0;
}


