#include "Register.h"

RegisterTable general_register;
RegisterTable argument_register;
Register      retvalue_register;

RegisterStack register_stack;

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

void Register::Set(Register& reg)
{
    data_type=reg.data_type;

    switch(reg.data_type)
    {
        case D_INT: INT_val =reg.INT_val; break;
        case D_DEC: DEC_val =reg.DEC_val; break;
        case D_STR: STR_val =reg.STR_val; break;
        case D_BOOL:BOOL_val=reg.BOOL_val;break;
    }
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

void RegisterTable::Set(int register_i,Register& reg)
{
    if(register_i>=table.size())
        Grow(register_i+1-table.size());
    
    table[register_i].Set(reg);
}

Register& RegisterTable::Get(int register_i)
{
    return table[register_i];
}

Register RegisterTable::Copy(int register_i)
{
    return table[register_i];
}



void RegisterStack::Push(Register reg)
{
    regstack.push(reg);
}

void RegisterStack::Pop(Register& reg)
{
    if(regstack.empty())
        diagnostor.Error(E_REGISTER,"Register stack is empty!");
        
    reg.Set(regstack.top());
    regstack.pop();
}
