#include "Variable.h"

void VariableTable::Grow(int n)
{
    while(n--)table.push_back(unordered_map<string,Variable>());
}



void VariableTable::Set(int scope_i,string name,int int_val)
{
    if(scope_i>=table.size())
        Grow(scope_i+1-table.size());
    
    table[scope_i][name].data_type=D_INT;
    table[scope_i][name].INT_val=int_val;
}

void VariableTable::Set(int scope_i,string name,double dec_val)
{
    if(scope_i>=table.size())
        Grow(scope_i+1-table.size());

    table[scope_i][name].data_type=D_DEC;
    table[scope_i][name].DEC_val=dec_val;
}

void VariableTable::Set(int scope_i,string name,string str_val)
{
    if(scope_i>=table.size())
        Grow(scope_i+1-table.size());

    table[scope_i][name].data_type=D_STR;
    table[scope_i][name].STR_val=str_val;
}

void VariableTable::Set(int scope_i,string name,bool bool_val)
{
    if(scope_i>=table.size())
        Grow(scope_i+1-table.size());

    table[scope_i][name].data_type=D_BOOL;
    table[scope_i][name].BOOL_val=bool_val;
}



Variable& VariableTable::Get(int scope_i,string name)
{
    return table[scope_i][name];
}
