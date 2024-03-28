#include "Register.h"

RegisterTable general_register;
RegisterTable argument_register;
Register      retvalue_register;

void Register::Set(int int_val)
{
    data_type=D_INT;
    INT_val=int_val;
}

void Register::Set(double dec_val)
{
    data_type=D_DEC;
    DEC_val=dec_val;
}

void Register::Set(string str_val)
{
    data_type=D_STR;
    STR_val=str_val;
}

void Register::Set(bool bool_val)
{
    data_type=D_BOOL;
    BOOL_val=bool_val;
}



void RegisterTable::Grow(int n)
{
    while(n--)table.push_back(Register());
}



void RegisterTable::Set(int register_i,int int_val)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());

    table[register_i].Set(int_val);
}

void RegisterTable::Set(int register_i,double dec_val)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());

    table[register_i].Set(dec_val);
}

void RegisterTable::Set(int register_i,string str_val)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());
    
    table[register_i].Set(str_val);
}

void RegisterTable::Set(int register_i,bool bool_val)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());
    
    table[register_i].Set(bool_val);
}



Register& RegisterTable::Get(int register_i)
{
    return table[register_i];
}
