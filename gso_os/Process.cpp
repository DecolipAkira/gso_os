#include "Process.h"

Process::Process(int _id) : id(_id), state(ProcessState::NEW), cpuUsage(0), memoryUsage(0) {}

Process::Process() : id(-1), state(ProcessState::NEW), cpuUsage(0), memoryUsage(0) {}
