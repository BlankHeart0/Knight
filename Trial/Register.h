#pragma once

#include "System.h"
#include "Diagnostor.h"

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
    bool free;

    Register():store_type(S_NULL),free(true){}
};

class GeneralRegister
{
public:
    vector<Register> table;

    GeneralRegister():table(8){}
    
    string Name(int register_i); 
    int Alloc(StoreType store_type);
    void Free(int register_i);
    void Grow();

    void Print();
};

#define REGISTER_ERROR(error_message)                     \
        do{                                               \
            diagnostor.Error(E_REGISTER,error_message);   \
        }while(0)
