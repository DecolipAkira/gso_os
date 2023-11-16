#pragma once

#include <iostream>
#include <vector>

#include "ResourceType.h"

class ResourceManager {
private:
    std::vector<int> recursosDisponiveis;

public:
    ResourceManager(int numRecursos);

    bool alocarRecursos(const std::vector<ResourceType>& recursos);

    void liberarRecursos(const std::vector<ResourceType>& recursos);
};