#pragma once

#include "System.h"
#include "Instruction.h"
#include "Type.h"
#include "Variable.h"
#include "Context.h"
#include "Diagnostor.h"

class Function
{
public:
    bool is_void;
    DataType data_type;
    
    vector<unique_ptr<Instruction>> instructions;
    VariableTable variables;
    unordered_map<int,int> lables;
};

class FunctionTable
{
private:
    unordered_map<string,Function> table;

public:
    void New(string name);
    Function& Get(string name);
};

class FunctionStack
{
private:
    stack<Context> context;

public:
    void Push();
    void Pop();
};

extern FunctionStack function_stack;