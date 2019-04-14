#ifndef LISTA_SEQUENCIAL_STRING_H 
#define LISTA_SEQUENCIAL_STRING_H 

#include "curso.h"
#include<string>


typedef int TipoApontador;

class ListaSequencialCurso{
private:
    Curso* Item;
    TipoApontador Primeiro, Ultimo;
    int TAM;
public:
    ListaSequencialCurso(int n);
    ~ListaSequencialCurso();

    void Adiciona(Curso& elemento);
    bool Vazia();
    void Imprime();
    Curso operator[] (int indice) const;
};





#endif /* LISTA_SEQUENCIAL_STRING__H */