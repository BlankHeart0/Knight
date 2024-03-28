#pragma once

#include "System.h"
#include "FileManager.h"
#include "Function.h"
#include "Parser.h"

class PC
{
public:
    string function_name;
    int instruction_id;
};

class VirtualMachine
{
private:
    FileManager file_manager;
    
public:
    FunctionTable functions;
    string nowInfunction;
    PC pc;

    void Initialize(string knightASM_file_name);
    void Load();
    void Run();

    Function& NowExcuteFunction();
};

extern VirtualMachine Steed;