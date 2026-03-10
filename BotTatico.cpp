#include "BotTatico.h"
#include <iostream>

BotTatico::BotTatico(const std::string& nome, char simbolo, char simboloAdversario, NivelBot nivel)
    : BotAleatorio(nome, simbolo), nivel(nivel), simboloAdversario(simboloAdversario) {}

int BotTatico::tentarJogada(Tabuleiro& tab, char sim) const {
    for (int i = 0; i < 9; i++) {
        if (!tab.isPosicaoLivre(i)) continue;

        tab.aplicarJogada(i, sim);
        char vencedor = tab.verificarVencedor();
        tab.aplicarJogada(i, ' ');
        tab.corrigirContador();

        if (vencedor == sim) return i;
    }
    return -1;
}

int BotTatico::escolherJogada(Tabuleiro& tab) {
    int pos = tentarJogada(tab, simbolo);

    if (pos == -1 && nivel == NivelBot::MEDIO)
        pos = tentarJogada(tab, simboloAdversario);

    if (pos == -1)
        pos = BotAleatorio::escolherJogada(tab);
    else
        std::cout << nome << " [" << simbolo << "] jogou na posicao " << (pos + 1) << "\n";

    return pos;
}
