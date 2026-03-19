#include <iostream>
#include <memory>
#include <limits>
#include <random>

#include "MotorJogo.h"
#include "JogadorHumano.h"
#include "BotAleatorio.h"
#include "BotTatico.h"

const std::string ARQUIVO_SAVE = "jogo_salvo.txt";

int lerOpcao(const std::string& prompt, int min, int max) {
    int op;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Digite um numero.\n";
            continue;
        }
        if (op >= min && op <= max) return op;
        std::cout << "Opcao invalida. Escolha entre " << min << " e " << max << ".\n";
    }
}

std::unique_ptr<Jogador> criarBot(char simbolo, char simboloAdv, int nivel) {
    if (nivel == 1)
        return std::make_unique<BotAleatorio>("Computador", simbolo);
    NivelBot nb = (nivel == 2) ? NivelBot::BASICO : NivelBot::MEDIO;
    return std::make_unique<BotTatico>("Computador", simbolo, simboloAdv, nb);
}

void exibirMenu(bool temSave) {
    std::cout << "\n====== JOGO DA VELHA ======\n";
    std::cout << "1. " << (temSave ? "Iniciar/continuar jogo" : "Iniciar novo jogo") << "\n";
    std::cout << "2. Escolher quem inicia\n";
    std::cout << "3. Modo de dificuldade\n";
    std::cout << "4. Suspender jogo\n";
    std::cout << "5. Mostrar Top 10\n";
    std::cout << "6. Sair\n";
    std::cout << "===========================\n";
}

int main() {
    MotorJogo motor;

    int quemInicia  = 0;
    int nivelBot    = 1;
    bool emPartida  = false;

    while (true) {
        bool temSave = motor.temJogoSuspenso(ARQUIVO_SAVE);
        exibirMenu(temSave);
        int op = lerOpcao("Escolha: ", 1, 6);

        switch (op) {
            case 1: {
                if (temSave) {
                    std::cout << "\n1. Novo jogo\n2. Continuar jogo suspenso\n";
                    int sub = lerOpcao("Escolha: ", 1, 2);
                    

                    if (sub == 2) {
                        if (motor.carregarJogo(ARQUIVO_SAVE)) {
                            std::cout << "Jogo carregado!\n";
                            std::remove(ARQUIVO_SAVE.c_str());
                            emPartida = true;
                            motor.jogar();
                            emPartida = false;
                        } else {
                            std::cout << "Erro ao carregar o jogo.\n";
                        }
                        break;
                    }
                }

                int inicio = quemInicia;
                if (inicio == 2) {
                    std::mt19937 rng(std::random_device{}());
                    inicio = std::uniform_int_distribution<int>(0, 1)(rng);
                }

                auto humano = std::make_unique<JogadorHumano>("Humano", 'X');
                auto bot    = criarBot('O', 'X', nivelBot);

                //transfere os jogadores para motor
                motor.configurarJogadores(std::move(humano), std::move(bot), inicio, nivelBot);
                emPartida = true;
                motor.jogar();
                emPartida = false;
                break;
            }

            case 2: {
                std::cout << "\nQuem inicia?\n";
                std::cout << "0. Humano\n1. Computador\n2. Aleatorio\n";
                quemInicia = lerOpcao("Escolha: ", 0, 2);
                std::cout << "Ok!\n";
                break;
            }

            case 3: {
                std::cout << "\nNivel de dificuldade:\n";
                std::cout << "1. Elementar (aleatorio)\n";
                std::cout << "2. Basico (tenta vencer)\n";
                std::cout << "3. Medio (vence ou bloqueia)\n";
                nivelBot = lerOpcao("Escolha: ", 1, 3);
                std::cout << "Nivel alterado!\n";
                break;
            }

            case 4: {
                if (!emPartida) {
                    std::cout << "Nenhum jogo em andamento para suspender.\n";
                    break;
                }
                if (motor.suspenderJogo(ARQUIVO_SAVE)) {
                    std::cout << "Jogo suspenso e salvo!\n";
                    return 0;
                } else {
                    std::cout << "Erro ao salvar o jogo.\n";
                }
                break;
            }

            case 5:
                motor.exibirRanking();
                break;

            case 6: {
                int conf = lerOpcao("Confirma saida? (1=Sim / 0=Nao): ", 0, 1);
                if (conf == 1) {
                    std::cout << "Ate logo!\n";
                    return 0;
                }
                break;
            }
        }
    }

    return 0;
}