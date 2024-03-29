#ifndef CURSO_H
#define CURSO_H

#include "lista.h"
#include "candidato.h"

class Curso{
private:
    const char* nome;
    double nota_de_corte;
    int vagas;
    ListaEncadeada<Candidato> Classificados;
    ListaEncadeada<Candidato> Espera;

public:
    Curso(const char* _nome, int _vagas);
    ~Curso();

    const char* get_nome();
    double get_nota_de_corte();
    int get_vagas();
    void set_nota_corte();

    Candidato* Classif_primeiro();
    Candidato* Classifproximo();
    Candidato* Espera_primeiro();
    Candidato* Esperaproximo();

    int Adiciona(Candidato& cand, int i_curso);
    void AdicionaFim(Candidato& cand);

    Candidato ClassificadosConsulta(int i);
    Candidato EsperaConsulta(int i);

    Candidato* ArrumaEspera(int i_curso, int situacao);
    int desempataEspera(Candidato& cand, int i_curso, Candidato* empate);
    int adicionaEspera(Candidato& cand, int i_curso);
    int desempatador(Candidato &cand, Candidato* atual, int i_curso);
    int desempataClassificados(Candidato& cand, int i_curso, Candidato* empate);
};



#endif /* CURSO_H */