#include "lista.h"
#include "curso.h"
#include <stdexcept>
#include <iostream>

template<class T>
/* Cria uma lista vazia, apenas com a célula cabeça */
ListaEncadeada<T>::ListaEncadeada(){
    /* Cria célula-cabeça */
    Celula<T> *cabeca = new Celula<T>();;
    this->primeiro = cabeca;
    this->ultimo = this->primeiro;

    /* Define o iterador */
    this->pos = this->primeiro;

    this->primeiro->prox = nullptr;
    this->primeiro->ant = nullptr;
    this->n_elementos = 0;
}

template<class T>
/* Destrutor da lista, libera a memória alocada */
ListaEncadeada<T>::~ListaEncadeada(){
    Celula<T>* atual = this->primeiro;
    Celula<T>* proximo = atual->prox;

    // Liberar as células seguintes
    while (proximo != nullptr){
        atual = proximo;
        proximo = atual->prox;
        delete atual;
    }
    this->primeiro = nullptr;
    this->ultimo = nullptr;
}

template<class T>
/* Adiciona o objeto no início da lista */
void ListaEncadeada<T>::AdicionaInicio(T& novo){
    // Cria a nova célula
    Celula<T>* nova_celula = new Celula<T>();
    nova_celula->objeto = new T(novo);

    // Coloca ela no lugar da primeira célula (depois da cabeça, obviamente)
    nova_celula->prox = this->primeiro->prox;
    this->primeiro->prox = nova_celula;
    nova_celula->ant = this->primeiro;

    // Define o ponteiro 'anterior' da célula seguinte
    if (this->n_elementos != 0){
        // Nova célula não é a última, logo existe um próximo elemento
        nova_celula->prox->ant = nova_celula;
    }else{
        /* Nova célula é a última, logo não tem-se que arrumar o anterior da 
        célula seguinte à nova, basta arrumar o ponteiro do último */
        this->ultimo = nova_celula;
    }

    // Adiciona um ao contador de elementos
    this->n_elementos++;
}


template<class T>
/* Adiciona o objeto no fim da lista */
void ListaEncadeada<T>::AdicionaFim(T& novo){
    // Cria a nova célula
    Celula<T>* nova_celula = new Celula<T>();
    nova_celula->objeto = new T(novo);

    // Coloca no último lugar
    nova_celula->prox = nullptr;
    nova_celula->ant = this->ultimo;
    this->ultimo->prox = nova_celula;
    this->ultimo = nova_celula;

    // Adiciona um ao contador de elementos
    this->n_elementos++;
}


template<class T>
/* Adiciona o objeto na posição de índice i da lista */
void ListaEncadeada<T>::Adiciona(T& novo, int i){
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
        Celula<T>* nova_celula = new Celula<T>();
        nova_celula->objeto = new T(novo);
        nova_celula->prox = nullptr;
        nova_celula->ant = nullptr;

        Celula<T>* cel_i = Pesquisa(i); // Célula na posição i
        nova_celula->prox = cel_i;
        nova_celula->ant = cel_i->ant;
        nova_celula->ant->prox = nova_celula;
        cel_i->ant = nova_celula;

        // Adiciona um ao contador de elementos
        this->n_elementos++;
    }
}

template<>
/* Adiciona um candidato nos cursos desejados, respeitando as regras do SISU */
void ListaEncadeada<Curso>::Adiciona(Candidato& cand){
}

template<>
/* Adiciona um candidato numa lista de Candidatos, respeitando os critérios de 
ordenação: nota, primeira opção e ordem de chegada */
void ListaEncadeada<Candidato>::Adiciona(Candidato& cand){
    
}

template<>
/* Procura um Candidato com nota menor ou igual à do Candidato pedido;
retorna o primeiro candidato com nota menor ou igual
retorna nullptr se o candidato pedido for o menor */
Celula<Candidato>* ListaEncadeada<Candidato>::Pesquisa(Candidato& cand){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista Vazia");

    Celula<Candidato>* atual = this->primeiro->prox; // j = 0 (posição 0)
    for (int j = 1; atual->objeto->get_nota() > cand.get_nota(); j++){    
        if (j == this->n_elementos){
            // Chegou no último e a nota ainda é maior, retorna nullptr
            return nullptr;
        }
        atual = atual->prox;
    } // Encontrar um com a nota igual ou menor
    return atual;
}

