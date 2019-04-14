#include "listaseqstring.h"
#include <iostream>
#include <string>

/* Construtor da classe ListaSequencial */
ListaSequencialString::ListaSequencialString(int n){
    if (n <= 0){
        throw std::invalid_argument("Lista com 0 ou menos elementos");
    }
    this->Primeiro = 0;
    this->Ultimo = 0;
    this->Item = new ItemString[n];
    this->TAM = n;
}

/* Destrutor da classe ListaSequencial */
ListaSequencialString::~ListaSequencialString(){
    delete[] this->Item;
}

/* Retorna um bool se a lista está vazia */
bool ListaSequencialString::Vazia(){
    return (this->Ultimo == 0);
}

/*  Adiciona um elemento ao fim da lista;
    Lista cheia levanta uma exceção */
void ListaSequencialString::Adiciona(ItemString elemento){
    if (this->Ultimo == this->TAM){
        throw std::invalid_argument("Lista Cheia");
    }
    this->Item[Ultimo] = elemento;
    this->Ultimo++;
}

/* Imprime a lista toda */
void ListaSequencialString::Imprime(){
    if (this->Vazia() == true){
        return;
    }else{
        for(int i = 0; i < this->Ultimo; i++){
            std::cout << this->Item[i].get_dado() << std::endl;
        }
    }
}

/* Overload do operador[], apenas para consulta */
ItemString ListaSequencialString::operator[] (int indice) const{
    if (indice >= this->TAM){
        throw std::out_of_range("Índice inválido");
    }
    return this->Item[indice];
}

