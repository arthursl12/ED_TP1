#ifndef CURSO_H
#define CURSO_H

#include <string>

class Curso{
private:
    std::string nome;
    double nota_de_corte;
    int vagas;

public:
    Curso(std::string _nome, int _vagas);
    Curso();

    std::string get_nome();
    double get_nota_de_corte();
    int get_vagas();
};



#endif /* CURSO_H */