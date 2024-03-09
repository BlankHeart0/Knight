#pragma once

#include "System.h"

// Maybe it can be replace to DataType
enum StoreType
{
    S_NULL,
    S_INT,
    S_DEC,
    S_STR
};

static vector<string> StoreType_text
{
    "S_NULL",
    "S_INT",
    "S_DEC",
    "S_STR"
};

class Register
{
public:
    StoreType store_type;
    
    int INT_val;
    double DEC_val;
    string STR_val;

    Register():store_type(S_NULL){}
};

class GeneralRegister
{
public:
    vector<Register> table;

    GeneralRegister():table(0){}

    void Set(int register_i,int int_val);
    void Set(int register_i,double dec_val);
    void Set(int register_i,string str_val);

    Register& GetReg(int register_i);

    void Grow(int n);
};

extern GeneralRegister general_register;