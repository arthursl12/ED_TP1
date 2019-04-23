#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>

class Candidato{
private:
    std::string nome;
    double nota;
    int i_curso1;
    int i_curso2;

public:
    Candidato(std::string _nome, double _nota, int _i_curso, int _i_curso2);
    Candidato();

    std::string get_nome();
    int get_curso_1();
    int get_curso_2();
    double get_nota();
};



#endif /* CANDIDATO_H */