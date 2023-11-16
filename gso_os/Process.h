#pragma once

#include <iostream>
#include <vector>

#include "ProcessState.h"
#include "ResourceType.h"

struct Process {
    int id;
    ProcessState state;
    std::vector<ResourceType> recursosNecessarios;
    int cpuUsage;
    int memoryUsage;

    Process(int _id);
    Process();
};

