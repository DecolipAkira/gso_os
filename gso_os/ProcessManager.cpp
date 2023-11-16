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
        Process novoProcesso(id); // Cria uma nova instƒncia de Processo
        novoProcesso.recursosNecessarios = { ResourceType::CPU, ResourceType::DISK }; // Define recursos necessários
        novoProcesso.cpuUsage = 30; // Uso de CPU fixo em 30%
        novoProcesso.memoryUsage = rand() % 101; // Uso de mem¢ria entre 0MB e 100MB

        if (!gerenciadorRecursos.alocarRecursos(novoProcesso.recursosNecessarios)) {
            std::cout << "Limite de recursos atingido. Não ‚ possível abrir mais aplicativos.\n";
            return;
        }

        filaNovos.push(novoProcesso);
        std::cout << "Aplicativo " << aplicativos[id] << " aberto.\n";
    }
    else {
        std::cout << "Aplicativo não encontrado.\n";
    }
}

void ProcessManager::fecharProcesso() {
    if (processoExecutando.state == ProcessState::RUNNING) {
        int idFechado = processoExecutando.id;
        gerenciadorRecursos.liberarRecursos(processoExecutando.recursosNecessarios);
        std::cout << "Aplicativo " << aplicativos[idFechado] << " encerrado.\n";
        processoExecutando.state = ProcessState::FINISHED;
        processoExecutando = Process();
    }
    else {
        std::cout << "Nenhum aplicativo está em execução.\n";
    }
}

void ProcessManager::escalonar() {
    if (!filaNovos.empty()) {
        Process proximoProcesso = filaNovos.front();
        if (gerenciadorRecursos.alocarRecursos(proximoProcesso.recursosNecessarios)) {
            processoExecutando = proximoProcesso;
            filaNovos.pop();
            processoExecutando.state = ProcessState::RUNNING;
            std::cout << "Executando aplicativo " << aplicativos[processoExecutando.id] << "\n";
        }
        else {
            std::cout << "Recursos não disponíveis para executar próximo aplicativo.\n";
        }
    }
    else {
        std::cout << "Nenhum aplicativo na fila de novos.\n";
    }
}

void ProcessManager::listarComandos() {
    std::cout << "Comandos disponíveis:\n\n";
    std::cout << "list: Lista todos os processos\n";
    std::cout << "run {id}: Executa um processo\n";
    std::cout << "kill: Encerra o processo em execução\n";
    std::cout << "running: Lista o processos em execução\n";
    std::cout << "clear: Limpa o Console\n";
    std::cout << "help: Lista todos os comandos possíveis\n";
    std::cout << "exit: Encerra o software\n";
}