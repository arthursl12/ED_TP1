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
    ListaEncadeada<Candidato> L_alunos;
    Candidato c1("Joao da Silva", 765.87,0,1);
    Candidato c2("Manuel da Silva", 722.87,0,2);
    Candidato c3("Maria da Silva", 622.87,2,0);
    Candidato c4("Joana da Silva", 622.87,0,1);
    Candidato c5("Mario da Silva", 657.93,0,2);
    Candidato c6("Sergio Osvaldo Felipe",871,0,2);
    Candidato c7("Lucia Esther Araujo",616.67,0,1);
    Candidato c8("Roberto da Silva",622.87,0,1);

    Curso cur1("Curso1",4);

    // Critério: nota
    cur1.Adiciona(c1,0);

    // Critério: nota
    cur1.Adiciona(c2,0);

    // Critério: nota
    cur1.Adiciona(c3,0);
    
    // Desempate: prioridade de quem escolheu como primeira opção
    cur1.Adiciona(c4,0);
    print_lista(cur1)

    // Critério: nota
    cur1.Adiciona(c5,0);

    // Critério: nota
    cur1.Adiciona(c6,0);

    // Desempate: ordem de chegada
    cur1.Adiciona(c8,0);

    return 0;
}


