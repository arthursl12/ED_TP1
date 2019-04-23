#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lista.h"
#include "curso.h"

TEST_CASE("ListaEncadeada: construtor"){
    CHECK_NOTHROW(ListaEncadeada<Candidato>());
}

TEST_CASE("ListaEncadeada: Vazia"){
    ListaEncadeada<Candidato> L;
    CHECK(L.Vazia() == true);

    Candidato c1("Joao da Silva", 765.87,1,23);
    L.AdicionaInicio(c1);
    CHECK(L.Vazia() == false);
}

TEST_CASE("ListaEncadeada: Consulta"){
    SUBCASE("Lista Vazia"){
        ListaEncadeada<Candidato> L;

        CHECK(L.Vazia() == true);
        CHECK_THROWS_AS(L[0], std::invalid_argument);
        CHECK_THROWS_AS(L[-1], std::invalid_argument);
        CHECK_THROWS_AS(L[10], std::invalid_argument);
    }
    SUBCASE("Lista Preenchida - Impar"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);
        ListaEncadeada<Candidato> L;

        L.AdicionaFim(c1);
        L.AdicionaFim(c2);
        L.AdicionaFim(c3);
        L.AdicionaFim(c4);
        L.AdicionaFim(c5);

        CHECK(L.Vazia() == false);
        CHECK(L[4].get_nome() == c5.get_nome());
        CHECK(L[3].get_nome() == c4.get_nome());
        CHECK(L[2].get_nome() == c3.get_nome());
        CHECK(L[1].get_nome() == c2.get_nome());
        CHECK(L[0].get_nome() == c1.get_nome());
        CHECK_THROWS_AS(L[-1], std::out_of_range);
        CHECK_THROWS_AS(L[5], std::out_of_range);
        CHECK_THROWS_AS(L[7], std::out_of_range);
    }
    SUBCASE("Lista Preenchida - Par"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);
        Candidato c6("Gilberto da Silva", 697.93,0,1);
        ListaEncadeada<Candidato> L;

        L.AdicionaFim(c1);
        L.AdicionaFim(c2);
        L.AdicionaFim(c3);
        L.AdicionaFim(c4);
        L.AdicionaFim(c5);
        L.AdicionaFim(c6);

        CHECK(L.Vazia() == false);
        CHECK(L[5].get_nome() == c6.get_nome());
        CHECK(L[4].get_nome() == c5.get_nome());
        CHECK(L[3].get_nome() == c4.get_nome());
        CHECK(L[2].get_nome() == c3.get_nome());
        CHECK(L[1].get_nome() == c2.get_nome());
        CHECK(L[0].get_nome() == c1.get_nome());
        CHECK_THROWS_AS(L[-1], std::out_of_range);
        CHECK_THROWS_AS(L[6], std::out_of_range);
        CHECK_THROWS_AS(L[10], std::out_of_range);
    }
}

TEST_CASE("ListaEncadeada: Adiciona"){
    SUBCASE("Adiciona no início"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);

        ListaEncadeada<Candidato> L;
        L.AdicionaInicio(c1);
        CHECK(L.Vazia() == false);
        CHECK(L[0].get_nome() == c1.get_nome());

        L.AdicionaInicio(c2);
        L.AdicionaInicio(c3);
        L.AdicionaInicio(c4);
        L.AdicionaInicio(c5);
        CHECK(L[0].get_nome() == c5.get_nome());
        CHECK(L[1].get_nome() == c4.get_nome());
        CHECK(L[2].get_nome() == c3.get_nome());
        CHECK(L[3].get_nome() == c2.get_nome());
        CHECK(L[4].get_nome() == c1.get_nome());
    }
    SUBCASE("Adiciona ao último"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        ListaEncadeada<Candidato> L;

        L.AdicionaFim(c4);
        CHECK(L[0].get_nome() == c4.get_nome());

        L.AdicionaInicio(c1);
        L.AdicionaInicio(c2);
        L.AdicionaFim(c3);
        CHECK(L[3].get_nome() == c3.get_nome());
    }
    SUBCASE("Adiciona no índice i"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);
        ListaEncadeada<Candidato> L;

        L.Adiciona(c1,0);
        CHECK(L[0].get_nome() == c1.get_nome());

        L.Adiciona(c2,0);
        CHECK(L[0].get_nome() == c2.get_nome());
        CHECK(L[1].get_nome() == c1.get_nome());

        L.Adiciona(c3,1);
        CHECK(L[0].get_nome() == c2.get_nome());
        CHECK(L[1].get_nome() == c3.get_nome());
        CHECK(L[2].get_nome() == c1.get_nome());

        L.Adiciona(c4,3);
        CHECK(L[0].get_nome() == c2.get_nome());
        CHECK(L[1].get_nome() == c3.get_nome());
        CHECK(L[2].get_nome() == c1.get_nome());
        CHECK(L[3].get_nome() == c4.get_nome());

        CHECK_THROWS_AS(L.Adiciona(c5,10),std::out_of_range);
    }
}

