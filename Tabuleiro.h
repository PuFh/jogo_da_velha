#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <array>

class Tabuleiro {
private:
    std::array<char, 9> casas;
    int numJogadas;

public:
    Tabuleiro();

    void aplicarJogada(int pos, char simbolo);
    char verificarVencedor() const;
    bool isCheio() const;
    bool isPosicaoLivre(int pos) const;
    void imprimirTabuleiro() const;
    void reset();

    int getNumJogadas() const;
    char getCasa(int pos) const;
    void corrigirContador();
};

#endif