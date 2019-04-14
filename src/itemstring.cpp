#include "itemstring.h"

/* Construtor do ItemString */
ItemString::ItemString(std::string _dado){
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
