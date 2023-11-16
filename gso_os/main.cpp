#include <iostream>
#include <locale>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <thread>
#include <chrono>
#include <regex>

#include "ProcessState.h"
#include "ResourceType.h"

#include "Process.h";
#include "ResourceManager.h"
#include "ProcessManager.h"

#include "Terminal.h"

int main() {
    setlocale(LC_ALL, "");

    srand(static_cast<unsigned int>(time(nullptr))); // Inicialização da semente para números aleatórios

    const int resourcesNumber = 3;

    ProcessManager gerenciador(resourcesNumber);

    std::string input;

    Terminal::loadingMessage("Iniciando o Sistema Operacional");

    Terminal::loadingMessage("Carregando Serviços de Rede");

    Terminal::loadingMessage("Inicializando Serviços de Hardware");

    Terminal::loadingMessage("Configurando Ambiente Terminal");

    Terminal::loadingMessage("Carregando Drivers de Dispositivos");

    Terminal::loadingMessage("Verificando Integridade do Sistema");

    Terminal::loadingMessage("Sistema Operacional inicializado com Sucesso!");

    system("cls");

    Terminal::welcomeMessage();

    system("timeout 1 > NUL");

    std::cout << "Digite um comando ('help' para exibir a lista de comandos):\n\n";

    while (true)
    {
        std::cout << "\x1B[32mdecolip\033[0m\x1B[35m@\033[0m\x1B[36mfatec\033[0m:\x1B[93m~/\033[0m $ ";

        std::getline(std::cin, input);

        if (input.empty())
            continue;

        std::string command;
        std::stringstream iss(input);

        iss >> command;

        if (command == "exit")
        {
            std::cout << "bye! o/\n";

            return 0;
        }
        else if (command == "help")
        {
            gerenciador.listarComandos();
        }
        else if (command == "clear")
        {
            system("cls");
        }
        else if (command == "running")
        {

        }
        else if (command == "kill")
        {
            gerenciador.fecharProcesso();
            gerenciador.escalonar();
        }
        else if (command == "list")
        {
            std::cout << "Listando Processos disponíveis para execução:\n\n";

            for (const auto& app : gerenciador.getAplicativos()) {
                std::cout << "[" << app.first << "]" << " " << app.second << "\n";
            }

            std::cout << "\n" << "Para executar um processo, utilize o comando \x1B[35mrun\033[0m \x1B[95m{id}\033[0m\n";
        }
        else if (command == "run" and input.substr(0, 4) == "run ")
        {
            std::regex pattern("\\d+");

            if (!input.substr(4).empty() and std::regex_match(input.substr(4), pattern)) {

                int id = std::stoi(input.substr(4));

                if (gerenciador.getAplicativos().find(id) != gerenciador.getAplicativos().end()) {
                    gerenciador.criarProcesso(id);
                    gerenciador.escalonar();
                }
                else {
                    std::cout << "ID de aplicativo inválido.\n";
                }
            } else {
                std::cout << "É necessário informar um id válido! \n";
            }
        }
        else
        {
            std::cout << "Comando não encontrado: " << command << "\n";
        }
    }
}