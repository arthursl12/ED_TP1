#ifndef LISTASEQ_H 
#define LISTASEQ_H

typedef int TipoChave;
typedef int TipoApontador;

template<class T>
class TipoItem{
private:
    TipoChave Chave;
    T Dado;
public:
    TipoItem(T _Dado, TipoChave _chave);
};

template<class T>
class ListaSequencial{
private:
    T Item[32];
    TipoApontador Primeiro, Ultimo;
public:
    ListaSequencial(int n);
    ~ListaSequencial();

    void Adiciona(T elemento);
    bool Vazia();
    void Imprime();
};





#endif /* LISTA_SEQUENCIAL_H */