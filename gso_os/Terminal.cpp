#include "Terminal.h"

#include <thread>
#include <chrono>

void Terminal::loadingMessage(std::string message) {
    int interval = 300;

    std::cout << message;

    for (int j = 0; j < 3; ++j) {
        std::cout << ".";

        std::this_thread::sleep_for(
            std::chrono::milliseconds(interval)
        );
    }

    std::cout << "\n";
}

void Terminal::loadSystem() {
    loadingMessage("Iniciando o Sistema Operacional");

    loadingMessage("Carregando Servi�os de Rede");

    loadingMessage("Inicializando Servi�os de Hardware");

    loadingMessage("Configurando Ambiente Terminal");

    loadingMessage("Carregando Drivers de Dispositivos");

    loadingMessage("Verificando Integridade do Sistema");

    loadingMessage("Sistema Operacional inicializado com Sucesso");

    system("cls");

    welcomeMessage();
}

void Terminal::welcomeMessage() {
    std::cout << "\n";
    std::cout << "   _____                  _       _\n";
    std::cout << "  | __  |___ _____    _ _|_|___ _| |___\n";
    std::cout << "  | __ -| -_|     |  | | | |   | . | . |\n";
    std::cout << "  |_____|___|_|_|_|   \\_/|_|_|_|___|___|\n";
    std::cout << "   ____              _ _\n";
    std::cout << "  |    \\ ___ ___ ___| |_|___\n";
    std::cout << "  |  |  | -_|  _| . | | | . |\n";
    std::cout << "  |____/|___|___|___|_|_|  _|\n";
    std::cout << "                        |_|\n";
    std::cout << "\n";
}