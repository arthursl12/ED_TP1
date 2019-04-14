#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "candidato.h"
#include <stdexcept>

TEST_CASE("Candidato: construtor"){
    CHECK_NOTHROW(Candidato("Joao da Silva", 765.87,1,23));
}

TEST_CASE("Candidato: construtor com entradas invalidas"){
    SUBCASE("Nota"){
        CHECK_THROWS_AS(Candidato("Joao da Silva", -2.9,1,23),std::invalid_argument);
        CHECK_THROWS_AS(Candidato("Joao da Silva", 1002.2,1,23), std::invalid_argument);
        CHECK_NOTHROW(Candidato("Joao da Silva", 0,1,23));
        CHECK_NOTHROW(Candidato("Joao da Silva", 1000,1,23));
    }
    SUBCASE("Índices dos cursos"){
        CHECK_THROWS_AS(Candidato("Joao da Silva", 765.87,-1,23), std::invalid_argument);
        CHECK_THROWS_AS(Candidato("Joao da Silva", 765.87,-1,-23), std::invalid_argument);
        CHECK_THROWS_AS(Candidato("Joao da Silva", 765.87,1,-23), std::invalid_argument);
        CHECK_NOTHROW(Candidato("Joao da Silva", 765.87,0,23));
        CHECK_THROWS_AS(Candidato("Joao da Silva", 765.87,1,1), std::invalid_argument);
    }
}

TEST_CASE("Candidato: Getters"){
    Candidato C("Joao da Silva", 765.87,1,23);
    CHECK(C.get_nome() == "Joao da Silva");
    CHECK(C.get_nota() == 765.87);
    CHECK(C.get_curso_1() == 1);
    CHECK(C.get_curso_2() == 23);
}