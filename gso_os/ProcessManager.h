#pragma once

#include <iostream>
#include <queue>
#include <map>
#include <iomanip>

#include "Process.h"
#include "ResourceManager.h"

class ProcessManager {
private:
    std::queue<Process> filaNovos;
    std::vector<Process> executando;
    std::queue<Process> filaProntos;
    std::queue<Process> filaBloqueados;
    ResourceManager gerenciadorRecursos;
    std::map<int, std::string> aplicativos;

public:
    ProcessManager(int numRecursos);

    void criarProcesso(int id);

    void fecharProcesso(int pid);

    void escalonar();

    void execucacao();

    bool existeExecucao(int pid);

    const std::map<int, std::string>& getAplicativos() const {
        return aplicativos;
    }

    void listarComandos();
};
