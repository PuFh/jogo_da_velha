#include "MotorJogo.h"
#include <iostream>

MotorJogo::MotorJogo()
    : turnoAtual(0), vitorias(0), derrotas(0), empates(0) {}

void MotorJogo::configurarJogadores(std::unique_ptr<Jogador> j1, std::unique_ptr<Jogador> j2, int quemInicia) {
    jogadores[0] = std::move(j1);
    jogadores[1] = std::move(j2);
    turnoAtual = quemInicia;
}

void MotorJogo::imprimirInfo() const {
    std::cout << "Jogada: " << (tabuleiro.getNumJogadas() + 1)
              << " | Vez de: " << jogadores[turnoAtual]->getNome()
              << " [" << jogadores[turnoAtual]->getSimbolo() << "]\n";
}

void MotorJogo::imprimirEstatisticas() const {
    std::cout << "\n=== Estatisticas da sessao ===\n";
    std::cout << "Vitorias: " << vitorias
              << " | Empates: " << empates
              << " | Derrotas: " << derrotas << "\n";
    std::cout << "==============================\n";
}

void MotorJogo::registrarNoRanking() {
    std::string nome;
    std::cout << "Digite seu nome para o ranking: ";
    std::cin >> nome;
    ranking.registrarResultado(nome, vitorias, empates, derrotas);
    std::cout << "Resultado salvo no ranking!\n";
}

void MotorJogo::jogar() {
    while (true) {
        tabuleiro.imprimirTabuleiro();
        imprimirInfo();

        int pos = jogadores[turnoAtual]->escolherJogada(tabuleiro);

        if (pos == -1) {
            std::cout << "Jogo suspenso.\n";
            return;
        }

        tabuleiro.aplicarJogada(pos, jogadores[turnoAtual]->getSimbolo());

        char vencedor = tabuleiro.verificarVencedor();
        if (vencedor != ' ') {
            tabuleiro.imprimirTabuleiro();
            std::cout << "\n*** " << jogadores[turnoAtual]->getNome() << " venceu! ***\n";

            if (turnoAtual == 0)
                vitorias++;
            else
                derrotas++;

            imprimirEstatisticas();
            registrarNoRanking();
            resetarPartida();
            return;
        }

        if (tabuleiro.isCheio()) {
            tabuleiro.imprimirTabuleiro();
            std::cout << "\n*** Empate! ***\n";
            empates++;
            imprimirEstatisticas();
            registrarNoRanking();
            resetarPartida();
            return;
        }

        turnoAtual = 1 - turnoAtual;
    }
}

void MotorJogo::resetarPartida() {
    tabuleiro.reset();
    turnoAtual = 0;
}

void MotorJogo::exibirRanking() const {
    ranking.exibirTop10();
}

int MotorJogo::getVitorias() const { return vitorias; }
int MotorJogo::getDerrotas() const { return derrotas; }
int MotorJogo::getEmpates() const  { return empates;  }