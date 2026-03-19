#include "BotAleatorio.h"
#include <vector>
#include <iostream>

BotAleatorio::BotAleatorio(const std::string& nome, char simbolo)
    : Jogador(nome, simbolo), rng(std::random_device{}()) {}//gera um semente pelo hard

int BotAleatorio::escolherJogada(Tabuleiro& tab) {
    std::vector<int> livres;

    for (int i = 0; i < 9; i++) {
        if (tab.isPosicaoLivre(i)) livres.push_back(i);//garantir q n vai sobrescrever aque vc tu jogou
    }

    std::uniform_int_distribution<int> dist(0, livres.size() - 1);
    int escolha = livres[dist(rng)];

    std::cout << nome << " [" << simbolo << "] jogou na posicao " << (escolha + 1) << "\n";
    return escolha;
}