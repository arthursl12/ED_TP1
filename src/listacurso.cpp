#include "listacurso.h"
#include <iostream>
#include <string>

/* Construtor da classe ListaSequencial */
ListaSequencialCurso::ListaSequencialCurso(int n){
    if (n <= 0){
        throw std::invalid_argument("Lista com 0 ou menos elementos");
    }
    this->Primeiro = 0;
    this->Ultimo = 0;
    this->Item = new Curso[n];
    this->TAM = n;
}

/* Destrutor da classe ListaSequencial */
ListaSequencialCurso::~ListaSequencialCurso(){
    delete[] this->Item;
}

/* Retorna um bool se a lista está vazia */
bool ListaSequencialCurso::Vazia(){
    return (this->Ultimo == 0);
}

/*  Adiciona um elemento ao fim da lista;
    Lista cheia levanta uma exceção */
void ListaSequencialCurso::Adiciona(Curso& elemento){
    if (this->Ultimo == this->TAM){
        throw std::invalid_argument("Lista Cheia");
    }
    this->Item[Ultimo] = elemento;
    this->Ultimo++;
}

/* Imprime a lista toda */
void ListaSequencialCurso::Imprime(){
    if (this->Vazia() == true){
        return;
    }else{
        for(int i = 0; i < this->Ultimo; i++){
            std::cout << this->Item[i].get_nome() << std::endl;
        }
    }
}

/* Overload do operador[], apenas para consulta */
Curso ListaSequencialCurso::operator[] (int indice) const{
    if (indice >= this->TAM){
        throw std::out_of_range("Índice inválido");
    }
    return this->Item[indice];
}

