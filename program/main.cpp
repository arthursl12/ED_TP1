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
}

void print_lista(ListaEncadeada<Candidato>& L_aluno){
    for (int i = 0; i < L_aluno.get_n_elementos(); i++){
        std::cout << i+1 << " - " << L_aluno.Consulta(i).get_nome() << std::endl;
    }
}


int main(int argc, char* argv[]){
    Curso cur1("Curso1",4);
    Curso cur2("Curso2",2);
    Curso cur3("Curso3",4);
    ListaEncadeada<Curso> L_cursos;
    L_cursos.AdicionaFim(cur1);
    L_cursos.AdicionaFim(cur2);
    L_cursos.AdicionaFim(cur3);

    L_cursos[2].get_nome() == cur3.get_nome();
    L_cursos[1].get_nome() == cur2.get_nome();
    L_cursos[0].get_nome() == cur1.get_nome();

    Candidato c1("Joao da Silva", 765.87,1,23);
    Candidato c2("Manuel da Silva", 722.87,2,3);
    Candidato c3("Maria da Silva", 622.87,0,2);
    L_cursos.Pesquisa(0)->objeto->AdicionaFim(c1);
    L_cursos.Pesquisa(1)->objeto->AdicionaFim(c2);

    L_cursos[0].ClassificadosConsulta(0).get_nome() == c1.get_nome();
    L_cursos[1].ClassificadosConsulta(0).get_nome() == c2.get_nome();

    L_cursos[1].AdicionaFim(c3);
    L_cursos[1].ClassificadosConsulta(0).get_nome() == c2.get_nome();
    L_cursos[1].ClassificadosConsulta(1).get_nome() == c3.get_nome();

    return 0;
}


