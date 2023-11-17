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

    srand(static_cast<unsigned int>(time(nullptr)));

    const int resourcesNumber = 3;

    ProcessManager gerenciador(resourcesNumber);

    std::string input;

    Terminal::loadSystem();

    system("timeout 1 > NUL");

    std::cout << "Digite um comando ('help' para exibir a lista de comandos):\n\n";

    std::regex pattern("\\d+");

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
            gerenciador.execucacao();
        }
        else if (command == "kill" and input.substr(0, 5) == "kill ")
        {
            if (!input.substr(5).empty() and std::regex_match(input.substr(5), pattern)) {
                int pid = std::stoi(input.substr(5));

                if (gerenciador.existeExecucao(pid)) {
                    gerenciador.fecharProcesso(pid);
                    gerenciador.escalonar();
                } else {
                    std::cout << "Processo não encontrado!\n";
                }
            } else {
                std::cout << "É necessário informar um PID válido! \n";
            }
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