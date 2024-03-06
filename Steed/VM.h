#pragma once

#include "System.h"
#include "FileManager.h"
#include "Function.h"
#include "Parser.h"

class VirtualMachine
{
private:
    FileManager file_manager;
    
public:
    Function main;

    void Initialize(string knightASM_file_name);
    void Load();
    void Run();
};

extern VirtualMachine Steed;