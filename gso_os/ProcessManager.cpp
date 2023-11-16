#include "ProcessManager.h"

ProcessManager::ProcessManager(int numRecursos) : gerenciadorRecursos(numRecursos) {
    aplicativos = {
        {1, "Editor de texto"},
        {2, "Editor de planilhas"},
        {3, "Editor de Apresenta��es"},
        {4, "Navegador"},
        {5, "Jogo"}
    };
}

void ProcessManager::criarProcesso(int id) {
    if (aplicativos.find(id) != aplicativos.end()) {
        Process novoProcesso(id); // Cria uma nova inst�ncia de Processo
        novoProcesso.recursosNecessarios = { ResourceType::CPU, ResourceType::DISK }; // Define recursos necess�rios
        novoProcesso.cpuUsage = 30; // Uso de CPU fixo em 30%
        novoProcesso.memoryUsage = rand() % 101; // Uso de mem�ria entre 0MB e 100MB

        if (!gerenciadorRecursos.alocarRecursos(novoProcesso.recursosNecessarios)) {
            std::cout << "Limite de recursos atingido. N�o � poss�vel abrir mais aplicativos.\n";
            return;
        }

        filaNovos.push(novoProcesso);
        std::cout << "Aplicativo " << aplicativos[id] << " aberto.\n";
    }
    else {
        std::cout << "Aplicativo n�o encontrado.\n";
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
        std::cout << "Nenhum aplicativo est� em execu��o.\n";
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
            std::cout << "Recursos n�o dispon�veis para executar pr�ximo aplicativo.\n";
        }
    }
    else {
        std::cout << "Nenhum aplicativo na fila de novos.\n";
    }
}

void ProcessManager::listarComandos() {
    std::cout << "Comandos dispon�veis:\n\n";
    std::cout << "list: Lista todos os processos\n";
    std::cout << "run {id}: Executa um processo\n";
    std::cout << "kill: Encerra o processo em execu��o\n";
    std::cout << "running: Lista o processos em execu��o\n";
    std::cout << "clear: Limpa o Console\n";
    std::cout << "help: Lista todos os comandos poss�veis\n";
    std::cout << "exit: Encerra o software\n";
}