#pragma once

#include "System.h"
#include "Type.h"
#include "Diagnostor.h"

class Register
{
public:
    DataType data_type;
    bool free;

    Register():free(true){}
};

class GeneralRegister
{
public:
    vector<Register> table;

    GeneralRegister():table(8){}
    
    string Name(int register_i);
    Register& GetReg(int register_i);

    int Alloc(DataType data_type);
    void Free(int register_i);
    void Grow();

    void Print();
};

extern GeneralRegister general_register;

#define REGISTER_ERROR(error_message)                     \
        do{                                               \
            diagnostor.Error(E_REGISTER,error_message);   \
        }while(0)
