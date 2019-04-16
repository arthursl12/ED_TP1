#ifndef LISTA_ENCADEADA_CANDIDATO_H
#define LISTA_ENCADEADA_CANDIDATO_H

#include "candidato.h"

typedef struct Celula{
    Candidato cand;
    Candidato* prox;
} Celula;

class ListaEncadeadaCandidato{
private:
    Celula* ultimo;
    Celula* primeiro;
    int n_elementos;
public:
    ListaEncadeadaCandidato();
    ~ListaEncadeadaCandidato();

    void AdicionaInicio(Candidato novo);
    void Adiciona(Candidato novo, int i);
    void AdicionaFim(Candidato novo);
    
    Candidato* RetiraUltimo();
    Candidato* RetiraPrimeiro();
    Candidato* Retira(int i);

    Candidato* Consulta(int i);
    bool Vazia();
};




#endif /* LISTA_ENCADEADA_CANDIDATO_H */