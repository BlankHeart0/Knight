#pragma once

#include "System.h"
#include "Diagnostor.h"
#include "Instruction.h"
#include "Type.h"
#include "Variable.h"

class Function
{
public:
    bool is_void;
    DataType data_type;
    
    vector<Instruction*> instructions;
    VariableTable variables;
    vector<int> lables;
    
    void Excute();
};

class FunctionTable
{
private:
    unordered_map<string,Function> table;

public:
    Function& Get(string name);
    void LoadInstruction(string name,Instruction* instruction);
};