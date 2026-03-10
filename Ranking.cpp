#include "Ranking.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Ranking::Ranking() {
    carregarArquivo();
}

void Ranking::carregarArquivo() {
    std::ifstream fin(arquivo);
    if (!fin.is_open()) return;

    EntradaRanking e;
    while (fin >> e.nome >> e.vitorias >> e.empates >> e.derrotas) {
        entradas.push_back(e);
    }
}

void Ranking::salvarArquivo() const {
    std::ofstream fout(arquivo);
    for (const auto& e : entradas) {
        fout << e.nome << " " << e.vitorias << " " << e.empates << " " << e.derrotas << "\n";
    }
}

void Ranking::registrarResultado(const std::string& nome, int vitorias, int empates, int derrotas) {
    for (auto& e : entradas) {
        if (e.nome == nome) {
            e.vitorias += vitorias;
            e.empates  += empates;
            e.derrotas += derrotas;
            salvarArquivo();
            return;
        }
    }

    entradas.push_back({nome, vitorias, empates, derrotas});
    salvarArquivo();
}

void Ranking::exibirTop10() const {
    if (entradas.empty()) {
        std::cout << "\nNenhum registro encontrado.\n";
        return;
    }

    auto copia = entradas;
    std::sort(copia.begin(), copia.end(), [](const EntradaRanking& a, const EntradaRanking& b) {
        return a.vitorias > b.vitorias;
    });

    std::cout << "\n======= TOP 10 =======\n";
    std::cout << "Nome            V   E   D\n";
    std::cout << "-------------------------\n";

    int limite = std::min((int)copia.size(), 10);
    for (int i = 0; i < limite; i++) {
        const auto& e = copia[i];
        std::cout << i + 1 << ". " << e.nome;
        for (int s = e.nome.size(); s < 14; s++) std::cout << ' ';
        std::cout << e.vitorias << "   " << e.empates << "   " << e.derrotas << "\n";
    }
    std::cout << "======================\n";
}
