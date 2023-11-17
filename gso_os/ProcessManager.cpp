#include "ProcessManager.h"

ProcessManager::ProcessManager(int numRecursos) : gerenciadorRecursos(numRecursos) {
    aplicativos = {
        {1, "Editor de texto"},
        {2, "Editor de planilhas"},
        {3, "Editor de Apresentações"},
        {4, "Navegador"},
        {5, "Jogo"}
    };
}

void ProcessManager::criarProcesso(int id) {
    if (aplicativos.find(id) != aplicativos.end()) {
        Process novoProcesso(id);
        novoProcesso.recursosNecessarios = { ResourceType::CPU, ResourceType::DISK };
        novoProcesso.cpuUsage = 30;
        novoProcesso.memoryUsage = rand() % 101;

        filaNovos.push(novoProcesso);
    }
    else {
        std::cout << "Aplicativo não encontrado.\n";
    }
}

bool ProcessManager::existeExecucao(int pid) {
    return (pid - 1) >= 0 && (pid - 1) < executando.size();
}

void ProcessManager::fecharProcesso(int pid) {
    if (!executando.empty()) {
        Process process = executando[pid - 1];
        process.state = ProcessState::FINISHED;
        
        gerenciadorRecursos.liberarRecursos(process.recursosNecessarios);

        std::cout << "Aplicativo \x1B[33m" << aplicativos[process.id] << "\033[0m encerrado.\n";

        executando.erase(executando.begin() + (pid - 1));
        filaProntos.push(process);
    } else {
        std::cout << "Nenhum aplicativo está em execução.\n";
    }
}

void ProcessManager::escalonar() {
    if (!filaNovos.empty()) {
        Process proximoProcesso = filaNovos.front();
        if (gerenciadorRecursos.temRecursos(proximoProcesso.recursosNecessarios)) {

            gerenciadorRecursos.alocarRecursos(proximoProcesso.recursosNecessarios);

            executando.push_back(proximoProcesso);
            filaNovos.pop();
            proximoProcesso.state = ProcessState::RUNNING;
            std::cout << "Executando aplicativo \x1B[33m" << aplicativos[proximoProcesso.id] << "\033[0m.\n";
        } else {
            std::cout << "Recursos não disponíveis para executar o aplicativo \x1B[33m" << aplicativos[proximoProcesso.id] << "\033[0m.\n";

            std::cout << "O aplicativo \x1B[33m" << aplicativos[proximoProcesso.id] << "\033[0m será executado assim que recursos forem disponibilizados!\n";
        }
    }
}

void ProcessManager::execucacao() {
    if (!executando.empty()) {
        std::cout << "Processos em Execução:\n\n";

        size_t pid = 1;

        for (Process process : executando) {
            std::cout << "PID: " << std::setw(2) << std::setfill('0') << pid;

            std::cout << " | ";

            std::cout << "CPU Usage: " << std::setw(2) << std::setfill('0') << process.cpuUsage << "%";

            std::cout << " | ";

            std::cout << " Memory Usage: " << std::setw(3) << std::setfill('0') << process.memoryUsage << "MB";

            std::cout << " | ";

            std::cout << "Process: \x1B[33m" << aplicativos[process.id] << "\033[0m\n";
            
            ++pid;
        }

        std::cout << "\n" << "Para finalizar um processo, utilize o comando \x1B[35mkill\033[0m \x1B[95m{pid}\033[0m\n";
    }
    else {
        std::cout << "Nenhum aplicativo está em execução.\n";
    }
}

void ProcessManager::listarComandos() {
    std::cout << "Comandos disponíveis:\n\n";
    std::cout << "list: Lista todos os processos\n";
    std::cout << "run {id}: Executa um processo\n";
    std::cout << "kill {pid}: Encerra o processo em execução\n";
    std::cout << "running: Lista o processos em execução\n";
    std::cout << "clear: Limpa o Console\n";
    std::cout << "help: Lista todos os comandos possíveis\n";
    std::cout << "exit: Encerra o software\n";
}