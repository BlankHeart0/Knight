#pragma once

#include "System.h"
#include "Type.h"
#include "Diagnostor.h"

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
    void Set(Register& reg);
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
    void Set(int register_i,Register& reg);

    Register& Get(int register_i);
    Register Copy(int register_i);
};

class RegisterStack
{
private:
    stack<Register> regstack;

public:
    void Push(Register reg);
    void Pop(Register& reg);
};

extern RegisterTable general_register;
extern RegisterTable argument_register;
extern Register      retvalue_register;

extern RegisterStack register_stack;
