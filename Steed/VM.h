#pragma once

#include "System.h"
#include "FileManager.h"

class VirtualMachine
{
private:
    FileManager file_manager;

public:
    void Initialize(string knightASM_file_name);
    void Load();
    void Run();
};