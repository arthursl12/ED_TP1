#include "lista.h"
#include "curso.h"
#include "candidato.h"
#include <stdexcept>
#include <iostream>

/* Permite que os seguintes templates sejam válidos, permitindo a compilação */
template class ListaEncadeada<Candidato>;
template class ListaEncadeada<Curso>;

template<class T>
/* Cria uma lista vazia, apenas com a célula cabeça */
ListaEncadeada<T>::ListaEncadeada(){
    /* Cria célula-cabeça */
    Celula<T> *cabeca = new Celula<T>;
    this->primeiro = cabeca;

    this->ultimo = this->primeiro;
    this->primeiro->prox = nullptr;
    this->primeiro->ant = nullptr;
    this->n_elementos = 0;
}

template<class T>
/* Destrutor da lista, libera a memória alocada */
ListaEncadeada<T>::~ListaEncadeada(){
    Celula<T>* atual;
    Celula<T>* proximo;

    // Liberar a célula-cabeça
    atual = this->primeiro;
    proximo = this->primeiro->prox;
    delete[] atual; 

    // Liberar as células seguintes
    while (proximo != nullptr){
        atual = proximo;
        proximo = atual->prox;
        delete[] atual;
    }
    this->primeiro = nullptr;
    this->ultimo = nullptr;
}


template<class T>
/* Adiciona o objeto no início da lista */
void ListaEncadeada<T>::AdicionaInicio(T& novo){
    // Cria a nova célula
    Celula<T>* nova_celula = new Celula<T>(novo);

    // Coloca ela no lugar da primeira célula (depois da cabeça, obviamente)
    nova_celula->prox = primeiro->prox;
    primeiro->prox = nova_celula;
    nova_celula->ant = primeiro;

    // Define o ponteiro 'anterior' da célula seguinte
    if (n_elementos != 0){
        // Nova célula não é a última, logo existe um próximo elemento
        nova_celula->prox->ant = nova_celula;
    }else{
        /* Nova célula é a última, logo não tem-se que arrumar o anterior da 
        célula seguinte à nova, basta arrumar o ponteiro do último */
        ultimo = nova_celula;
    }

    // Adiciona um ao contador de elementos
    n_elementos++;
}

template<class T>
/* Adiciona o objeto no fim da lista */
void ListaEncadeada<T>::AdicionaFim(T& novo){
    // Cria a nova célula
    Celula<T>* nova_celula;
    nova_celula = new Celula<T>(novo);

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
        Celula<T>* nova_celula = new Celula<T>(novo);
        nova_celula->prox = nullptr;
        nova_celula->ant = nullptr;

        Celula<T> cel_i = Pesquisa(i); // Célula na posição i
        nova_celula->prox = &cel_i;
        nova_celula->ant = cel_i.ant;
        nova_celula->ant->prox = nova_celula;
        cel_i.ant = nova_celula;

        // Adiciona um ao contador de elementos
        this->n_elementos++;
    }
}

template<>
void ListaEncadeada<Curso>::AnaliseEmpurrado(Candidato& empurrado,int i_curso_atual){
    int i1_empurrado = empurrado.get_curso_1();
    int i2_empurrado = empurrado.get_curso_2();

    if (i1_empurrado == i_curso_atual){
        /* O 'empurrado' foi colocado na lista de espera de sua primeira opção
        logo deve ser colocado para se classificar na sua segunda opção */
        Celula<Curso> cur2 = this->Pesquisa(i2_empurrado);
        int res2 = cur2.objeto.Adiciona(empurrado,i2_empurrado);
        if (res2 == 1){
            /* Alterou a lista de espera do segundo curso, temos que arrumá-la */
            cur2.objeto.ArrumaEspera(i2_empurrado,res2);
            AnaliseEmpurrado(cur2.objeto.ArrumaEspera(i2_empurrado,res2),i2_empurrado);
        }
    }else{
        /* O 'empurrado' foi colocado na lista de espera de sua segunda opção
        logo apenas temos que arrumar essa lista de espera */
        Celula<Curso> cur2 = this->Pesquisa(i2_empurrado);
        cur2.objeto.ArrumaEspera(i2_empurrado,2);

    }
}

template<>
/* Adiciona um candidato nos cursos desejados, respeitando as regras do SISU */
void ListaEncadeada<Curso>::Adiciona(Candidato& cand){
    Celula<Curso> cur1 = this->Pesquisa(cand.get_curso_1());
    int res = cur1.objeto.Adiciona(cand,cand.get_curso_1());
    std::cout << cand.get_nome() << ": " << cur1.objeto.get_nome() << "(" << cand.get_curso_1() << ")" << " res=" << res << std::endl;

    if (res == 1){
        /* Alterou a lista de espera, tem-se que reorganizar o primeiro lugar
        que foi 'empurrado' para lá e colocar esse no outro curso dele*/
        this->AnaliseEmpurrado(cur1.objeto.ArrumaEspera(cand.get_curso_1(),res),cand.get_curso_1());
        
    }else if (res == 2){
        /* O novo candidato foi para a lista de espera, então devemos colocá-lo
        na sua segunda opção */
        Celula<Curso> cur2 = this->Pesquisa(cand.get_curso_2());
        int res2 = cur2.objeto.Adiciona(cand,cand.get_curso_2());
        if (res2 == 1)
            cur2.objeto.ArrumaEspera(cand.get_curso_2(),res);
    }
    /* Se o res == 0 ele foi classificado direto, não precisamos colocar ninguém 
    em outro curso */
}

