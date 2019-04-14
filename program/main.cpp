#include <cstdio>
#include <string>
#include <iostream>

#include "listacurso.h"





int main(int argc, char* argv[]){
    ListaSequencialCurso minhalista(2);
    Curso ola("Ola",1), mundo("Mundo",0);
    minhalista.Adiciona(ola);
    minhalista.Adiciona(mundo);
    minhalista.Imprime();

    return 0;
}