TEST_CASE("ListaEncadeada: Retira"){
    SUBCASE("Retira o último"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        ListaEncadeada<Candidato> L;
        L.AdicionaFim(c1);
        L.AdicionaFim(c2);
        L.AdicionaFim(c3);

        CHECK(L[2].get_nome() == c3.get_nome());
        CHECK(L[1].get_nome() == c2.get_nome());
        CHECK(L[0].get_nome() == c1.get_nome());
        Candidato c = L.RetiraUltimo();
        CHECK(c.get_nome() == c3.get_nome());

        CHECK(L[1].get_nome() == c2.get_nome());
        CHECK(L[0].get_nome() == c1.get_nome());
        c = L.RetiraUltimo();
        CHECK(c.get_nome() == c2.get_nome());

        CHECK(L[0].get_nome() == c1.get_nome());
        c = L.RetiraUltimo();
        CHECK(c.get_nome() == c1.get_nome());

        CHECK(L.Vazia() == true);
        CHECK_THROWS_AS(L.RetiraUltimo(),std::invalid_argument);
    }
    SUBCASE("Retira o primeiro"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        ListaEncadeada<Candidato> L;
        L.AdicionaFim(c1);
        L.AdicionaFim(c2);
        L.AdicionaFim(c3);

        CHECK(L[2].get_nome() == c3.get_nome());
        CHECK(L[1].get_nome() == c2.get_nome());
        CHECK(L[0].get_nome() == c1.get_nome());
        Candidato c = L.RetiraPrimeiro();
        CHECK(c.get_nome() == c1.get_nome());

        CHECK(L[1].get_nome() == c3.get_nome());
        CHECK(L[0].get_nome() == c2.get_nome());
        c = L.RetiraPrimeiro();
        CHECK(c.get_nome() == c2.get_nome());

        CHECK(L[0].get_nome() == c3.get_nome());
        c = L.RetiraPrimeiro();
        CHECK(c.get_nome() == c3.get_nome());

        CHECK(L.Vazia() == true);
        CHECK_THROWS_AS(L.RetiraPrimeiro(),std::invalid_argument);
    }
    SUBCASE("Retira i-ésimo"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);
        ListaEncadeada<Candidato> L;

        L.Adiciona(c1,0);
        L.Adiciona(c2,0);
        L.Adiciona(c3,1);
        L.Adiciona(c4,3);

        CHECK(L[0].get_nome() == c2.get_nome());
        CHECK(L[1].get_nome() == c3.get_nome());
        CHECK(L[2].get_nome() == c1.get_nome());
        CHECK(L[3].get_nome() == c4.get_nome());
        Candidato c = L.Retira(2);
        CHECK(c.get_nome() == c1.get_nome());

        CHECK(L[0].get_nome() == c2.get_nome());
        CHECK(L[1].get_nome() == c3.get_nome());
        CHECK(L[2].get_nome() == c4.get_nome());
        c = L.Retira(0);
        CHECK(c.get_nome() == c2.get_nome());

        CHECK(L[0].get_nome() == c3.get_nome());
        CHECK(L[1].get_nome() == c4.get_nome());
        c = L.Retira(1);
        CHECK(c.get_nome() == c4.get_nome());

        CHECK(L[0].get_nome() == c3.get_nome());
        CHECK_THROWS_AS(L.Retira(2), std::out_of_range);
        c = L.Retira(0);
        CHECK(c.get_nome() == c3.get_nome());
        CHECK(L.Vazia() == true);
        CHECK_THROWS_AS(L.Retira(0), std::invalid_argument);
    }
}

TEST_CASE("ListaEncadeada: get_n_elementos"){
    ListaEncadeada<Candidato> L;

    CHECK(L.Vazia() == true);
    CHECK(L.get_n_elementos() == 0);

    Candidato c1("Joao da Silva", 765.87,1,23);
    Candidato c2("Manuel da Silva", 722.87,2,3);
    Candidato c3("Maria da Silva", 622.87,0,2);
    Candidato c4("Joana da Silva", 627.83,1,2);
    Candidato c5("Mario da Silva", 657.93,5,1);

    L.Adiciona(c1,0);
    CHECK(L.get_n_elementos() == 1);
    L.Adiciona(c2,0);
    CHECK(L.get_n_elementos() == 2);
    L.Adiciona(c3,1);
    CHECK(L.get_n_elementos() == 3);
    L.Adiciona(c4,3);
    CHECK(L.get_n_elementos() == 4);
}

