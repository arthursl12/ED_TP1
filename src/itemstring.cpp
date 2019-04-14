#include "itemstring.h"
#include <stdexcept>

/* Construtor do ItemString */
ItemString::ItemString(std::string _dado){
    if (_dado == "")
        throw std::invalid_argument("String vazia");
    Dado = _dado;
    Chave = _dado;
}

/* Construtor Vazio */
ItemString::ItemString(){
    this->Dado = "";
    this->Chave = "";
}

/* Retorna a string guardada no ItemString */
std::string ItemString::get_dado(){
    return this->Dado;
}
