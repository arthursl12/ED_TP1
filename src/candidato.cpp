#include "candidato.h"
#include <stdexcept>

/* Construtor da classe Candidato */
Candidato::Candidato(std::string _nome, double _nota, int _i_curso1, int _i_curso2)
:nome(_nome){
    if (_nota < 0 || _nota > 1000)
        throw std::invalid_argument("Nota invalida");
    else if (_i_curso1 < 0 || _i_curso2 < 0)
        throw std::invalid_argument("Indice de curso invalido");
    else if (_i_curso1 == _i_curso2)
        throw std::invalid_argument("Indices de curso iguais");
    else{
        this->nota = _nota;
        this->i_curso1 = _i_curso1;
        this->i_curso2 = _i_curso2;
    }
}

/* GETTERS */
/* Retorna o nome do candidato */
std::string Candidato::get_nome(){
    return this->nome;
}

/* Retorna a nota do candidato */
double Candidato::get_nota(){
    return this->nota;
}

/* Retorna o índice do primeiro curso do candidato */
int Candidato::get_curso_1(){
    return this->i_curso1;
}

/* Retorna o índice do segundo curso do candidato */
int Candidato::get_curso_2(){
    return this->i_curso2;
}
