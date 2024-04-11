#pragma once

#include "System.h"
#include "FileManager.h"
#include "Type.h"
#include "Function.h"
#include "Parser.h"
#include "Context.h"

class VirtualMachine
{
private:
    FileManager file_manager;
    
public:
    PermissionSet program_permissions;
    FunctionTable functions;
    string parsing_function;
    PC pc;
    bool is_stop;

    void Initialize(string knightASM_file_name);
    void Load();
    void Run();

    Function& ParsingFunction();
    Function& ExcutingFunction();
};

extern VirtualMachine Steed;