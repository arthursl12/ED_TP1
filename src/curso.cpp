#include "curso.h"
#include <stdexcept>

/* Construtor do Curso */
Curso::Curso(std::string _nome, int _vagas)
:nome(_nome){
    if (_vagas < 0)
        throw std::invalid_argument("# vagas invalido");
    this->nota_de_corte = 0;
    this->vagas = _vagas;
}

/* Construtor Vazio */
Curso::Curso(){
    this->nome = "";
    this->vagas = -1;
    this->nota_de_corte = -1;
}

/* Getters */
/* Retorna a string com o nome do curso */
std::string Curso::get_nome(){
    return this->nome;
}

/* Retorna a nota de corte do curso */
double Curso::get_nota_de_corte(){
    return this->nota_de_corte;
}

/* Retorna o numero de vagas do curso */
int Curso::get_vagas(){
    return this->vagas;
}

/* Retorna uma cópia do objeto Candidato na 
posição de índice i da lista de Classificados */
Candidato Curso::ClassificadosConsulta(int i){
    return this->classificados.Consulta(i);
}

/* Retorna uma cópia do objeto Candidato na 
posição de índice i da lista de Espera */
Candidato Curso::EsperaConsulta(int i){
    return this->espera.Consulta(i);
}

void Curso::Adiciona(Candidato& cand, ListaEncadeada<Curso> l_curso){
    
}