template<>
/* Procura um Candidato com nota menor ou igual à do Candidato pedido;
retorna o primeiro candidato com nota menor ou igual
retorna nullptr se o candidato pedido for o menor */
Celula<Candidato>& ListaEncadeada<Candidato>::Pesquisa(Candidato& cand){
    Celula<Candidato> *vazia = new Celula<Candidato>();
    if (this->Vazia() == true)
        return *vazia;

    Celula<Candidato>* atual = this->primeiro->prox; // j = 0 (posição 0)
    for (int j = 1; atual->objeto.get_nota() > cand.get_nota(); j++){    
        if (j == this->n_elementos){
            // Chegou no último e a nota ainda é maior, retorna nullptr
            return *vazia;
        }
        atual = atual->prox;
    } // Encontrar um com a nota igual ou menor
    return *atual;
}

template<class T>
/* Acessa a célula na posição de índice i */
Celula<T>& ListaEncadeada<T>::Pesquisa(int i){
    if (Vazia() == true)
        throw std::invalid_argument("Lista Vazia");
    if (i < 0 || i >= n_elementos)
        throw std::out_of_range("Indice invalido");
    
    if (i == 0){
        // Primeiro elemento
        return *(primeiro->prox);
    }else if (i == n_elementos-1){
        // Último elemento
        return *ultimo;
    }else if (i < this->n_elementos/2){
        // Até a metade, procure a partir do início
        Celula<T>* atual = primeiro->prox; // j = 0 (posição 0)
        for (int j = 1; j != i ; j++){
            atual = atual->prox;
        } // Encontrar o anterior à posição de interesse
        return *(atual->prox);
    }else{
        // Após a metade, procure voltando do fim
        Celula<T>* atual = ultimo; // j = n-1 (posição n-1)
        for (int j = n_elementos-1; j != i; j--){
            atual = atual->ant;
        } // Encontrar o elemento na posição de interesse
        return *atual;
    }
}

template<class T>
/* Acessa o objeto na posição de índice i */
T& ListaEncadeada<T>::operator[](int index){
    return Pesquisa(index).objeto;
}

template<>
/* Retira o primeiro elemento e retorna um ponteiro para o retirado */
Candidato& ListaEncadeada<Candidato>::RetiraPrimeiro(){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista vazia");
    
    // Basta rearranjar os ponteiros da célula-cabeça
    Celula<Candidato>* cabeca = this->primeiro;
    Celula<Candidato>* eliminar = this->primeiro->prox;
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

    Candidato *c = new Candidato(eliminar->objeto);
    eliminar->objeto = Candidato();
    delete eliminar;
    return (*c);
}

template<>
/* Retira o último e retorna o ponteiro do retirado */
Candidato& ListaEncadeada<Candidato>::RetiraUltimo(){
    if (this->Vazia() == true)
        throw std::invalid_argument("Lista vazia");
    if (this->n_elementos == 1)
        return this->RetiraPrimeiro();
    
    // Encontra o antes do último e o último
    Celula<Candidato>* ant_fim = this->ultimo->ant; /*<-- Custo constante (Lista Duplamente Encadeada)*/
    Celula<Candidato>* fim = this->ultimo;

    // Rearranja os ponteiros
    ant_fim->prox = nullptr;
    this->ultimo = ant_fim;
    
    // Decrementa o contador
    this->n_elementos--;

    Candidato *c = new Candidato(fim->objeto);
    fim->objeto = Candidato();
    delete fim;
    return (*c);
}

template<>
/* Retira um elemento da i-ésima posição e retorna um ponteiro para ele */
Candidato& ListaEncadeada<Candidato>::Retira(int i){
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
        Celula<Candidato>* eliminar = &this->Pesquisa(i);

        // Rearrumar os ponteiros
        eliminar->ant->prox = eliminar->prox;
        eliminar->prox->ant = eliminar->ant;

        // Decrementa o contador
        this->n_elementos--;

        Candidato *c = new Candidato(eliminar->objeto);
        eliminar->objeto = Candidato();
        delete eliminar;
        return (*c);
    }
}

template<class T>
/* Retorna true se a lista está vazia, false do contrário */
bool ListaEncadeada<T>::Vazia(){
    return (this->n_elementos == 0 && this->primeiro == this->ultimo);
}

template<class T>
/* Retorna o número de elementos da lista */
int ListaEncadeada<T>::get_n_elementos(){
    return this->n_elementos;
}

template<>
/* Retorna o índice do candidato na lista */
int ListaEncadeada<Candidato>::get_indice(Candidato& cand){
    Celula<Candidato>* atual = this->primeiro->prox; // j = 0 (posição 0)
    int j;
    for (j = 1; atual->objeto.get_nome() != cand.get_nome() ; j++){
        atual = atual->prox;
    } // Encontrar o anterior à posição de interesse
    return j-1;
}

template<>
void ListaEncadeada<Curso>::imprime(){
    for (int i = 0; i < this->get_n_elementos(); i++){
        (*this)[i].print_curso();
        std::cout << std::endl;
    }
}


