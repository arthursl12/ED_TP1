#include <cstdio>
#include <string>
#include <iostream>
#include <iomanip>

#include "lista.h"
#include "curso.h"

void print_curso(ListaEncadeada<Curso>& L_curso){
    Curso *it = L_curso._primeiro();
    while (it != nullptr) {
        printf("%s %.2f\n",it->get_nome(),it->get_nota_de_corte());
        printf("Classificados\n");
        Candidato *it_cand = it->Classif_primeiro();
        while (it_cand != nullptr) {
            printf("%s %.2f\n",it_cand->get_nome(),it_cand->get_nota());
            it_cand = it->Classifproximo();
        }
        std::cout << "Lista de espera\n";
        it_cand = it->Espera_primeiro();
        while (it_cand != nullptr) {
            printf("%s %.2f\n",it_cand->get_nome(),it_cand->get_nota());
            it_cand = it->Esperaproximo();
        }
        printf("\n");
        it = L_curso.proximo();
    }
}

int main(int argc, char* argv[]){
    ListaEncadeada<Curso> L_curso;

    int n_cursos, n_alunos;
    scanf("%i %i\n",&n_cursos, &n_alunos);

    // Lê os cursos
    for (int i = 0; i < n_cursos; i++){
        char* _nome = (char*) malloc(100*sizeof(char));
        int _vagas;

        scanf("%[^\n]s",_nome);
        scanf("%i\n",&_vagas);

        Curso *c = new Curso(_nome,_vagas);
        L_curso.AdicionaFim(*c);
    }

    // Lê os alunos
    for (int i = 0; i < n_alunos; i++){
        char* _nome = (char*) malloc(100*sizeof(char));
        int _i_1;
        int _i_2;
        float _nota;

        scanf("%[^\n]s",_nome);
        scanf("%f %i %i\n", &_nota, &_i_1, &_i_2);

        Candidato *c = new Candidato(_nome, _nota, _i_1, _i_2);
        L_curso.Adiciona(*c);
    }

    // Imprime
    print_curso(L_curso);

    // Finaliza:
    while (L_curso.Vazia() == false){
        L_curso.RetiraUltimo();
    }

    return 0;
}


