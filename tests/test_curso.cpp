#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "curso.h"
#include "candidato.h"

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

TEST_CASE("Curso: adiciona"){
    Candidato c1("Joao da Silva", 765.87,0,1);
    Candidato c2("Manuel da Silva", 722.87,0,2);
    Candidato c3("Maria da Silva", 622.87,2,0);
    Candidato c4("Joana da Silva", 622.87,0,1);
    Candidato c5("Mario da Silva", 657.93,0,2);
    Candidato c6("Sergio Osvaldo Felipe",871,0,2);
    Candidato c7("Lucia Esther Araujo",616.67,0,1);
    Candidato c8("Roberto da Silva",622.87,0,1);

    Curso cur1("Curso1",4);

    // Critério: nota
    CHECK(cur1.Adiciona(c1,0) == 0);
    CHECK(cur1.get_nota_de_corte() == 0);
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c1.get_nome());

    // Critério: nota
    CHECK(cur1.Adiciona(c2,0) == 0);
    CHECK(cur1.get_nota_de_corte() == 0);
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(cur1.ClassificadosConsulta(1).get_nome() == c2.get_nome());

    // Critério: nota
    CHECK(cur1.Adiciona(c3,0) == 0);
    CHECK(cur1.get_nota_de_corte() == 0);
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(cur1.ClassificadosConsulta(1).get_nome() == c2.get_nome());
    CHECK(cur1.ClassificadosConsulta(2).get_nome() == c3.get_nome());
    
    // Desempate: prioridade de quem escolheu como primeira opção
    CHECK(cur1.Adiciona(c4,0) == 0);
    CHECK(cur1.get_nota_de_corte() == c3.get_nota());
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(cur1.ClassificadosConsulta(1).get_nome() == c2.get_nome());
    CHECK(cur1.ClassificadosConsulta(2).get_nome() == c4.get_nome());
    CHECK(cur1.ClassificadosConsulta(3).get_nome() == c3.get_nome());

    // Critério: nota
    CHECK(cur1.Adiciona(c5,0) == 1);
    CHECK(cur1.get_nota_de_corte() == c4.get_nota());
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c1.get_nome());
    CHECK(cur1.ClassificadosConsulta(1).get_nome() == c2.get_nome());
    CHECK(cur1.ClassificadosConsulta(2).get_nome() == c5.get_nome());
    CHECK(cur1.ClassificadosConsulta(3).get_nome() == c4.get_nome());
    CHECK(cur1.EsperaConsulta(0).get_nome() == c3.get_nome());

    // Critério: nota
    CHECK(cur1.Adiciona(c6,0) == 1);
    CHECK(cur1.get_nota_de_corte() == c5.get_nota());
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c6.get_nome());
    CHECK(cur1.ClassificadosConsulta(1).get_nome() == c1.get_nome());
    CHECK(cur1.ClassificadosConsulta(2).get_nome() == c2.get_nome());
    CHECK(cur1.ClassificadosConsulta(3).get_nome() == c5.get_nome());
    CHECK(cur1.EsperaConsulta(0).get_nome() == c4.get_nome());
    CHECK(cur1.EsperaConsulta(1).get_nome() == c3.get_nome());

    // Critério: nota
    CHECK(cur1.Adiciona(c7,0) == 2);
    CHECK(cur1.get_nota_de_corte() == c5.get_nota());
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c6.get_nome());
    CHECK(cur1.ClassificadosConsulta(1).get_nome() == c1.get_nome());
    CHECK(cur1.ClassificadosConsulta(2).get_nome() == c2.get_nome());
    CHECK(cur1.ClassificadosConsulta(3).get_nome() == c5.get_nome());
    CHECK(cur1.EsperaConsulta(0).get_nome() == c4.get_nome());
    CHECK(cur1.EsperaConsulta(1).get_nome() == c3.get_nome());
    CHECK(cur1.EsperaConsulta(2).get_nome() == c7.get_nome());


    // Desempate: ordem de chegada
    CHECK(cur1.Adiciona(c8,0) == 2);
    CHECK(cur1.get_nota_de_corte() == c5.get_nota());
    CHECK(cur1.ClassificadosConsulta(0).get_nome() == c6.get_nome());
    CHECK(cur1.ClassificadosConsulta(1).get_nome() == c1.get_nome());
    CHECK(cur1.ClassificadosConsulta(2).get_nome() == c2.get_nome());
    CHECK(cur1.ClassificadosConsulta(3).get_nome() == c5.get_nome());
    CHECK(cur1.EsperaConsulta(0).get_nome() == c4.get_nome());
    CHECK(cur1.EsperaConsulta(1).get_nome() == c8.get_nome());
    CHECK(cur1.EsperaConsulta(2).get_nome() == c3.get_nome());
    CHECK(cur1.EsperaConsulta(3).get_nome() == c7.get_nome());
}