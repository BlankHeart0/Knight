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
    Variable& Visit(Token variable);
};



class Function
{
public:
    DataType ret_type;
    bool is_void;
    string name;
    VariableTable vartable;

    Function(){}
    Function(string name):
        is_void(true),name(name){}
    Function(DataType ret_type,string name):
        is_void(false),ret_type(ret_type),name(name){}
};

class FunctionTable
{
private:
    unordered_map<string,Function> table;
    bool Exist(string function_name);

public:
    void Add(Token type,string function_name);
    Function& Visit(Token function);
    Function& Visit(string function_name);
};




#define SYMBOL_ERROR(error_message)                             \
        do{                                                     \
            diagnostor.Error(E_SYMBOL,line,error_message);      \
        }while(0)
