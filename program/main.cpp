#include <cstdio>
#include <string>
#include <iostream>

#include "lista.h"
#include "curso.h"

int main(int argc, char* argv[]){
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

    

    return 0;
}