TEST_CASE("ListaEncadeada<Candidato>: pesquisa"){
    Candidato c1("Joao da Silva", 765.87,0,1);
    Candidato c3("Mario da Silva", 657.93,0,2);
    Candidato c2("Maria da Silva", 622.87,2,0);
    Candidato C1("Joana da Silva", 622.87,0,1);
    Candidato C2("Manuel da Silva", 722.87,0,2);
    Candidato C3("Jobson da Silva", 522.87,0,2);
    ListaEncadeada<Candidato> L_cand;

    // Checagens rápidas
    CHECK(L_cand.Vazia() == true);
    CHECK(L_cand.Pesquisa(c1) == nullptr);

    // Cria a lista em ordem
    L_cand.AdicionaFim(c1);
    L_cand.AdicionaFim(c3);
    L_cand.AdicionaFim(c2);

    CHECK(L_cand.Pesquisa(C1).objeto.get_nome() == c2.get_nome());
    CHECK(L_cand.Pesquisa(C2).objeto.get_nome() == c3.get_nome());
    CHECK(L_cand.Pesquisa(C3) == nullptr);
}

TEST_CASE("ListaEncadeada<Candidato>: get_indice"){
    ListaEncadeada<Candidato> L;

    Candidato c1("Joao da Silva", 765.87,1,23);
    Candidato c2("Manuel da Silva", 722.87,2,3);
    Candidato c3("Maria da Silva", 622.87,0,2);
    Candidato c4("Joana da Silva", 627.83,1,2);
    Candidato c5("Mario da Silva", 657.93,5,1);

    L.Adiciona(c1,0);
    CHECK(L.get_indice(c1) == 0);
    L.Adiciona(c2,0);
    CHECK(L.get_indice(c2) == 0);
    L.Adiciona(c3,1);
    CHECK(L.get_indice(c3) == 1);
    L.Adiciona(c4,3);
    CHECK(L.get_indice(c4) == 3);
}

