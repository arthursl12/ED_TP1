#include "curso.h"
#include <stdexcept>
#include <iostream>

Curso::Curso(const char* _nome, int _vagas)
:nome(_nome){
    if (_vagas < 0)
        throw std::invalid_argument("# vagas invalido");
    this->nota_de_corte = 0;
    this->vagas = _vagas;
}

Curso::~Curso(){
}

const char* Curso::get_nome(){
    return this->nome;
}
double Curso::get_nota_de_corte(){
    return this->nota_de_corte;
}
int Curso::get_vagas(){
    return this->vagas;
}

/* Retorna uma cópia do objeto Candidato na 
posição de índice i da lista de Classificados */
Candidato Curso::ClassificadosConsulta(int i){
    return this->Classificados.Consulta(i);
}

/* Retorna uma cópia do objeto Candidato na 
posição de índice i da lista de Espera */
Candidato Curso::EsperaConsulta(int i){
    return this->Espera.Consulta(i);
}

/* Executa um desempate entre os candidatos 'cand' e 'atual', sendo que 'atual'
já está na lista e 'cand' será colocado nela; Retorna 0 se o candidato 'atual' 
tem prioridade; Retorna 1 se o candidato 'cand' tem prioridade */
int Curso::desempatador(Candidato &cand, Candidato* atual, int i_curso){
    int i1_cand = cand.get_curso_1();
    int i1_atual = atual->get_curso_1();
    if (i1_cand == i_curso && i1_atual != i_curso){
        /* Candidato novo tem prioridade (primeira opção de curso) */
        return 1;
    }else if (i1_cand != i_curso && i1_atual == i_curso){
        /* Candidato da posição tem prioridade (primeira opção de curso) */
        return 0;  
    }else{
        /* Nenhum tem prioridade, usa-se a ordem de chegada.
        Como o candidato da posição já está na lista, ele chegou primeiro, logo
        tem a prioridade, neste caso */
        return 0;
    }
}

/* Executa o desempate entre 'cand' (que está sendo adicionado) e 'empate' (que
já está na lista de Espera), adicionando 'cand' na posição apropriada */
int Curso::desempataEspera(Candidato &cand, int i_curso, Candidato* empate){
    Candidato* it = empate;

    while (it->get_nota() == cand.get_nota()){
        /* Loop: caso haja mais de um candidato empatado */
        int res = desempatador(cand,it,i_curso);
        
        if (res == 1){
            /* Preferência do novo */
            /* Coloca o novo na posição do atual  */
            int pos = Espera.get_indice(it);
            Espera.Adiciona(cand,pos);
            return 2;   
        }
        it = Espera.proximo();
        if (it == nullptr)
            break;
    }

    /* Mesmo após todas as iterações, a preferência é de quem já está na
    lista, logo o novo vai para depois de todos aqueles com a mesma nota 
    dele */
    int pos = Espera.get_indice(it);
    Espera.Adiciona(cand,pos+1);
    return 2;
}

int Curso::adicionaEspera(Candidato& cand, int i_curso){
    Candidato *ptr = Espera.Pesquisa(cand);

    if (ptr == nullptr){
        /* Candidato tem a menor nota da Espera */
        Espera.AdicionaFim(cand);
        return 2;
    }else{
        if (ptr->get_nota() == cand.get_nota()){
            return desempataEspera(cand,i_curso,ptr);
        }else{
            /* Adiciona o novo candidato à frente do candidato com
            a nota menor */
            Espera.Adiciona(cand,Espera.get_indice(ptr));
            return 2;
        }
    }
}

void Curso::set_nota_corte(){
    int qtd_classif = Classificados.get_n_elementos();
    if (qtd_classif == vagas)
        this->nota_de_corte = ClassificadosConsulta(qtd_classif-1).get_nota();
}

int Curso::desempataClassificados(Candidato& cand, int i_curso, Candidato* empate){
    Candidato* ptr = empate;

    while (ptr->get_nota() == cand.get_nota()){
        /* Loop: caso haja mais de um candidato empatado */
        int res = desempatador(cand,ptr,i_curso);
        
        if (res == 1){
            /* Preferência do novo */
            int pos = Classificados.get_indice(ptr);
            Classificados.Adiciona(cand,pos);

            if (Classificados.get_n_elementos() > vagas){
                Candidato *c = Classificados.RetiraUltimo();
                Espera.AdicionaInicio(*c);
                set_nota_corte();
                return 1;
            }
            set_nota_corte();
            return 0;
        }

        ptr = Classificados.proximo();
        if (ptr == nullptr)
            break;
    }

    /* Mesmo após todas as iterações, a preferência é de quem já está na
    lista, logo o novo vai para depois de todos aqueles com a mesma nota 
    dele */
    if (Classificados.get_n_elementos() == vagas){
        Espera.AdicionaInicio(cand);
        return 1;
    }
    
    int pos = Classificados.get_indice(ptr);
    Classificados.Adiciona(cand,pos+1);
    set_nota_corte();
    return 0;
}

/* Adiciona um candidato ao referido Curso, pela ordem de nota;
Retorna 0 se foi Classificado e não alterou a lista de Espera;
Retorna 1 se foi Classificado e "empurrou" alguém para a lista de Espera;
Retorna 2 se foi para lista de Espera;
*/
int Curso::Adiciona(Candidato& cand, int i_curso){
    if (Classificados.Vazia() == true){
        Classificados.AdicionaInicio(cand);
        return 0;
    }

    Candidato* ptr = Classificados.Pesquisa(cand);
    if (ptr == nullptr){
        /* Candidato tem nota menor que todos os Classificados */
        if (Classificados.get_n_elementos() == vagas)
            return adicionaEspera(cand, i_curso);
        Classificados.AdicionaFim(cand);
        set_nota_corte();
        return 0;
        
    }  
    if (ptr->get_nota() == cand.get_nota())
        return desempataClassificados(cand,i_curso,ptr);
    
    /* Coloca o novo na posição do atual  */
    int pos = Classificados.get_indice(ptr);
    Classificados.Adiciona(cand,pos);

    if (Classificados.get_n_elementos() > vagas){
        Candidato *c = Classificados.RetiraUltimo();
        Espera.AdicionaInicio(*c);
        set_nota_corte();
        return 1;
    }
    set_nota_corte();
    return 0;     
}

void Curso::AdicionaFim(Candidato& cand){
    this->Classificados.AdicionaFim(cand);
}

Candidato* Curso::Classif_primeiro(){
    return Classificados._primeiro();
}
Candidato* Curso::Classifproximo(){
    return Classificados.proximo();
}
Candidato* Curso::Espera_primeiro(){
    return Espera._primeiro();
}
Candidato* Curso::Esperaproximo(){
    return Espera.proximo();
}

/* Reorganiza a lista de Espera caso alguém dos Classificados tenha sido 'empurrado'
para lá */
Candidato* Curso::ArrumaEspera(int i_curso, int situacao){
    Candidato* empurrado = Espera.RetiraPrimeiro();

    if (Espera.get_n_elementos() > 0)
        adicionaEspera(*empurrado,i_curso);
    else
        Espera.AdicionaInicio(*empurrado);

    
    if (situacao == 1)
        return empurrado;
    else
        return nullptr;
}
