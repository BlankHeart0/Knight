#pragma once

#include "System.h"
#include "Type.h"
#include "Diagnostor.h"

class Variable
{
public:
    Type type;
    string name;
    int scope_i;

    Variable(){}
    Variable(Type type,string name,int scope_i):
        type(type),name(name),scope_i(scope_i){}
};

class VariableTable
{
private:
    vector<unordered_map<string,Variable>> table;

    int ScopeSize();
    bool Exist(string variable_name);

public:
    void EnterScope();
    void LeaveScope();
    
    void Add(Type type,string variable_name,int line);
    Variable& Visit(string variable_name,int line);
};



class Parameter
{
public:
    Type type;
    string name;

    Parameter(){}
    Parameter(Type type,string name):
        type(type),name(name){}
};

class Function
{
public:
    Type ret_type;
    bool is_void;
    string name;
    vector<Parameter> parameters; 
    VariableTable vartable;

    int lable_id;
    int NewLable();

    Function(){}
    Function(string name):
        is_void(true),name(name),lable_id(0){}
    Function(Type ret_type,string name):
        is_void(false),ret_type(ret_type),name(name),lable_id(0){}
};

class FunctionTable
{
private:
    unordered_map<string,Function> table;
    bool Exist(string function_name);

public:
    void Add(string function_name,int line);
    void Add(Type type,string function_name,int line);
    
    Function& Visit(string function_name);
    Function& Visit(string function_name,int line);
};



#define SYMBOL_ERROR(error_message)                             \
        do{                                                     \
            diagnostor.Error(E_SYMBOL,line,error_message);      \
        }while(0)
