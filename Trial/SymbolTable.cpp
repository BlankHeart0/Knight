#include "SymbolTable.h"

void VariableTable::EnterScope()
{
    table.push_back(unordered_map<string,Variable>());
}

void VariableTable::LeaveScope()
{
    table.pop_back();
}

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

void VariableTable::Add(Token type,string variable_name)
{
    int line=type.line;
    
    if(!Exist(variable_name))
    {
        int scope_i=ScopeSize()-1;
        switch(type.token_type)
        {
            case INT:
                table.back()[variable_name]=Variable(D_INT,variable_name,scope_i);
                break;
            case DEC:
                table.back()[variable_name]=Variable(D_DEC,variable_name,scope_i);
                break;
            case STR:
                table.back()[variable_name]=Variable(D_STR,variable_name,scope_i);
                break;
            case BOOL:
                table.back()[variable_name]=Variable(D_BOOL,variable_name,scope_i);
                break;
        }
    }
    else SYMBOL_ERROR("The variable: "+variable_name+" is redefined");
}

Variable& VariableTable::Visit(Token variable)
{
    int line=variable.line;

    bool is_exist=false;
    int  target_i;
    for(int i=table.size()-1;i>=0;i--)
    {
        if(table[i].find(variable.lexeme)!=table[i].end())
        {
            is_exist=true;
            target_i=i;
            break;
        }
    }

    if(!is_exist)
        SYMBOL_ERROR("The variable: "+variable.lexeme+" is undefined");

    return table[target_i][variable.lexeme];
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

void FunctionTable::Add(Token type,string function_name)
{
    int line=type.line;

    if(!Exist(function_name))
    {
        // rerturn void
        if(!type.is_valid)
        {
            table[function_name]=Function(function_name);
            return;
        }

        switch(type.token_type)
        {
            case INT:
                table[function_name]=Function(D_INT,function_name);
                break;
            case DEC:
                table[function_name]=Function(D_DEC,function_name);
                break;
            case STR:
                table[function_name]=Function(D_STR,function_name);
                break;
            case BOOL:
                table[function_name]=Function(D_BOOL,function_name);
                break;
        }
    }
    else SYMBOL_ERROR("The function: "+function_name+" is redefined");
}

Function& FunctionTable::Visit(Token function)
{
    int line=function.line;

    if(!Exist(function.lexeme))
        SYMBOL_ERROR("The variable: "+function.lexeme+" is undefined");
    
    return table[function.lexeme];
}

//@Bug:Only used by NowInFunction
Function& FunctionTable::Visit(string function_name)
{
    return table[function_name];
}
