#pragma once

#include "System.h"
#include "Type.h"

class Register
{
public:
    DataType data_type;
    
    int INT_val;
    double DEC_val;
    string STR_val;
    bool BOOL_val;

    void Set(int int_val);
    void Set(double dec_val);
    void Set(string str_val);
    void Set(bool bool_val);
};

class RegisterTable
{
private:
    vector<Register> table;
    void Grow(int n);

public:
    RegisterTable():table(0){}

    void Set(int register_i,int int_val);
    void Set(int register_i,double dec_val);
    void Set(int register_i,string str_val);
    void Set(int register_i,bool bool_val);

    Register& Get(int register_i);
};

extern RegisterTable general_register;
extern RegisterTable argument_register;
extern Register      retvalue_register;