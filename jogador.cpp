#include "Jogador.h"

Jogador::Jogador(const std::string& nome, char simbolo)
    : nome(nome), simbolo(simbolo) {}

std::string Jogador::getNome() const {
    return nome;
}

char Jogador::getSimbolo() const {
    return simbolo;
}