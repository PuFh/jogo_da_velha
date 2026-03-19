#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include "Tabuleiro.h"

class Jogador {
protected:
    std::string nome;
    char simbolo;

public:
    Jogador(const std::string& nome, char simbolo);

    virtual int escolherJogada(Tabuleiro& tab) = 0;//polimor
    virtual ~Jogador() = default; //Destrutor virt

    std::string getNome() const;
    char getSimbolo() const;
};

#endif