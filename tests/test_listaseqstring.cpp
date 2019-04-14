#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "listaseqstring.h"

TEST_CASE("ListaSequencialString: construtor"){
    CHECK_NOTHROW(ListaSequencialString(2));
}

TEST_CASE("ListaSequencialString: construtor com entrada invalida"){
    CHECK_THROWS_AS(ListaSequencialString(0), std::invalid_argument);
    CHECK_THROWS_AS(ListaSequencialString(-3), std::invalid_argument);
}

TEST_CASE("ListaSequencialString: Adiciona"){
    ListaSequencialString L(3);
    ItemString str1("um"), str2("dois"), str3("tres"), str4("quatro");
    CHECK_NOTHROW(L.Adiciona(str1));
    CHECK_NOTHROW(L.Adiciona(str2));
    CHECK_NOTHROW(L.Adiciona(str3));
    CHECK_THROWS_AS(L.Adiciona(str4), std::invalid_argument);

    CHECK(L[0].get_dado() == str1.get_dado());
    CHECK(L[1].get_dado() == str2.get_dado());
    CHECK(L[2].get_dado() == str3.get_dado());
    CHECK_THROWS_AS(L[4], std::out_of_range);
}

TEST_CASE("ListaSequencialString: Vazia"){
    ListaSequencialString L(3);
    ItemString str1("um"), str2("dois"), str3("tres"), str4("quatro");
    CHECK(L.Vazia() == true);
    L.Adiciona(str1);
    CHECK(L.Vazia() == false);
    L.Adiciona(str2);
    CHECK(L.Vazia() == false);
    L.Adiciona(str3);
    CHECK(L.Vazia() == false);
}

TEST_CASE("ListsaSequencialString: Imprime"){
    ListaSequencialString L(2);
    ItemString str1("um"), str2("dois");
    L.Adiciona(str1);
    L.Adiciona(str2);

    std::stringstream ss;
    //change the underlying buffer and save the old buffer
    auto old_buf = std::cout.rdbuf(ss.rdbuf()); 
    L.Imprime();
    std::cout.rdbuf(old_buf); //reset
    CHECK(ss.str() == "um\ndois\n");
}