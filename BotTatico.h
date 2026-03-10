#ifndef BOTTATICO_H
#define BOTTATICO_H

#include "BotAleatorio.h"

enum class NivelBot { BASICO = 2, MEDIO = 3 };

class BotTatico : public BotAleatorio {
private:
    NivelBot nivel;
    char simboloAdversario;

    int tentarJogada(Tabuleiro& tab, char sim) const;

public:
    BotTatico(const std::string& nome, char simbolo, char simboloAdversario, NivelBot nivel);

    int escolherJogada(Tabuleiro& tab) override;
};

#endif
