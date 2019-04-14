#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "curso.h"

TEST_CASE("Curso: construtor"){
    CHECK_NOTHROW(Curso("Teste",2));
}

TEST_CASE("Curso: construtor com entradas invalidas"){
    CHECK_NOTHROW(Curso("123",3));
    CHECK_THROWS_AS(Curso("curso", -1), std::invalid_argument);
    CHECK_NOTHROW(Curso("curso", 0));
}

TEST_CASE("Curso: construtor vazio"){
    CHECK_NOTHROW(Curso());
}

TEST_CASE("Curso: getters"){
    Curso C("curso", 32);
    CHECK(C.get_nome() == "curso");
    CHECK(C.get_vagas() == 32);
    CHECK(C.get_nota_de_corte() == 0.0);

    Curso C2;
    CHECK(C2.get_nome() == "");
    CHECK(C2.get_vagas() == -1);
    CHECK(C2.get_nota_de_corte() == -1);
}