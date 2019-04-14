#ifndef LISTA_SEQUENCIAL_STRING_H 
#define LISTA_SEQUENCIAL_STRING_H 

#include "itemstring.h"
#include<string>


typedef int TipoApontador;

class ListaSequencialString{
private:
    ItemString* Item;
    TipoApontador Primeiro, Ultimo;
public:
    ListaSequencialString(int n);
    ~ListaSequencialString();

    void Adiciona(ItemString elemento);
    bool Vazia();
    void Imprime();
    ItemString operator[] (int indice) const;
};





#endif /* LISTA_SEQUENCIAL_STRING__H */