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
    
    
public:
    ListaEncadeada();
    ~ListaEncadeada();

    Celula<T>* Pesquisa(int i);
    Celula<Candidato>* Pesquisa(Candidato& cand);

    void AdicionaInicio(T& novo);
    void Adiciona(T& novo, int i);
    void AdicionaFim(T& novo);
    void Adiciona(Candidato& cand);
    
    T* RetiraUltimo();
    T* RetiraPrimeiro();
    T* Retira(int i);

    T Consulta(int i);
    bool Vazia();
    int get_n_elementos();
    int get_indice(Candidato& cand);
};




#endif /* LISTA_ENCADEADA_H */