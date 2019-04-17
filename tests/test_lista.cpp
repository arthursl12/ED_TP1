#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lista.h"

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
        CHECK_THROWS_AS(L.Consulta(0), std::invalid_argument);
        CHECK_THROWS_AS(L.Consulta(-1), std::invalid_argument);
        CHECK_THROWS_AS(L.Consulta(10), std::invalid_argument);
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
        CHECK(L.Consulta(4).get_nome() == c5.get_nome());
        CHECK(L.Consulta(3).get_nome() == c4.get_nome());
        CHECK(L.Consulta(2).get_nome() == c3.get_nome());
        CHECK(L.Consulta(1).get_nome() == c2.get_nome());
        CHECK(L.Consulta(0).get_nome() == c1.get_nome());
        CHECK_THROWS_AS(L.Consulta(-1), std::out_of_range);
        CHECK_THROWS_AS(L.Consulta(5), std::out_of_range);
        CHECK_THROWS_AS(L.Consulta(7), std::out_of_range);
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
        CHECK(L.Consulta(5).get_nome() == c6.get_nome());
        CHECK(L.Consulta(4).get_nome() == c5.get_nome());
        CHECK(L.Consulta(3).get_nome() == c4.get_nome());
        CHECK(L.Consulta(2).get_nome() == c3.get_nome());
        CHECK(L.Consulta(1).get_nome() == c2.get_nome());
        CHECK(L.Consulta(0).get_nome() == c1.get_nome());
        CHECK_THROWS_AS(L.Consulta(-1), std::out_of_range);
        CHECK_THROWS_AS(L.Consulta(6), std::out_of_range);
        CHECK_THROWS_AS(L.Consulta(10), std::out_of_range);
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
        CHECK(L.Consulta(0).get_nome() == c1.get_nome());

        L.AdicionaInicio(c2);
        L.AdicionaInicio(c3);
        L.AdicionaInicio(c4);
        L.AdicionaInicio(c5);
        CHECK(L.Consulta(0).get_nome() == c5.get_nome());
        CHECK(L.Consulta(1).get_nome() == c4.get_nome());
        CHECK(L.Consulta(2).get_nome() == c3.get_nome());
        CHECK(L.Consulta(3).get_nome() == c2.get_nome());
        CHECK(L.Consulta(4).get_nome() == c1.get_nome());
    }
    SUBCASE("Adiciona ao último"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        ListaEncadeada<Candidato> L;

        L.AdicionaFim(c4);
        CHECK(L.Consulta(0).get_nome() == c4.get_nome());

        L.AdicionaInicio(c1);
        L.AdicionaInicio(c2);
        L.AdicionaFim(c3);
        CHECK(L.Consulta(3).get_nome() == c3.get_nome());
    }
    SUBCASE("Adiciona no índice i"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);
        ListaEncadeada<Candidato> L;

        L.Adiciona(c1,0);
        CHECK(L.Consulta(0).get_nome() == c1.get_nome());

        L.Adiciona(c2,0);
        CHECK(L.Consulta(0).get_nome() == c2.get_nome());
        CHECK(L.Consulta(1).get_nome() == c1.get_nome());

        L.Adiciona(c3,1);
        CHECK(L.Consulta(0).get_nome() == c2.get_nome());
        CHECK(L.Consulta(1).get_nome() == c3.get_nome());
        CHECK(L.Consulta(2).get_nome() == c1.get_nome());

        L.Adiciona(c4,3);
        CHECK(L.Consulta(0).get_nome() == c2.get_nome());
        CHECK(L.Consulta(1).get_nome() == c3.get_nome());
        CHECK(L.Consulta(2).get_nome() == c1.get_nome());
        CHECK(L.Consulta(3).get_nome() == c4.get_nome());

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

        CHECK(L.Consulta(2).get_nome() == c3.get_nome());
        CHECK(L.Consulta(1).get_nome() == c2.get_nome());
        CHECK(L.Consulta(0).get_nome() == c1.get_nome());
        Candidato *c = L.RetiraUltimo();
        CHECK(c->get_nome() == c3.get_nome());
        delete(c);

        CHECK(L.Consulta(1).get_nome() == c2.get_nome());
        CHECK(L.Consulta(0).get_nome() == c1.get_nome());
        c = L.RetiraUltimo();
        CHECK(c->get_nome() == c2.get_nome());
        delete(c);

        CHECK(L.Consulta(0).get_nome() == c1.get_nome());
        c = L.RetiraUltimo();
        CHECK(c->get_nome() == c1.get_nome());
        delete(c);

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

        CHECK(L.Consulta(2).get_nome() == c3.get_nome());
        CHECK(L.Consulta(1).get_nome() == c2.get_nome());
        CHECK(L.Consulta(0).get_nome() == c1.get_nome());
        Candidato *c = L.RetiraPrimeiro();
        CHECK(c->get_nome() == c1.get_nome());

        CHECK(L.Consulta(1).get_nome() == c3.get_nome());
        CHECK(L.Consulta(0).get_nome() == c2.get_nome());
        c = L.RetiraPrimeiro();
        CHECK(c->get_nome() == c2.get_nome());
        delete(c);

        CHECK(L.Consulta(0).get_nome() == c3.get_nome());
        c = L.RetiraPrimeiro();
        CHECK(c->get_nome() == c3.get_nome());
        delete(c);

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

        CHECK(L.Consulta(0).get_nome() == c2.get_nome());
        CHECK(L.Consulta(1).get_nome() == c3.get_nome());
        CHECK(L.Consulta(2).get_nome() == c1.get_nome());
        CHECK(L.Consulta(3).get_nome() == c4.get_nome());
        Candidato *c = L.Retira(2);
        CHECK(c->get_nome() == c1.get_nome());
        delete(c);

        CHECK(L.Consulta(0).get_nome() == c2.get_nome());
        CHECK(L.Consulta(1).get_nome() == c3.get_nome());
        CHECK(L.Consulta(2).get_nome() == c4.get_nome());
        c = L.Retira(0);
        CHECK(c->get_nome() == c2.get_nome());
        delete(c);

        CHECK(L.Consulta(0).get_nome() == c3.get_nome());
        CHECK(L.Consulta(1).get_nome() == c4.get_nome());
        c = L.Retira(1);
        CHECK(c->get_nome() == c4.get_nome());
        delete(c);

        CHECK(L.Consulta(0).get_nome() == c3.get_nome());
        CHECK_THROWS_AS(L.Retira(2), std::out_of_range);
        c = L.Retira(0);
        CHECK(c->get_nome() == c3.get_nome());
        delete(c);
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

