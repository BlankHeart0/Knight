#pragma once

#include "System.h"
#include "Type.h"

class OperandConstant
{
public:
    DataType data_type;

    int    INT_val;
    double DEC_val;
    string STR_val;
    bool   BOOL_val;

    OperandConstant(int INT_val):   data_type(D_INT), INT_val(INT_val)  {}
    OperandConstant(double DEC_val):data_type(D_DEC), DEC_val(DEC_val)  {}
    OperandConstant(string STR_val):data_type(D_STR), STR_val(STR_val)  {}
    OperandConstant(bool BOOL_val): data_type(D_BOOL),BOOL_val(BOOL_val){}
};



enum RegisterType
{
    R_General,X_Argument,Y_Retvalue
};

class OperandRegister
{
public:
    RegisterType register_type;
    int register_i;

    OperandRegister(RegisterType register_type):
        register_type(register_type),register_i(-1){}
    OperandRegister(RegisterType register_type,int register_i):
        register_type(register_type),register_i(register_i){}
};



class OperandType
{
public:
    bool is_void;
    DataType data_type; 

    OperandType():is_void(true){}
    OperandType(DataType data_type):data_type(data_type),is_void(false){}
};



class OperandVariable
{
public: 
    string name;
    int scope_i;

    OperandVariable(string name,int scope_i):
        name(name),scope_i(scope_i){}
};



class OperandPermission
{
public:
    PermissionSet permissions;

    OperandPermission(PermissionSet permissions):permissions(permissions){}
};



class OperandName
{
public:
    string name;

    OperandName(string name):name(name){}
};

typedef OperandName OperandApplication;
typedef OperandName OperandFunction;



class OperandNatural
{
public:
    int N;

    OperandNatural(int N):N(N){}
};

typedef OperandNatural OperandLable;
typedef OperandNatural OperandFlag;
