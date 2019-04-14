#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "listacurso.h"

TEST_CASE("ListaSequencialCurso: construtor"){
    CHECK_NOTHROW(ListaSequencialCurso(2));
}

TEST_CASE("ListaSequencialCurso: construtor com entrada invalida"){
    CHECK_THROWS_AS(ListaSequencialCurso(0), std::invalid_argument);
    CHECK_THROWS_AS(ListaSequencialCurso(-3), std::invalid_argument);
}

TEST_CASE("ListaSequencialCurso: Adiciona"){
    ListaSequencialCurso L(3);
    Curso c1("um",3), c2("dois",4), c3("tres",0), c4("quatro",5);
    CHECK_NOTHROW(L.Adiciona(c1));
    CHECK_NOTHROW(L.Adiciona(c2));
    CHECK_NOTHROW(L.Adiciona(c3));
    CHECK_THROWS_AS(L.Adiciona(c4), std::invalid_argument);

    CHECK(L[0].get_nome() == c1.get_nome());
    CHECK(L[1].get_nome() == c2.get_nome());
    CHECK(L[2].get_nome() == c3.get_nome());
    CHECK_THROWS_AS(L[4], std::out_of_range);
}

TEST_CASE("ListaSequencialCurso: Vazia"){
    ListaSequencialCurso L(3);
    Curso c1("um",3), c2("dois",4), c3("tres",0), c4("quatro",5);
    CHECK(L.Vazia() == true);
    L.Adiciona(c1);
    CHECK(L.Vazia() == false);
    L.Adiciona(c2);
    CHECK(L.Vazia() == false);
    L.Adiciona(c3);
    CHECK(L.Vazia() == false);
}

TEST_CASE("ListsaSequencialcing: Imprime"){
    ListaSequencialCurso L(2);
    Curso c1("um",3), c2("dois",4);
    L.Adiciona(c1);
    L.Adiciona(c2);

    std::stringstream ss;
    //change the underlying buffer and save the old buffer
    auto old_buf = std::cout.rdbuf(ss.rdbuf()); 
    L.Imprime();
    std::cout.rdbuf(old_buf); //reset
    CHECK(ss.str() == "um\ndois\n");
}