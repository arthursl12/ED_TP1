#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lista.h"

TEST_CASE("ListaEncadeadaCandidato: construtor"){
    CHECK_NOTHROW(ListaEncadeadaCandidato());
}

TEST_CASE("ListaEncadeadaCandidato: Vazia"){
    ListaEncadeadaCandidato L;
    CHECK(L.Vazia() == true);

    Candidato c1("Joao da Silva", 765.87,1,23);
    L.AdicionaInicio(c1);
    CHECK(L.Vazia() == false);
}

TEST_CASE("ListaEncadeadaCandidato: Consulta"){
    Candidato c1("Joao da Silva", 765.87,1,23);
    Candidato c2("Manuel da Silva", 722.87,2,3);
    Candidato c3("Maria da Silva", 622.87,0,2);
    ListaEncadeadaCandidato L;

    CHECK(L.Vazia() == true);
    CHECK_THROWS_AS(L.Consulta(0), std::invalid_argument);
    CHECK_THROWS_AS(L.Consulta(-1), std::invalid_argument);
    CHECK_THROWS_AS(L.Consulta(10), std::invalid_argument);

    L.AdicionaFim(c1);
    L.AdicionaFim(c2);
    L.AdicionaFim(c3);
    CHECK(L.Vazia() == false);

    CHECK(L.Consulta(2)->get_nome() == c3.get_nome());
    CHECK(L.Consulta(1)->get_nome() == c2.get_nome());
    CHECK(L.Consulta(0)->get_nome() == c1.get_nome());
    CHECK_THROWS_AS(L.Consulta(-1), std::out_of_range);
    CHECK_THROWS_AS(L.Consulta(3), std::out_of_range);
    CHECK_THROWS_AS(L.Consulta(4), std::out_of_range);
}

TEST_CASE("ListaEncadeadaCandidato: Adiciona"){
    SUBCASE("Adiciona no início"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        ListaEncadeadaCandidato L;
        L.AdicionaInicio(c1);
        L.AdicionaInicio(c2);
        CHECK(L.Consulta(0)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c1.get_nome());
    }
    SUBCASE("Adiciona no índice i"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);
        ListaEncadeadaCandidato L;

        L.Adiciona(c1,0);
        CHECK(L.Consulta(0)->get_nome() == c1.get_nome());

        L.Adiciona(c2,0);
        CHECK(L.Consulta(0)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c1.get_nome());

        L.Adiciona(c3,1);
        CHECK(L.Consulta(0)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(2)->get_nome() == c1.get_nome());

        L.Adiciona(c4,3);
        CHECK(L.Consulta(0)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(2)->get_nome() == c1.get_nome());
        CHECK(L.Consulta(3)->get_nome() == c4.get_nome());

        CHECK_THROWS_AS(L.Adiciona(c5,10),std::out_of_range);
    }
    SUBCASE("Adiciona ao último"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        ListaEncadeadaCandidato L;

        L.AdicionaFim(c4);
        CHECK(L.Consulta(0)->get_nome() == c4.get_nome());

        L.AdicionaInicio(c1);
        L.AdicionaInicio(c2);
        L.AdicionaFim(c3);
        CHECK(L.Consulta(3)->get_nome() == c3.get_nome());
    }
}

TEST_CASE("ListaEncadeadaCandidato: Retira"){
    SUBCASE("Retira o último"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        ListaEncadeadaCandidato L;
        L.AdicionaFim(c1);
        L.AdicionaFim(c2);
        L.AdicionaFim(c3);

        CHECK(L.Consulta(2)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(0)->get_nome() == c1.get_nome());
        CHECK(L.RetiraUltimo()->get_nome() == c3.get_nome());

        CHECK(L.Consulta(1)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(0)->get_nome() == c1.get_nome());
        CHECK(L.RetiraUltimo()->get_nome() == c2.get_nome());

        CHECK(L.Consulta(0)->get_nome() == c1.get_nome());
        CHECK(L.RetiraUltimo()->get_nome() == c1.get_nome());

        CHECK(L.Vazia() == true);
        CHECK_THROWS_AS(L.RetiraUltimo(),std::invalid_argument);
    }
    SUBCASE("Retira o primeiro"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        ListaEncadeadaCandidato L;
        L.AdicionaFim(c1);
        L.AdicionaFim(c2);
        L.AdicionaFim(c3);

        CHECK(L.Consulta(2)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(0)->get_nome() == c1.get_nome());
        CHECK(L.RetiraPrimeiro()->get_nome() == c1.get_nome());

        CHECK(L.Consulta(1)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(0)->get_nome() == c2.get_nome());
        CHECK(L.RetiraPrimeiro()->get_nome() == c2.get_nome());

        CHECK(L.Consulta(0)->get_nome() == c3.get_nome());
        CHECK(L.RetiraPrimeiro()->get_nome() == c3.get_nome());

        CHECK(L.Vazia() == true);
        CHECK_THROWS_AS(L.RetiraUltimo(),std::invalid_argument);
    }
    SUBCASE("Retira i-ésimo"){
        Candidato c1("Joao da Silva", 765.87,1,23);
        Candidato c2("Manuel da Silva", 722.87,2,3);
        Candidato c3("Maria da Silva", 622.87,0,2);
        Candidato c4("Joana da Silva", 627.83,1,2);
        Candidato c5("Mario da Silva", 657.93,5,1);
        ListaEncadeadaCandidato L;

        L.Adiciona(c1,0);
        L.Adiciona(c2,0);
        L.Adiciona(c3,1);
        L.Adiciona(c4,3);

        CHECK(L.Consulta(0)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(2)->get_nome() == c1.get_nome());
        CHECK(L.Consulta(3)->get_nome() == c4.get_nome());
        CHECK(L.Retira(2)->get_nome() == c1.get_nome());

        CHECK(L.Consulta(0)->get_nome() == c2.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(2)->get_nome() == c4.get_nome());
        CHECK(L.Retira(0)->get_nome() == c2.get_nome());

        CHECK(L.Consulta(0)->get_nome() == c3.get_nome());
        CHECK(L.Consulta(1)->get_nome() == c4.get_nome());
        CHECK(L.Retira(1)->get_nome() == c4.get_nome());

        CHECK(L.Consulta(0)->get_nome() == c3.get_nome());
        CHECK_THROWS_AS(L.Retira(2), std::invalid_argument);
        CHECK(L.Retira(0)->get_nome() == c3.get_nome());
        CHECK(L.Vazia() == true);
        CHECK_THROWS_AS(L.Retira(0), std::invalid_argument);

    }
}

