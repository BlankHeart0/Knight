#pragma once

#include "System.h"
#include "Variable.h"

class PC
{
public:
    string excuting_function;
    int instruction_id;
};

class Context
{
public:
    PC pc;
    VariableTable variables;

    Context(PC pc,VariableTable variables):
        pc(pc),variables(variables){}
};