/*
TEST_CASE("ListaEncadeada<Curso>: adiciona"){
    // "Carrega os candidatos"
    ListaEncadeada<Candidato> L_cand;
    Candidato c1("Joao da Silva", 765.87,1,0);
    Candidato c2("Manuel da Silva", 722.87,2,0);
    Candidato c3("Maria da Silva", 622.87,0,2);
    Candidato c4("Joana da Silva", 627.83,1,2);
    Candidato c5("Mario da Silva", 657.93,1,2);
    Candidato c6("Sergio Osvaldo Felipe",871,1,0);
    Candidato c7("Lucia Esther Araujo",656.67,0,1);
    std::cout << "OK1" << std::endl;

    // Carrega os cursos
    Curso cur1("Curso1",4);
    Curso cur2("Curso2",2);
    Curso cur3("Curso3",4);
    ListaEncadeada<Curso> L_cursos;
    L_cursos.AdicionaFim(cur1);
    L_cursos.AdicionaFim(cur2);
    L_cursos.AdicionaFim(cur3);
    std::cout << "OK2" << std::endl;

    

    /* Estágios:
    C1:__,__,__,__/__
    C2:__,__/__
    C3:__,__,__,__/__
    *

    /* Teste Adição c1:
    C1:__,__,__,__/__
    C2:c1,__/__
    C3:__,__,__,__/__
    *
    L_cursos.Adiciona(c1);
    L_cursos.imprime();
    CHECK(L_cursos[0].get_nota_de_corte() == 0);
    CHECK(L_cursos[1].ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(L_cursos[1].get_nota_de_corte() == 0);
    CHECK(L_cursos[2].get_nota_de_corte() == 0);

    /* Teste Adição c2:
    C1:__,__,__,__/__
    C2:c1,__/__
    C3:c2,__,__,__/__
    *
    L_cursos.Adiciona(c2);
    L_cursos.imprime();
    CHECK(L_cursos[0].get_nota_de_corte() == 0);
    CHECK(L_cursos[1].ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(L_cursos[1].get_nota_de_corte() == 0);
    CHECK(L_cursos[2].ClassificadosConsulta(0).get_nome() == c2.get_nome());
    CHECK(L_cursos[2].get_nota_de_corte() == 0);

    /* Teste Adição c3:
    C1:c3,__,__,__/__
    C2:c1,__/__
    C3:c2,__,__,__/__
    *
    L_cursos.Adiciona(c3);
    L_cursos.imprime();
    CHECK(L_cursos[0].ClassificadosConsulta(0).get_nome() == c3.get_nome());
    CHECK(L_cursos[0].get_nota_de_corte() == 0);
    CHECK(L_cursos[1].ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(L_cursos[1].get_nota_de_corte() == 0);
    CHECK(L_cursos[2].ClassificadosConsulta(0).get_nome() == c2.get_nome());
    CHECK(L_cursos[2].get_nota_de_corte() == 0);

    /* Teste Adição c4:
    C1:c3,__,__,__/__
    C2:c1,c4/__
    C3:c2,__,__,__/__
    *
    L_cursos.Adiciona(c4);
    CHECK(L_cursos[0].ClassificadosConsulta(0).get_nome() == c3.get_nome());
    CHECK(L_cursos[0].get_nota_de_corte() == 0);
    CHECK(L_cursos[1].ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(L_cursos[1].ClassificadosConsulta(1).get_nome() == c4.get_nome());
    CHECK(L_cursos[1].get_nota_de_corte() == c4.get_nota());
    CHECK(L_cursos[2].ClassificadosConsulta(0).get_nome() == c2.get_nome());
    CHECK(L_cursos[2].get_nota_de_corte() == 0);

    /* Teste Adição c5:
    C1:c3,__,__,__/__
    C2:c1,c5/c4,__
    C3:c2,c4,__,__/__
    *
    L_cursos.Adiciona(c5);
    CHECK(L_cursos[0].ClassificadosConsulta(0).get_nome() == c3.get_nome());
    CHECK(L_cursos[0].get_nota_de_corte() == 0);
    CHECK(L_cursos[1].ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(L_cursos[1].ClassificadosConsulta(1).get_nome() == c5.get_nome());
    CHECK(L_cursos[1].EsperaConsulta(0).get_nome() == c4.get_nome());
    CHECK(L_cursos[1].get_nota_de_corte() == c5.get_nota());
    CHECK(L_cursos[2].ClassificadosConsulta(0).get_nome() == c2.get_nome());
    CHECK(L_cursos[2].ClassificadosConsulta(1).get_nome() == c4.get_nome());
    CHECK(L_cursos[2].get_nota_de_corte() == 0);

    /* Teste Adição c6:
    C1:c3,__,__,__/__
    C2:c6,c1/c5,c4,__
    C3:c2,c5,c4,__/__
    *
    L_cursos.Adiciona(c6);
    CHECK(L_cursos[0].ClassificadosConsulta(0).get_nome() == c3.get_nome());
    CHECK(L_cursos[0].get_nota_de_corte() == 0);
    CHECK(L_cursos[1].ClassificadosConsulta(0).get_nome() == c6.get_nome());
    CHECK(L_cursos[1].ClassificadosConsulta(1).get_nome() == c1.get_nome());
    CHECK(L_cursos[1].EsperaConsulta(0).get_nome() == c5.get_nome());
    CHECK(L_cursos[1].EsperaConsulta(1).get_nome() == c4.get_nome());
    CHECK(L_cursos[1].get_nota_de_corte() == c1.get_nota());
    CHECK(L_cursos[2].ClassificadosConsulta(0).get_nome() == c2.get_nome());
    CHECK(L_cursos[2].ClassificadosConsulta(1).get_nome() == c5.get_nome());
    CHECK(L_cursos[2].ClassificadosConsulta(2).get_nome() == c4.get_nome());
    CHECK(L_cursos[2].get_nota_de_corte() == 0);

    /*Teste Classificação Final: 
    Cur1(4): c7,c3,__,__/__
    Cur2(2): c6,c1/c5,c4
    Cur3(4): c2,c5,c4,__/__
    *
    L_cursos.Adiciona(c7);
    CHECK(L_cursos[0].ClassificadosConsulta(0).get_nome() == c7.get_nome());
    CHECK(L_cursos[0].ClassificadosConsulta(1).get_nome() == c3.get_nome());
    CHECK(L_cursos[0].get_nota_de_corte() == 0);
    std::cout << "OK4" << std::endl;

    CHECK(L_cursos[1].ClassificadosConsulta(0).get_nome() == c6.get_nome());
    CHECK(L_cursos[1].ClassificadosConsulta(1).get_nome() == c1.get_nome());
    CHECK(L_cursos[1].EsperaConsulta(0).get_nome() == c5.get_nome());
    CHECK(L_cursos[1].EsperaConsulta(1).get_nome() == c4.get_nome());
    CHECK(L_cursos[1].get_nota_de_corte() == c1.get_nota());
    std::cout << "OK5" << std::endl;

    CHECK(L_cursos[2].ClassificadosConsulta(0).get_nome() == c2.get_nome());
    CHECK(L_cursos[2].ClassificadosConsulta(1).get_nome() == c5.get_nome());
    CHECK(L_cursos[2].ClassificadosConsulta(2).get_nome() == c4.get_nome());
    CHECK(L_cursos[2].get_nota_de_corte() == 0);
    std::cout << "OK6" << std::endl;


}*/




