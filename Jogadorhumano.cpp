#include "Jogadorhumano.h"
#include <iostream>
#include <limits>

JogadorHumano::JogadorHumano(const std::string& nome, char simbolo)
    : Jogador(nome, simbolo) {}

int JogadorHumano::escolherJogada(Tabuleiro& tab) {
    int pos;

    while (true) {
        std::cout << nome << " [" << simbolo << "], escolha uma posicao (1-9, 0 para suspender): ";

        if (!(std::cin >> pos)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Digite um numero.\n";
            continue;
        }

        if (pos == 0) return -1;

        if (pos < 1 || pos > 9) {
            std::cout << "Posicao invalida. Escolha entre 1 e 9.\n";
            continue;
        }

        if (!tab.isPosicaoLivre(pos - 1)) {
            std::cout << "Posicao ocupada. Tente outra.\n";
            continue;
        }

        return pos - 1;
    }
}