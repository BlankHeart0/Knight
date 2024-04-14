#include "SymbolTable.h"

int VariableTable::ScopeSize()
{
    return table.size();
}

bool VariableTable::Exist(string variable_name)
{
    if(table.back().find(variable_name)==table.back().end())
        return false;
    return true;
}

void VariableTable::EnterScope()
{
    table.push_back(unordered_map<string,Variable>());
}

void VariableTable::LeaveScope()
{
    table.pop_back();
}

void VariableTable::Add(Type type,string variable_name,int line)
{
    if(!Exist(variable_name))
    {
        int scope_i=ScopeSize()-1;
        table.back()[variable_name]=Variable(type,variable_name,scope_i);
    }
    else SYMBOL_ERROR("The variable: "+variable_name+" is redefined");
}

Variable& VariableTable::Visit(string variable_name,int line)
{
    bool is_exist=false;
    int  target_i;
    for(int i=table.size()-1;i>=0;i--)
    {
        if(table[i].find(variable_name)!=table[i].end())
        {
            is_exist=true;
            target_i=i;
            break;
        }
    }

    if(!is_exist)
        SYMBOL_ERROR("The variable: "+variable_name+" is undefined");

    return table[target_i][variable_name];
}



int Function::NewLable()
{
    return lable_id++;
}

bool FunctionTable::Exist(string function_name)
{
    if(table.find(function_name)==table.end())
        return false;
    return true;
}

void FunctionTable::Add(string function_name,int line)
{
    if(!Exist(function_name))
    {
        table[function_name]=Function(function_name);
        return;
    }
    else SYMBOL_ERROR("The function: "+function_name+" is redefined");
}
  
void FunctionTable::Add(Type type,string function_name,int line)
{   
    if(function_name=="main")
        SYMBOL_ERROR("Main function must ret void");
        
    if(!Exist(function_name))
    {
        table[function_name]=Function(type,function_name);
        return;
    }
    else SYMBOL_ERROR("The function: "+function_name+" is redefined");
}

Function& FunctionTable::Visit(string function_name)
{
    return table[function_name];
}

Function& FunctionTable::Visit(string function_name,int line)
{
    if(!Exist(function_name))
        SYMBOL_ERROR("The function: "+function_name+" is undefined");
    
    return table[function_name];
}
