#ifndef LISTA_ENCADEADA_CANDIDATO_H
#define LISTA_ENCADEADA_CANDIDATO_H

#include "candidato.h"

typedef struct Celula{
    Candidato cand;
    Celula* prox;
    
    // Construtor inicializador para Celula_str
    Celula(Candidato _cand)
    :cand(_cand){}
} Celula;


class ListaEncadeadaCandidato{
private:
    Celula* ultimo;
    Celula* primeiro;
    int n_elementos;

    Celula* Pesquisa(int i);
public:
    ListaEncadeadaCandidato();
    ~ListaEncadeadaCandidato();

    void AdicionaInicio(Candidato& novo);
    void Adiciona(Candidato& novo, int i);
    void AdicionaFim(Candidato& novo);
    
    Candidato* RetiraUltimo();
    Candidato* RetiraPrimeiro();
    Candidato* Retira(int i);

    Candidato Consulta(int i);
    bool Vazia();
};




#endif /* LISTA_ENCADEADA_CANDIDATO_H */