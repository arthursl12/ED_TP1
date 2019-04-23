#include "curso.h"
#include <stdexcept>
#include <iostream>

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
    return this->classificados[i];
}

/* Retorna uma cópia do objeto Candidato na 
posição de índice i da lista de Espera */
Candidato Curso::EsperaConsulta(int i){
    return this->espera;
}

/* Executa um desempate entre os candidatos 'cand' e 'atual', sendo que 'atual'
já está na lista e 'cand' será colocado nela; Retorna 0 se o candidato 'atual' 
tem prioridade; Retorna 1 se o candidato 'cand' tem prioridade */
int desempatador(Candidato &cand, Candidato &atual, int i_curso){
    int i1_cand = cand.get_curso_1();
    int i1_atual = atual.get_curso_1();
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


/* Adiciona um candidato ao referido Curso, pela ordem de nota;
Retorna 0 se foi Classificado e não alterou a lista de espera;
Retorna 1 se foi Classificado e "empurrou" alguém para primeiro na lista de espera;
Retorna 2 se foi para lista de espera;
*/
int Curso::Adiciona(Candidato& cand, int i_curso){
    /* Supõe que o índice do curso está certo */
    if (this->classificados.Vazia() == true){
        // Não há classificados ainda
        this->classificados.AdicionaInicio(cand);
        return 0;
    }else{
        Celula<Candidato> ptr = this->classificados.Pesquisa(cand);
        if (ptr.objeto.get_nome() == ""){
            /* Candidato tem nota menor que todos os Classificados */
            if (this->classificados.get_n_elementos() == this->vagas){
                /* Classificados está cheio e o novo candidato tem nota menor:
                vai para a lista de espera */
                ptr = this->espera.Pesquisa(cand);

                if (ptr == nullptr){
                    /* Candidato tem a menor nota da Espera */
                    this->espera.AdicionaFim(cand);
                    return 2;
                }else{
                    if (ptr->objeto.get_nota() == cand.get_nota()){
                        /* Há um empate de notas dentro de Espera */
                        while (ptr->objeto.get_nota() == cand.get_nota()){
                            /* Loop: caso haja mais de um candidato empatado */
                            int res = desempatador(cand,ptr->objeto,i_curso);
                            
                            if (res == 1){
                                /* Preferência do novo */
                                /* Coloca o novo na posição do atual  */
                                int pos = this->espera.get_indice(ptr->objeto);
                                this->espera.Adiciona(cand,pos);
                                return 2;   
                            }
                            if (ptr->prox == nullptr)
                                break;
                            ptr = ptr->prox;
                        }

                        /* Mesmo após todas as iterações, a preferência é de quem já está na
                        lista, logo o novo vai para depois de todos aqueles com a mesma nota 
                        dele */
                        int pos = this->espera.get_indice(ptr.objeto);
                        this->espera.Adiciona(cand,pos+1);
                        return 2;
                    }else{
                        /* Adiciona o novo candidato à frente do candidato com
                        a nota menor */
                        this->espera.Adiciona(cand,this->espera.get_indice(ptr.objeto));
                        return 2;
                    }
                }
            }else{
                /* Classificados não está cheio e o novo candidato tem nota menor:
                vai para o fim de Classificados */
                this->classificados.AdicionaFim(cand);
                if (this->classificados.get_n_elementos() == this->vagas)
                    this->nota_de_corte = cand.get_nota();
                return 0;
            }
        }else{
            if (ptr->objeto.get_nota() == cand.get_nota()){
                /* Há um empate de notas dentro dos Classificados */
                std::cout << "OBJ : " << ptr->objeto.get_nota() << " :: Cand: " << cand.get_nota() << std::endl;
                while (ptr->objeto.get_nota() == cand.get_nota()){
                    /* Loop: caso haja mais de um candidato empatado */
                    std::cout << "OBJ : " << ptr->objeto.get_nota() << " :: Cand: " << cand.get_nota() << std::endl;
                    int res = desempatador(cand,ptr->objeto,i_curso);
                    
                    if (res == 1){
                        /* Preferência do novo */
                        if (this->classificados.get_n_elementos() == this->vagas){
                            /* Coloca o novo na posição do atual  */
                            int pos = this->classificados.get_indice(ptr->objeto);
                            this->classificados.Adiciona(cand,pos);

                            /* O último dos Classificados irá para a espera */
                            Candidato *c = this->classificados.RetiraUltimo();
                            this->espera.AdicionaInicio(*c);

                            this->nota_de_corte = this->ClassificadosConsulta(this->vagas-1).get_nota();
                            return 1;
                        }else{
                            /* Novo ocupa lugar do atual */
                            int pos = this->classificados.get_indice(ptr->objeto);
                            this->classificados.Adiciona(cand,pos);
                            if (this->classificados.get_n_elementos() == this->vagas)
                                this->nota_de_corte = cand.get_nota();
                            return 0;
                        }
                    }
                    if (ptr.prox == nullptr)
                        break;
                    ptr = ptr.prox;
                }

                /* Mesmo após todas as iterações, a preferência é de quem já está na
                lista, logo o novo vai para depois de todos aqueles com a mesma nota 
                dele */
                if (this->classificados.get_n_elementos() == this->vagas){
                    this->espera.AdicionaInicio(cand);
                    return 1;
                }else{
                    int pos = this->classificados.get_indice(ptr->objeto);
                    this->classificados.Adiciona(cand,pos+1);
                    if (this->classificados.get_n_elementos() == this->vagas)
                        this->nota_de_corte = cand.get_nota();
                    return 0;
                }
            }else{
                /* Coloca o novo na posição do atual  */
                int pos = this->classificados.get_indice(ptr->objeto);
                this->classificados.Adiciona(cand,pos);

                if (this->classificados.get_n_elementos() > this->vagas){
                    /* Se a lista de classificados estiver cheia, temos que 
                    retirar o último, que terá que ir para a lista de espera;
                    A condição é 'maior que' pois já adicionamos o novo dentre os
                    classificados  */

                    /* O último dos Classificados irá para a espera */
                    Candidato *c = this->classificados.RetiraUltimo();
                    this->espera.AdicionaInicio(*c);

                    this->nota_de_corte = this->ClassificadosConsulta(this->vagas-1).get_nota();
                    return 1;
                }else{
                    /* A lista de classificados ainda não está completa, logo o
                    último não terá que ir para a lista de espera. Basta checar
                    se for o caso de alterar a nota de corte (se for igual)*/
                    if (this->classificados.get_n_elementos() == this->vagas){
                        this->nota_de_corte = this->ClassificadosConsulta(this->vagas-1).get_nota();
                    }
                    return 0;
                }
            }
        }        
    }
}

/* Reorganiza a lista de Espera caso alguém dos classificados tenha sido 'empurrado'
para lá */
Candidato& Curso::ArrumaEspera(int i_curso, int situacao){
    Celula<Candidato> novo = this->espera.Pesquisa(0);
    Celula<Candidato> primeiro = this->espera.Pesquisa(1);
    Candidato retorno = novo.objeto;
    if (novo.objeto.get_nota() == primeiro.objeto.get_nota()){
        /* Há um empate de notas dentro de Espera */
        int res = 0;
        while (primeiro->objeto.get_nota() == novo->objeto.get_nota()){
            /* Loop: caso haja mais de um candidato empatado */
            res = desempatador(novo->objeto,primeiro->objeto,i_curso);
            
            if (res == 1){
                /* Preferência do novo */
                /* Coloca o novo na posição do atual  */
                int pos = this->espera.get_indice(primeiro->objeto);
                this->espera.Adiciona(novo->objeto,pos);
                break; 
            }
            if (primeiro->prox == nullptr)
                break;
            primeiro = primeiro->prox;
        }

        if (res == 0){
            /* Mesmo após todas as iterações, a preferência é de quem já está na
            lista, logo o novo vai para depois de todos aqueles com a mesma nota 
            dele */
            int pos = this->espera.get_indice(primeiro->objeto);
            this->espera.Adiciona(novo->objeto,pos+1);
        }
        
    }else if (novo.objeto.get_nota() < primeiro.objeto.get_nota()){
        /* A nota do 'empurrado' é menor, tem-se que iterar pela espera até 
        encontrar alguém que tenha nota menor que a dele */
        Celula<Candidato> *c = this->espera.Pesquisa(novo->objeto);
        if (c == nullptr){
            /* O 'empurrado' tem a menor nota da espera */
            this->espera.AdicionaFim(novo->objeto);
        }else{
            if (novo->objeto.get_nota() == primeiro->objeto.get_nota()){
                /* Há um empate de notas dentro de Espera */
                int res = 0;
                while (primeiro->objeto.get_nota() == novo->objeto.get_nota()){
                    /* Loop: caso haja mais de um candidato empatado */
                    res = desempatador(novo->objeto,primeiro->objeto,i_curso);
                    
                    if (res == 1){
                        /* Preferência do novo */
                        /* Coloca o novo na posição do atual  */
                        int pos = this->espera.get_indice(primeiro->objeto);
                        this->espera.Adiciona(novo->objeto,pos);
                        break; 
                    }
                    if (primeiro->prox == nullptr)
                        break;
                    primeiro = primeiro->prox;
                }

                if (res == 0){
                    /* Mesmo após todas as iterações, a preferência é de quem já está na
                    lista, logo o novo vai para depois de todos aqueles com a mesma nota 
                    dele */
                    int pos = this->espera.get_indice(primeiro->objeto);
                    this->espera.Adiciona(novo->objeto,pos+1);
                }
            }else{
                /* Adiciona o novo candidato à frente do candidato com
                a nota menor */
                this->espera.Adiciona(novo->objeto,this->espera.get_indice(primeiro->objeto));
            }
        }
    }
    /* Caso contrário, o que foi 'empurrado' para fora dos classificados tinha 
    nota maior que o primeiro da lista de espera, e então o 'empurrado' fica em
    primeiro da lista de espera */
    if (situacao == 1){
        return retorno;
    }else{
        return nullptr;
    }
}

void print_lista(ListaEncadeada<Candidato>& L_aluno){
    if (L_aluno.Vazia() == false){
        for (int i = 0; i < L_aluno.get_n_elementos(); i++){
            std::cout << i+1 << " - " << L_aluno[i].get_nome() << std::endl;
        }
    }
}


void Curso::print_curso(){
    std::cout << "Curso: ";
    std::cout << this->get_nome() << std::endl;
    std::cout << "\tVagas: " << this->get_vagas() << std::endl;
    std::cout << "Classificados: " << std::endl;
    print_lista(this->classificados);
    std::cout << "Espera: " << std::endl;
    print_lista(this->espera);
}
