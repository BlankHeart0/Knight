#pragma once

#include "System.h"
#include "Type.h"
#include "Diagnostor.h"

class Register
{
public:
    Type type;
    bool free;

    Register():free(true){}
};

class GeneralRegister
{
public:
    vector<Register> table;

    GeneralRegister():table(8){}
    
    string Name(int r_i);
    Register& GetReg(int r_i);

    int Alloc(Type type);
    void Free(int r_i);
    void Grow();

    void Print();
};

extern GeneralRegister general_register;
