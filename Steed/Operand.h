#pragma once

#include "System.h"
#include "SymbolTable.h"

// Maybe it can be replace to DataType
enum ConstantType
{
    C_INT,C_DEC,C_STR
};

class OperandConstant
{
public:
    ConstantType constant_type;

    int INT_val;
    double DEC_val;
    string STR_val;

    OperandConstant(int INT_val):constant_type(C_INT),INT_val(INT_val){}
    OperandConstant(double DEC_val):constant_type(C_DEC),DEC_val(DEC_val){}
    OperandConstant(string STR_val):constant_type(C_STR),STR_val(STR_val){}
};



enum RegisterType
{
    R_General
};

class OperandRegister
{
public:
    RegisterType register_type;
    int register_i;

    OperandRegister(RegisterType register_type,int register_i):
        register_type(register_type),register_i(register_i){}
};



class OperandType
{
public:
    DataType data_type;

    OperandType(DataType data_type):data_type(data_type){}
};

class OperandVariable
{
public: 
    string name;
    int scope_i;

    OperandVariable(string name,int scope_i):
        name(name),scope_i(scope_i){}
};