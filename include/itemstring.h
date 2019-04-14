#ifndef ITEM_STRING_H
#define ITEM_STRING_H

#include <string>

typedef std::string TipoChave;

class ItemString{
private:
    TipoChave Chave;
    std::string Dado;
public:
    ItemString(std::string _Dado);
    ItemString();
    std::string get_dado();
};



#endif /* ITEM_STRING_H */