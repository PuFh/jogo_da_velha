#ifndef MOTORJOGO_H
#define MOTORJOGO_H

#include "Tabuleiro.h"
#include "Jogador.h"
#include "Ranking.h"
#include <memory>
#include <string>

class MotorJogo {
private:
    Tabuleiro tabuleiro;
    std::unique_ptr<Jogador> jogadores[2];
    int turnoAtual;
    int vitorias;
    int derrotas;
    int empates;
    int nivelBot;
    Ranking ranking;

    void imprimirInfo() const;
    void imprimirEstatisticas() const;
    void registrarNoRanking();

public:
    MotorJogo();

    void configurarJogadores(std::unique_ptr<Jogador> j1, std::unique_ptr<Jogador> j2, int quemInicia, int nivel);
    void jogar();
    void resetarPartida();
    void exibirRanking() const;

    bool suspenderJogo(const std::string& arquivo) const;
    bool carregarJogo(const std::string& arquivo);
    bool temJogoSuspenso(const std::string& arquivo) const;

    int getVitorias() const;
    int getDerrotas() const;
    int getEmpates() const;
};

#endif