#pragma once

#include <iostream>
#include <queue>
#include <map>

#include "Process.h"
#include "ResourceManager.h"

class ProcessManager {
private:
    std::queue<Process> filaNovos;
    std::queue<Process> filaProntos;
    Process processoExecutando;
    std::queue<Process> filaBloqueados;
    ResourceManager gerenciadorRecursos;
    std::map<int, std::string> aplicativos;

public:
    ProcessManager(int numRecursos);

    void criarProcesso(int id);

    void fecharProcesso();

    void escalonar();

    const std::map<int, std::string>& getAplicativos() const {
        return aplicativos;
    }

    void listarComandos();
};
