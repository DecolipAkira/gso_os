#include "ResourceManager.h"

ResourceManager::ResourceManager(int numRecursos) : recursosDisponiveis(numRecursos, 100) {}

bool ResourceManager::alocarRecursos(const std::vector<ResourceType>& recursos) {
    // Verifica se há pelo menos 30 unidades disponíveis de cada recurso
    for (ResourceType recurso : recursos) {
        if (recursosDisponiveis[static_cast<int>(recurso)] < 30) {
            return false; // Recursos insuficientes
        }
    }

    // Subtrai 30 unidades de cada recurso alocado
    for (ResourceType recurso : recursos) {
        recursosDisponiveis[static_cast<int>(recurso)] -= 30;
    }

    return true; // Recursos alocados com sucesso
}

// Libera recursos de um processo
void ResourceManager::liberarRecursos(const std::vector<ResourceType>& recursos) {
    // Adiciona 30 unidades de cada recurso liberado
    for (ResourceType recurso : recursos) {
        recursosDisponiveis[static_cast<int>(recurso)] += 30;
    }
}