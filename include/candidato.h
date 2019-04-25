#ifndef CANDIDATO_H
#define CANDIDATO_H

class Candidato{
private:
    const char* nome;
    double nota;
    int i_curso1;
    int i_curso2;

public:
    Candidato(const char* _nome, double _nota, int _i_curso, int _i_curso2);

    const char* get_nome();
    int get_curso_1();
    int get_curso_2();
    double get_nota();
};



#endif /* CANDIDATO_H */