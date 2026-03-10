#ifndef RANKING_H
#define RANKING_H

#include <string>
#include <vector>

struct EntradaRanking {
    std::string nome;
    int vitorias;
    int empates;
    int derrotas;
};

class Ranking {
private:
    std::vector<EntradaRanking> entradas;
    const std::string arquivo = "top10.txt";

    void carregarArquivo();
    void salvarArquivo() const;

public:
    Ranking();

    void registrarResultado(const std::string& nome, int vitorias, int empates, int derrotas);
    void exibirTop10() const;
};

#endif
