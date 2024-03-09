#include "Register.h"

GeneralRegister general_register;

void GeneralRegister::Set(int register_i,int int_val)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());
    
    table[register_i].store_type=S_INT;
    table[register_i].INT_val=int_val;
}

void GeneralRegister::Set(int register_i,double dec_val)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());

    table[register_i].store_type=S_DEC;
    table[register_i].DEC_val=dec_val;
}

void GeneralRegister::Set(int register_i,string str_val)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());
    
    table[register_i].store_type=S_STR;
    table[register_i].STR_val=str_val;
}



Register& GeneralRegister::GetReg(int register_i)
{
    return table[register_i];
}



void GeneralRegister::Grow(int n)
{
    while(n--)table.push_back(Register());
}
