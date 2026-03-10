#include "Tabuleiro.h"
#include <iostream>

Tabuleiro::Tabuleiro() : numJogadas(0) {
    casas.fill(' ');
}

void Tabuleiro::aplicarJogada(int pos, char simbolo) {
    casas[pos] = simbolo;
    numJogadas++;
}

char Tabuleiro::verificarVencedor() const {
    const int combinacoes[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto& combo : combinacoes) {
        char a = casas[combo[0]];
        char b = casas[combo[1]];
        char c = casas[combo[2]];
        if (a != ' ' && a == b && b == c) return a;
    }

    return ' ';
}

bool Tabuleiro::isCheio() const {
    return numJogadas >= 9;
}

bool Tabuleiro::isPosicaoLivre(int pos) const {
    if (pos < 0 || pos > 8) return false;
    return casas[pos] == ' ';
}

void Tabuleiro::imprimirTabuleiro() const {
    std::cout << "\n";
    for (int i = 0; i < 9; i++) {
        if (casas[i] == ' ') {
            std::cout << " " << (i + 1) << " ";
        } else {
            std::cout << " " << casas[i] << " ";
        }

        if ((i + 1) % 3 == 0) {
            std::cout << "\n";
            if (i < 6) std::cout << "---+---+---\n";
        } else {
            std::cout << "|";
        }
    }
    std::cout << "\n";
}

void Tabuleiro::reset() {
    casas.fill(' ');
    numJogadas = 0;
}

int Tabuleiro::getNumJogadas() const {
    return numJogadas;
}

char Tabuleiro::getCasa(int pos) const {
    return casas[pos];
}

void Tabuleiro::corrigirContador() {
    if (numJogadas > 0) numJogadas--;
}