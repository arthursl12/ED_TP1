#ifndef LISTA_SEQUENCIAL_STRING_H 
#define LISTA_SEQUENCIAL_STRING_H 

#include<string>

typedef std::string TipoChave;
typedef int TipoApontador;

class ItemString{
private:
    TipoChave Chave;
    std::string Dado;
public:
    ItemString(std::string _Dado);
    ItemString();
    std::string get_dado();
};

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
};





#endif /* LISTA_SEQUENCIAL_STRING__H */