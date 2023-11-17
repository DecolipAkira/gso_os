#include "ResourceManager.h"

ResourceManager::ResourceManager(int numRecursos) : recursosDisponiveis(numRecursos, 100) {}

bool ResourceManager::temRecursos(const std::vector<ResourceType>& recursos) {
    for (ResourceType recurso : recursos) {
        if (recursosDisponiveis[static_cast<int>(recurso)] < 30) {
            return false;
        }
    }

    return true;
}

bool ResourceManager::alocarRecursos(const std::vector<ResourceType>& recursos) {
    for (ResourceType recurso : recursos) {
        if (recursosDisponiveis[static_cast<int>(recurso)] < 30) {
            return false;
        }
    }

    for (ResourceType recurso : recursos) {
        recursosDisponiveis[static_cast<int>(recurso)] -= 30;
    }

    return true;
}

void ResourceManager::liberarRecursos(const std::vector<ResourceType>& recursos) {
    for (ResourceType recurso : recursos) {
        recursosDisponiveis[static_cast<int>(recurso)] += 30;
    }
}