#pragma once

#include "System.h"
#include "Instruction.h"
#include "SymbolTable.h"

class Function
{
public:
    //string name;
    vector<Instruction*> instructions;
    VariableTable vartable;
    
    void Excute();
};