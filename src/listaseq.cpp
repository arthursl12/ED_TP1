#include "listaseq.h"
#include <iostream>

template<class T>
/* Construtor do item */
TipoItem<T>::TipoItem(T _dado, TipoChave _chave){
    Dado = _dado;
    Chave = _chave;
}


template<class T>
/* Construtor da classe ListaSequencial */
ListaSequencial<T>::ListaSequencial(int n){
    this->Primeiro = 0;
    this->Ultimo = 0;
    this->Item = new T[n];
}

template<class T>
/* Destrutor da classe ListaSequencial */
ListaSequencial<T>::~ListaSequencial(){
    delete(this->Item);
}

template<class T>
/* Retorna um bool se a lista está vazia */
bool ListaSequencial<T>::Vazia(){
    return (this->Ultimo == 0);
}

template<class T>
/*  Adiciona um elemento ao fim da lista;
    Lista cheia levanta uma exceção */
void ListaSequencial<T>::Adiciona(T elemento){
    this->Item[Ultimo] = elemento;
}

template<class T>
/* Imprime a lista toda */
void ListaSequencial<T>::Imprime(){
    if (this->Vazia() == true){
        return;
    }else{
        for(int i = 0; i < this->Ultimo; i++){
            std::cout << this->Item[i] << std::endl;
        }
    }
}

