#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "itemstring.h"

TEST_CASE("ItemString: construtor"){
    CHECK_NOTHROW(ItemString("Teste"));
}

TEST_CASE("ItemString: construtor com entradas invalidas"){
    CHECK_THROWS_AS(ItemString(""),std::invalid_argument);
    CHECK_NOTHROW(ItemString("123"));
}

TEST_CASE("ItemString: construtor vazio"){
    CHECK_NOTHROW(ItemString());
}

TEST_CASE("ItemString: getters"){
    ItemString item("teste");
    CHECK(item.get_dado() == "teste");
    ItemString item2;
    CHECK(item2.get_dado() == "");
}