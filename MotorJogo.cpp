#include "MotorJogo.h"
#include "JogadorHumano.h"
#include "BotAleatorio.h"
#include "BotTatico.h"
#include <iostream>
#include <fstream>

MotorJogo::MotorJogo()
    : turnoAtual(0), vitorias(0), derrotas(0), empates(0), nivelBot(1) {}

void MotorJogo::configurarJogadores(std::unique_ptr<Jogador> j1, std::unique_ptr<Jogador> j2, int quemInicia, int nivel) {
    jogadores[0] = std::move(j1);
    jogadores[1] = std::move(j2);
    turnoAtual = quemInicia;
    nivelBot = nivel;
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

static std::string tipoJogador(const std::unique_ptr<Jogador>& j) {
    if (dynamic_cast<JogadorHumano*>(j.get()))  return "HUMANO";
    if (dynamic_cast<BotTatico*>(j.get()))       return "BOT_TATICO";
    if (dynamic_cast<BotAleatorio*>(j.get()))    return "BOT_ALEATORIO";
    return "DESCONHECIDO";
}

bool MotorJogo::suspenderJogo(const std::string& arquivo) const {
    std::ofstream fout(arquivo);
    if (!fout.is_open()) return false;

    for (int i = 0; i < 2; i++) {
        fout << tipoJogador(jogadores[i]) << " "
             << jogadores[i]->getNome()    << " "
             << jogadores[i]->getSimbolo() << "\n";
    }

    fout << turnoAtual << "\n";
    fout << nivelBot   << "\n";

    for (int i = 0; i < 9; i++) {
        char c = tabuleiro.getCasa(i);
        fout << (c == ' ' ? '.' : c);
    }
    fout << "\n";

    fout << tabuleiro.getNumJogadas() << "\n";
    fout << vitorias << " " << empates << " " << derrotas << "\n";

    return true;
}

bool MotorJogo::carregarJogo(const std::string& arquivo) {
    std::ifstream fin(arquivo);
    if (!fin.is_open()) return false;

    std::string tipos[2], nomes[2];
    char simbolos[2];

    for (int i = 0; i < 2; i++) {
        fin >> tipos[i] >> nomes[i] >> simbolos[i];
    }

    fin >> turnoAtual >> nivelBot;

    std::string casas;
    fin >> casas;

    fin >> vitorias >> empates >> derrotas;

    tabuleiro.reset();
    for (int i = 0; i < 9; i++) {
        if (casas[i] != '.') {
            tabuleiro.aplicarJogada(i, casas[i]);
        }
    }

    auto criarJogador = [&](const std::string& tipo, const std::string& nome, char simbolo) -> std::unique_ptr<Jogador> {
        char adv = (simbolo == 'X') ? 'O' : 'X';
        if (tipo == "HUMANO")
            return std::make_unique<JogadorHumano>(nome, simbolo);
        if (tipo == "BOT_TATICO") {
            NivelBot nb = (nivelBot == 2) ? NivelBot::BASICO : NivelBot::MEDIO;
            return std::make_unique<BotTatico>(nome, simbolo, adv, nb);
        }
        return std::make_unique<BotAleatorio>(nome, simbolo);
    };

    jogadores[0] = criarJogador(tipos[0], nomes[0], simbolos[0]);
    jogadores[1] = criarJogador(tipos[1], nomes[1], simbolos[1]);

    return true;
}

bool MotorJogo::temJogoSuspenso(const std::string& arquivo) const {
    std::ifstream fin(arquivo);
    return fin.is_open();
}

int MotorJogo::getVitorias() const { return vitorias; }
int MotorJogo::getDerrotas() const { return derrotas; }
int MotorJogo::getEmpates() const  { return empates;  }