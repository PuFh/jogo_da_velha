#ifndef MOTORJOGO_H
#define MOTORJOGO_H

#include "Tabuleiro.h"
#include "Jogador.h"
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

    void imprimirInfo() const;
    void imprimirEstatisticas() const;

public:
    MotorJogo();

    void configurarJogadores(std::unique_ptr<Jogador> j1, std::unique_ptr<Jogador> j2, int quemInicia);
    void jogar();
    void resetarPartida();

    int getVitorias() const;
    int getDerrotas() const;
    int getEmpates() const;
};

#endif
