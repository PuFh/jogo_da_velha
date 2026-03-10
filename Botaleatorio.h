#ifndef BOTALEATORIO_H
#define BOTALEATORIO_H

#include "Jogador.h"
#include <random>

class BotAleatorio : public Jogador {
protected:
    std::mt19937 rng;

public:
    BotAleatorio(const std::string& nome, char simbolo);

    int escolherJogada(Tabuleiro& tab) override;
};

#endif