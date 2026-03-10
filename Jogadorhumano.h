#ifndef JOGADORHUMANO_H
#define JOGADORHUMANO_H

#include "Jogador.h"

class JogadorHumano : public Jogador {
public:
    JogadorHumano(const std::string& nome, char simbolo);

    int escolherJogada(Tabuleiro& tab) override;
};

#endif