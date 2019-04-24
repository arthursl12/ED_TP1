#include <cstdio>
#include <string>
#include <iostream>
#include <iomanip>

#include "lista.h"
#include "curso.h"

void print_curso(ListaEncadeada<Curso>& L_curso){
    for (int i = 0; i < L_curso.get_n_elementos(); i++){
        Curso c = L_curso.Consulta(i);
        std::cout << "Curso: ";
        std::cout << c.get_nome() << std::endl;
        std::cout << "\tVagas: " << c.get_vagas() << std::endl;
    }
}

void print_cand(ListaEncadeada<Candidato>& L_aluno){
    for (int i = 0; i < L_aluno.get_n_elementos(); i++){
        Candidato c = L_aluno.Consulta(i);
        std::cout << "Al: ";
        std::cout << c.get_nome() << std::endl;
        std::cout << "\t1: " << c.get_curso_1();
        std::cout << "  2: " << c.get_curso_2();
        std::cout << std::setprecision(6) << "\tNota: " << c.get_nota();
        std::cout << std::endl;
    }
}
/*
void modulo_leitura(){
    ListaEncadeada<Candidato> L_alunos;
    ListaEncadeada<Curso> L_curso;

    

    int n_cursos, n_alunos;
    scanf("%i %i\n",&n_cursos, &n_alunos);

    // Lê os cursos
    for (int i = 0; i < n_cursos; i++){
        std::string _nome;
        char _nome_char[100];
        int _vagas;

        scanf("%[^\n]s",_nome_char);
        scanf("%i\n",&_vagas);
        _nome = _nome_char;

        Curso *c = new Curso(_nome,_vagas);
        L_curso.AdicionaFim(*c);
    }
    print_curso(L_curso);

    // Lê os alunos
    for (int i = 0; i < n_alunos; i++){
        std::string _nome;
        char _nome_char[100];
        int _i_1;
        int _i_2;
        float _nota;

        scanf("%[^\n]s",_nome_char);
        scanf("%f %i %i\n", &_nota, &_i_1, &_i_2);
        _nome = _nome_char;

        Candidato *c = new Candidato(_nome, _nota, _i_1, _i_2);
        L_alunos.AdicionaFim(*c);
    }
    print_cand(L_alunos);
}*/

void print_lista(ListaEncadeada<Candidato>& L_aluno){
    for (int i = 0; i < L_aluno.get_n_elementos(); i++){
        std::cout << i+1 << " - " << L_aluno.Consulta(i).get_nome() << std::endl;
    }
}


int main(int argc, char* argv[]){
    // "Carrega os candidatos"
    ListaEncadeada<Candidato> L_cand;
    Candidato *c1 = new Candidato("Joao da Silva", 765.87,1,0);
    Candidato *c2 = new Candidato("Manuel da Silva", 722.87,2,0);
    Candidato *c3 = new Candidato("Maria da Silva", 622.87,0,2);
    Candidato *c4 = new Candidato("Joana da Silva", 627.83,1,2);
    Candidato *c5 = new Candidato("Mario da Silva", 657.93,1,2);
    Candidato *c6 = new Candidato("Sergio Osvaldo Felipe",871,1,0);
    Candidato *c7 = new Candidato("Lucia Esther Araujo",656.67,0,1);
    L_cand.AdicionaFim(*c1);
    L_cand.AdicionaFim(*c2);
    L_cand.AdicionaFim(*c3);
    L_cand.AdicionaFim(*c4);
    L_cand.AdicionaFim(*c5);
    L_cand.AdicionaFim(*c6);
    L_cand.AdicionaFim(*c7);
    Candidato *it_cand = L_cand._primeiro();

    // Carrega os cursos
    Curso* cur1 = new Curso("Curso1",4);
    Curso* cur2 = new Curso("Curso2",2);
    Curso* cur3 = new Curso("Curso3",4);
    ListaEncadeada<Curso>* L_cursos = new ListaEncadeada<Curso>;
    L_cursos->AdicionaFim(*cur1);
    L_cursos->AdicionaFim(*cur2);
    L_cursos->AdicionaFim(*cur3);

    for (int i = 0; i < L_cand.get_n_elementos(); i++){
        L_cursos->Adiciona(*it_cand);
        it_cand = L_cand.proximo();
    }

    std::cout << L_cursos->Consulta(0).ClassificadosConsulta(0).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(0).ClassificadosConsulta(1).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(0).get_nota_de_corte();

    std::cout << L_cursos->Consulta(1).ClassificadosConsulta(0).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(1).ClassificadosConsulta(1).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(1).EsperaConsulta(0).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(1).EsperaConsulta(1).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(1).get_nota_de_corte() << std::endl;

    std::cout << L_cursos->Consulta(2).ClassificadosConsulta(0).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(2).ClassificadosConsulta(1).get_nome() << std::endl;
    std::cout << L_cursos->Consulta(2).ClassificadosConsulta(2).get_nome() << std::endl;

    delete cur1;
    delete cur2;
    delete cur3;
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete c5;
    delete c6;
    delete c7;

    return 0;
}


