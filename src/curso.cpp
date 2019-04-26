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
int desempatador(Candidato &cand, Candidato* atual, int i_curso){
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

/* Adiciona um candidato ao referido Curso, pela ordem de nota;
Retorna 0 se foi Classificado e não alterou a lista de Espera;
Retorna 1 se foi Classificado e "empurrou" alguém para primeiro na lista de Espera;
Retorna 2 se foi para lista de Espera;
*/
int Curso::Adiciona(Candidato& cand, int i_curso){
    if (this->Classificados.Vazia() == true){
        this->Classificados.AdicionaInicio(cand);
        return 0;
    }

    Candidato* ptr = this->Classificados.Pesquisa(cand);
    if (ptr == nullptr){
        /* Candidato tem nota menor que todos os Classificados */
        if (this->Classificados.get_n_elementos() == this->vagas){
            return adicionaEspera(cand, i_curso);
        }else{
            /* Classificados não está cheio e o novo candidato tem nota menor:
            vai para o fim de Classificados */
            this->Classificados.AdicionaFim(cand);
            if (this->Classificados.get_n_elementos() == this->vagas)
                this->nota_de_corte = cand.get_nota();
            return 0;
        }
    }else{
        if (ptr->get_nota() == cand.get_nota()){
            /* Há um empate de notas dentro dos Classificados */
            // Encontrar o iterador para o candidato de ptr
            Candidato *it = this->Classificados._primeiro();
            while (it->get_nome() != ptr->get_nome()){
                it = this->Classificados.proximo();
            }
            while (ptr->get_nota() == cand.get_nota()){
                /* Loop: caso haja mais de um candidato empatado */
                int res = desempatador(cand,ptr,i_curso);
                
                if (res == 1){
                    /* Preferência do novo */
                    if (this->Classificados.get_n_elementos() == this->vagas){
                        /* Coloca o novo na posição do atual  */
                        int pos = this->Classificados.get_indice(ptr);
                        this->Classificados.Adiciona(cand,pos);

                        /* O último dos Classificados irá para a Espera */
                        Candidato *c = this->Classificados.RetiraUltimo();
                        this->Espera.AdicionaInicio(*c);

                        this->nota_de_corte = this->ClassificadosConsulta(this->vagas-1).get_nota();
                        return 1;
                    }else{
                        /* Novo ocupa lugar do atual */
                        int pos = this->Classificados.get_indice(ptr);
                        this->Classificados.Adiciona(cand,pos);
                        if (this->Classificados.get_n_elementos() == this->vagas)
                            this->nota_de_corte = cand.get_nota();
                        return 0;
                    }
                }
                it = this->Classificados.proximo();
                if (it == nullptr)
                    break;
            }

            /* Mesmo após todas as iterações, a preferência é de quem já está na
            lista, logo o novo vai para depois de todos aqueles com a mesma nota 
            dele */
            if (this->Classificados.get_n_elementos() == this->vagas){
                this->Espera.AdicionaInicio(cand);
                return 1;
            }else{
                int pos = this->Classificados.get_indice(ptr);
                this->Classificados.Adiciona(cand,pos+1);
                if (this->Classificados.get_n_elementos() == this->vagas)
                    this->nota_de_corte = cand.get_nota();
                return 0;
            }
        }else{
            /* Coloca o novo na posição do atual  */
            int pos = this->Classificados.get_indice(ptr);
            this->Classificados.Adiciona(cand,pos);
            if (Classificados.get_n_elementos() >= get_vagas()){
                if (Classificados.get_n_elementos() > get_vagas()){
                    /* O último dos Classificados irá para a Espera */
                    Candidato *c = this->Classificados.RetiraUltimo();
                    this->Espera.AdicionaInicio(*c);
                    this->nota_de_corte = this->ClassificadosConsulta(this->vagas-1).get_nota();
                    return 1;
                }
                return 0;
            }
            return 0;
        }
    }        
    
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
    Candidato* novo = Espera.RetiraPrimeiro();

    if (Espera.get_n_elementos() > 0){
        Candidato* primeiro = Espera._primeiro();
        Candidato *retorno = novo;
        if (novo->get_nota() == primeiro->get_nota()){
            int res = desempataEspera(*novo, i_curso, primeiro);
        }else if (novo->get_nota() < primeiro->get_nota()){
            /* A nota do 'empurrado' é menor, tem-se que iterar pela Espera até 
            encontrar alguém que tenha nota menor que a dele */
            Candidato *c = this->Espera.Pesquisa(*novo);
            if (c == nullptr){
                /* O 'empurrado' tem a menor nota da Espera */
                this->Espera.AdicionaFim(*novo);
            }else{
                if (novo->get_nota() == primeiro->get_nota()){
                    /* Há um empate de notas dentro de Espera */
                    int res = desempataEspera(*novo, i_curso, primeiro);
                }else{
                    /* Adiciona o novo candidato à frente do candidato com
                    a nota menor */
                    this->Espera.Adiciona(*novo,this->Espera.get_indice(primeiro));
                }
            }
        }
        /* Caso contrário, o que foi 'empurrado' para fora dos Classificados tinha 
        nota maior que o primeiro da lista de Espera, e então o 'empurrado' fica em
        primeiro da lista de Espera */
    }

    Espera.AdicionaInicio(*novo);
    if (situacao == 1){
        return novo;
    }else{
        return nullptr;
    }
    

    
}
