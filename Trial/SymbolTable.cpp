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
        }
    }
    else SYMBOL_ERROR("The variable: "+variable_name+" is redefined");
}

Variable VariableTable::Visit(Token variable)
{
    int line=variable.line;

    bool is_exist=false;
    Variable target;
    for(int i=table.size()-1;i>=0;i--)
    {
        if(table[i].find(variable.lexeme)!=table[i].end())
        {
            is_exist=true;
            target=table[i][variable.lexeme];
            break;
        }
    }

    if(!is_exist)
        SYMBOL_ERROR("The variable: "+variable.lexeme+" is undefined");

    return target;
}
