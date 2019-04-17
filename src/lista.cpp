#include "lista.h"
#include "curso.h"
#include <stdexcept>
#include <iostream>

/* Cria uma lista vazia, apenas com a célula cabeça */
template<class T>
ListaEncadeada<T>::ListaEncadeada(){
    /* Cria célula-cabeça */
    Celula<T> *cabeca = (Celula<T>*) malloc(sizeof(Celula<T>));
    this->primeiro = cabeca;

    this->ultimo = this->primeiro;
    this->primeiro->prox = nullptr;
    this->n_elementos = 0;
}

/* Destrutor da lista, libera a memória alocada */
template<class T>
ListaEncadeada<T>::~ListaEncadeada(){
    Celula<T>* atual;
    Celula<T>* proximo;

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

/* Adiciona o objeto no início da lista */
template<class T>void 
ListaEncadeada<T>::AdicionaInicio(T& novo){
    // Cria a nova célula
    Celula<T>* nova_celula;
    nova_celula = new Celula<T>(novo);

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

/* Adiciona o objeto no fim da lista */
template<class T>void 
ListaEncadeada<T>::AdicionaFim(T& novo){
    // Cria a nova célula
    Celula<T>* nova_celula;
    nova_celula = new Celula<T>(novo);

    // Coloca no último lugar
    nova_celula->prox = nullptr;
    this->ultimo->prox = nova_celula;
    this->ultimo = nova_celula;

    // Adiciona um ao contador de elementos
    this->n_elementos++;
}

/* Adiciona o objeto na posição de índice i da lista */
template<class T>void 
ListaEncadeada<T>::Adiciona(T& novo, int i){
    if (i > n_elementos)
        throw std::out_of_range("Indice invalido");
    
    if (i == 0){
        // Adicionar no início
        this->AdicionaInicio(novo);
    }else if (i == this->n_elementos){
        // Adicionar no final
        this->AdicionaFim(novo);
    }else{
        // Cria a nova célula
        Celula<T>* nova_celula;
        nova_celula = new Celula<T>(novo);
        nova_celula->prox = nullptr;

        Celula<T>* anterior = this->primeiro; // j = 0 (posição 0)
        for (int j = 0; j != i; j++){
            anterior = anterior->prox;
        } // Encontrar o anterior à posição de interesse
        nova_celula->prox = anterior->prox;
        anterior->prox = nova_celula;

        // Adiciona um ao contador de elementos
        this->n_elementos++;
    }
}

/* Retorna true se a lista está vazia, false do contrário */
template<class T>bool 
ListaEncadeada<T>::Vazia(){
    return (this->n_elementos == 0 && this->primeiro == this->ultimo);
}

/* Retorna uma cópia do objeto na posição de índice i */
template<class T>
T ListaEncadeada<T>::Consulta(int i){
    return this->Pesquisa(i)->objeto;
}

/* Retorna o ponteiro da célula na posição de índice i */
template<class T>
Celula<T>* ListaEncadeada<T>::Pesquisa(int i){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista Vazia");
    if (i < 0 || i >= this->n_elementos)
        throw std::out_of_range("Indice invalido");
    
    if (i == 0){
        // Primeiro elemento
        return this->primeiro->prox;
    }else if (i == this->n_elementos-1){
        // Último elemento
        return this->ultimo;
    }else{
        Celula<T>* atual = this->primeiro->prox; // j = 0 (posição 0)
        for (int j = 1; j != i ; j++){
            atual = atual->prox;
        } // Encontrar o anterior à posição de interesse
        return atual->prox;
    }
}

/* Retira o último e retorna o retirado por referência */
template<class T>
T* ListaEncadeada<T>::RetiraUltimo(){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista vazia");
    if (this->n_elementos == 1)
        return this->RetiraPrimeiro();
    
    // Encontra o antes do último e o último
    Celula<T>* ant_fim = this->Pesquisa(this->n_elementos-2);
    Celula<T>* fim = this->ultimo;

    // Rearranja os ponteiros
    ant_fim->prox = nullptr;
    this->ultimo = ant_fim;
    
    // Decrementa o contador
    this->n_elementos--;

    T* c = new T(fim->objeto);
    delete (fim);
    return c;
}

template<class T>
T* ListaEncadeada<T>::RetiraPrimeiro(){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista vazia");
    
    // Basta rearranjar os ponteiros da célula-cabeça
    Celula<T>* cabeca = this->primeiro;
    Celula<T>* eliminar = this->primeiro->prox;
    cabeca->prox = eliminar->prox;

    if (this->n_elementos == 1){
        // Se for a lista só tiver um elemento
        this->ultimo = cabeca;
    }


    // Decrementa o contador
    this->n_elementos--;

    T* c = new T(eliminar->objeto);
    delete (eliminar);
    return c;
}

template<class T>
T* ListaEncadeada<T>::Retira(int i){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista vazia");
    if (i > n_elementos)
        throw std::out_of_range("Indice invalido");
    
    if (i == 0){
        // Retirar o primeiro elemento
        return this->RetiraPrimeiro();
    }else if(i == this->n_elementos-1){
        // Retirar o último elemento
        return this->RetiraUltimo();
    }else{
        Celula<T>* anterior = this->primeiro;
        for (int j = 0; j != i; j++){
            anterior = anterior->prox;
        } // Encontra a célula anterior;

        // Rearrumar os ponteiros
        Celula<T>* eliminar = anterior->prox;
        anterior->prox = eliminar->prox;

        // Decrementa o contador
        this->n_elementos--;

        T *c = new T(eliminar->objeto);
        delete(eliminar);
        return c;
    }
}

/* Permite que os seguintes templates sejam válidos, permitindo a compilação */
template class ListaEncadeada<Candidato>;
template class ListaEncadeada<Curso>;