template<class T>
/* Retorna true se a lista está vazia, false do contrário */
bool ListaEncadeada<T>::Vazia(){
    return (this->n_elementos == 0 && this->primeiro == this->ultimo);
}

template<class T>
/* Retorna uma cópia do objeto na posição de índice i */
T ListaEncadeada<T>::Consulta(int i){
    return *this->Pesquisa(i)->objeto;
}

template<class T>
/* Retorna o ponteiro da célula na posição de índice i */
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
    }else if (i < this->n_elementos/2){
        // Até a metade, procure a partir do início
        Celula<T>* atual = this->primeiro->prox; // j = 0 (posição 0)
        for (int j = 1; j != i ; j++){
            atual = atual->prox;
        } // Encontrar o anterior à posição de interesse
        return atual->prox;
    }else{
        // Após a metade, procure voltando do fim
        Celula<T>* atual = this->ultimo; // j = n-1 (posição n-1)
        for (int j = this->n_elementos-1; j != i; j--){
            atual = atual->ant;
        } // Encontrar o elemento à posição de interesse
        return atual;
    }
}

template<class T>
/* Retira o último e retorna o ponteiro do retirado */
T* ListaEncadeada<T>::RetiraUltimo(){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista vazia");
    if (this->n_elementos == 1)
        return this->RetiraPrimeiro();
    
    // Encontra o antes do último e o último
    Celula<T>* ant_fim = this->ultimo->ant; /*<-- Custo constante (Lista Duplamente Encadeada)*/
    Celula<T>* fim = this->ultimo;

    // Rearranja os ponteiros
    ant_fim->prox = nullptr;
    this->ultimo = ant_fim;
    
    // Decrementa o contador
    this->n_elementos--;

    T *c = fim->objeto;
    fim->objeto = nullptr;
    delete fim;
    return c;
}

template<class T>
/* Retira o primeiro elemento e retorna um ponteiro para o retirado */
T* ListaEncadeada<T>::RetiraPrimeiro(){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista vazia");
    
    // Basta rearranjar os ponteiros da célula-cabeça
    Celula<T>* cabeca = this->primeiro;
    Celula<T>* eliminar = this->primeiro->prox;
    cabeca->prox = eliminar->prox;

    // Arrumar o ponteiro 'anterior' ou o último, dependendo do caso
    if (this->n_elementos == 1){
        /* Se for a lista só tiver um elemento, não tem célula seguinte, logo
        não precisa arrumar o ponteiro 'anterior' */
        this->ultimo = cabeca;
    }else{
        // Arrumar o 'anterior' da célula seguinte à eliminada
        cabeca->prox->ant = cabeca;
    }

    // Decrementa o contador
    this->n_elementos--;

    T *c = eliminar->objeto;
    eliminar->objeto = nullptr;
    delete eliminar;
    return c;
}


template<class T>
/* Retira um elemento da i-ésima posição e retorna um ponteiro para ele */
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
        Celula<T>* eliminar = this->Pesquisa(i);

        // Rearrumar os ponteiros
        eliminar->ant->prox = eliminar->prox;
        eliminar->prox->ant = eliminar->ant;

        // Decrementa o contador
        this->n_elementos--;

        T *c = eliminar->objeto;
        eliminar->objeto = nullptr;
        delete eliminar;
        return c;
    }
}

template<class T>
/* Retorna o número de elementos da lista */
int ListaEncadeada<T>::get_n_elementos(){
    return this->n_elementos;
}

template<>
/* Retorna o índice do candidato na lista */
int ListaEncadeada<Candidato>::get_indice(Candidato* cand){
    Celula<Candidato>* atual = this->primeiro->prox; // j = 0 (posição 0)
    int j;
    for (j = 1; atual->objeto->get_nome() != cand->get_nome() ; j++){
        atual = atual->prox;
    } // Encontrar o anterior à posição de interesse
    return j-1;
}

template <class T> 
T* ListaEncadeada<T>::_primeiro() {
    this->pos = this->primeiro; 
    return this->proximo();
}

template <class T> 
T* ListaEncadeada<T>::proximo() {
    this->pos = this->pos->prox;
    if (this->pos == nullptr) 
        return nullptr; 
    else 
        return this->pos->objeto;
}


/* Permite que os seguintes templates sejam válidos, permitindo a compilação */
template class ListaEncadeada<Candidato>;
template class ListaEncadeada<Curso>;