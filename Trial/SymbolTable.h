#pragma once

#include "System.h"
#include "Token.h"
#include "Type.h"
#include "Diagnostor.h"

class Variable
{
public:
    DataType data_type;
    string name;
    int scope_i;

    Variable(){}
    Variable(DataType data_type,string name,int scope_i):
        data_type(data_type),name(name),scope_i(scope_i){}
};

class VariableTable
{
private:
    vector<unordered_map<string,Variable>> table;
    bool Exist(string variable_name);

public:
    void EnterScope();
    void LeaveScope();
    int ScopeSize();
    void Add(Token type,string variable_name);
    Variable Visit(Token variable);
};

#define SYMBOL_ERROR(error_message)                             \
        do{                                                     \
            diagnostor.Error(E_SYMBOL,line,error_message);      \
        }while(0)
