#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include "candidato.h"

template<class T>
struct Celula{
    T objeto;
    Celula* prox;
    Celula* ant;
    
    // Construtor inicializador para Celula_str
    Celula(T _obj)
    :objeto(_obj){}
};

template<class T>
class ListaEncadeada{
private:
    Celula<T>* ultimo;
    Celula<T>* primeiro;
    int n_elementos;

    Celula<T>* Pesquisa(int i);
public:
    ListaEncadeada();
    ~ListaEncadeada();

    void AdicionaInicio(T& novo);
    void Adiciona(T& novo, int i);
    void AdicionaFim(T& novo);
    
    T* RetiraUltimo();
    T* RetiraPrimeiro();
    T* Retira(int i);

    T Consulta(int i);
    bool Vazia();
    int get_n_elementos();
};




#endif /* LISTA_ENCADEADA_H */