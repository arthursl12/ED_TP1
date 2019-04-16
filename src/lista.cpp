#include "lista.h"
#include <stdexcept>
#include <iostream>

/* Cria uma lista vazia, apenas com a célula cabeça */
ListaEncadeadaCandidato::ListaEncadeadaCandidato(){
    /* Cria célula-cabeça */
    Celula *cabeca = (Celula*) malloc(sizeof(Celula));
    this->primeiro = cabeca;

    this->ultimo = this->primeiro;
    this->primeiro->prox = nullptr;
    this->n_elementos = 0;
}

/* Destrutor da lista, libera a memória alocada */
ListaEncadeadaCandidato::~ListaEncadeadaCandidato(){
    Celula* atual;
    Celula* proximo;

    // Liberar a célula-cabeça
    atual = this->primeiro;
    proximo = this->primeiro->prox;
    free(atual); 

    // Liberar as células seguintes
    while (proximo != nullptr){
        atual = proximo;
        proximo = atual->prox;
        delete atual;
    }
    this->primeiro = nullptr;
    this->ultimo = nullptr;
}

/* Adiciona o candidato no início da lista */
void ListaEncadeadaCandidato::AdicionaInicio(Candidato& novo){
    // Cria a nova célula
    Celula* nova_celula;
    nova_celula = new Celula(novo);

    // Coloca ela no lugar da primeira célula (depois da cabeça, obviamente)
    nova_celula->prox = this->primeiro->prox;
    this->primeiro->prox = nova_celula;

    // Arruma o ponteiro do último
    if (this->n_elementos == 0){
        this->ultimo = nova_celula;
    }

    // Adiciona um ao contador de elementos
    this->n_elementos++;
}

/* Adiciona o candidato no fim da lista */
void ListaEncadeadaCandidato::AdicionaFim(Candidato& novo){
    // Cria a nova célula
    Celula* nova_celula;
    nova_celula = new Celula(novo);

    // Coloca no último lugar
    nova_celula->prox = nullptr;
    this->ultimo->prox = nova_celula;
    this->ultimo = nova_celula;

    // Adiciona um ao contador de elementos
    this->n_elementos++;
}

/* Adiciona o candidato na posição de índice i da lista */
void ListaEncadeadaCandidato::Adiciona(Candidato& novo, int i){
    if (i == 0){
        // Adicionar no início
        this->AdicionaInicio(novo);
    }else if (i == this->n_elementos-1){
        // Adicionar no final
        this->AdicionaFim(novo);
    }else{
        // Cria a nova célula
        Celula* nova_celula;
        nova_celula = new Celula(novo);
        nova_celula->prox = nullptr;

        Celula* atual = this->primeiro->prox; // j = 0 (posição 0)
        for (int j = 0; j != i-1; j++){
            atual = atual->prox;
        } // Encontrar o anterior à posição de interesse
        nova_celula->prox = atual->prox;
        atual->prox = nova_celula;

        // Adiciona um ao contador de elementos
        this->n_elementos++;
    }
}

/* Retorna true se a lista está vazia, false do contrário */
bool ListaEncadeadaCandidato::Vazia(){
    return (this->n_elementos == 0 && this->primeiro == this->ultimo);
}

Candidato ListaEncadeadaCandidato::Consulta(int i){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista Vazia");
    if (i < 0 || i >= this->n_elementos)
        throw std::out_of_range("Indice invalido");
    
    if (i == 0){
        // Primeiro elemento
        return this->primeiro->prox->cand;
    }else if (i == this->n_elementos-1){
        // Último elemento
        return this->ultimo->cand;
    }else{
        Celula* atual = this->primeiro->prox; // j = 0 (posição 0)
        for (int j = 0; j != i-1 ; j++){
            atual = atual->prox;
        } // Encontrar o anterior à posição de interesse
        return atual->prox->cand;
    }
}

Candidato& ListaEncadeadaCandidato::RetiraUltimo(){}
Candidato& ListaEncadeadaCandidato::RetiraPrimeiro(){}
Candidato& ListaEncadeadaCandidato::Retira(int i){}
