#ifndef CURSO_H
#define CURSO_H

#include <string>
#include "lista.h"
#include "candidato.h"

class Curso{
private:
    std::string nome;
    double nota_de_corte;
    int vagas;
    ListaEncadeada<Candidato> classificados;
    ListaEncadeada<Candidato> espera;

public:
    Curso(std::string _nome, int _vagas);

    std::string get_nome();
    double get_nota_de_corte();
    int get_vagas();

    Candidato ClassificadosConsulta(int i);
    Candidato EsperaConsulta(int i);

    int Adiciona(Candidato& cand, int i_curso);
    void AdicionaFim(Candidato& cand);
};



#endif /* CURSO_H */