#pragma once

#include "System.h"

enum DataType
{
    D_INT,D_DEC,D_STR
};

class Variable{
public:
    DataType data_type;
    string name;

    int INT_val;
    double DEC_val;
    string STR_val;

    Variable(){}
    Variable(string name,int int_val):
        data_type(D_INT),name(name),INT_val(int_val){}
    Variable(string name,double dec_val):
        data_type(D_DEC),name(name),DEC_val(dec_val){}
    Variable(string name,string str_val):
        data_type(D_STR),name(name),STR_val(str_val){}
};

class VariableTable
{
private:
    vector<unordered_map<string,Variable>> table;

public:
    void Set(int scope_i,string name,int int_val);
    void Set(int scope_i,string name,double dec_val);
    void Set(int scope_i,string name,string str_val);
    
    Variable& GetVariable(int scope_i,string name);
    
    void Grow(int n);
};