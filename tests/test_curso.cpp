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

TEST_CASE("Curso: consulta"){
    SUBCASE("ClassificadosConsulta"){
        
    }
    SUBCASE("EsperaConsulta"){}
}

TEST_CASE("Curso: adiciona"){
    // "Carrega os candidatos"
    ListaEncadeada<Candidato> L_cand;
    Candidato c1("Joao da Silva", 765.87,1,0);
    Candidato c2("Manuel da Silva", 722.87,2,0);
    Candidato c3("Maria da Silva", 622.87,0,2);
    Candidato c4("Joana da Silva", 627.83,1,2);
    Candidato c5("Mario da Silva", 657.93,1,2);
    Candidato c6("Sergio Osvaldo Felipe",871,1,0);
    Candidato c7("Lucia Esther Araujo",656.67,0,1);
    L_cand.AdicionaFim(c1);
    L_cand.AdicionaFim(c2);
    L_cand.AdicionaFim(c3);
    L_cand.AdicionaFim(c4);
    L_cand.AdicionaFim(c5);
    L_cand.AdicionaFim(c6);
    L_cand.AdicionaFim(c7);

    // Carrega os cursos
    Curso cur1("Curso1",4);
    Curso cur2("Curso2",2);
    Curso cur3("Curso3",4);
    ListaEncadeada<Curso> L_cursos;
    L_cursos.AdicionaFim(cur1);
    L_cursos.AdicionaFim(cur2);
    L_cursos.AdicionaFim(cur3);

    for (int i = 0; i < L_cand.get_n_elementos(); i++){
        Candidato* c = &(L_cand.Pesquisa(i)->objeto);
        int i_curso = c->get_curso_1();
        L_cursos.Pesquisa(i_curso)->objeto.Adiciona(*c, L_cursos);
    }

    // Cur1(4): c7,c3,__,__/__
    // Cur2(2): c6,c1/c5,c4
    // Cur3(4): c2,c5,c4

    CHECK(L_cursos.Consulta(0).ClassificadosConsulta(0).get_nome() == c7.get_nome());
    CHECK(L_cursos.Consulta(0).ClassificadosConsulta(1).get_nome() == c3.get_nome());
    CHECK(L_cursos.Consulta(0).get_nota_de_corte() == 0);

    CHECK(L_cursos.Consulta(1).ClassificadosConsulta(0).get_nome() == c6.get_nome());
    CHECK(L_cursos.Consulta(1).ClassificadosConsulta(1).get_nome() == c1.get_nome());
    CHECK(L_cursos.Consulta(1).EsperaConsulta(0).get_nome() == c5.get_nome());
    CHECK(L_cursos.Consulta(1).EsperaConsulta(1).get_nome() == c4.get_nome());
    CHECK(L_cursos.Consulta(1).get_nota_de_corte() == c1.get_nota());

    CHECK(L_cursos.Consulta(2).ClassificadosConsulta(0).get_nome() == c2.get_nome());
    CHECK(L_cursos.Consulta(2).ClassificadosConsulta(1).get_nome() == c5.get_nome());
    CHECK(L_cursos.Consulta(2).ClassificadosConsulta(2).get_nome() == c4.get_nome());








}