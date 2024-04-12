#include "Function.h"
#include "VM.h"

FunctionStack function_stack;

void FunctionTable::New(string name)
{
    table[name];
}

Function& FunctionTable::Get(string name)
{
    if(table.find(name)==table.end())
        diagnostor.Error(E_FUNCTION,"Can not find "+name);

    return table[name];
}



void FunctionStack::Push()
{
    Steed.pc.instruction_id++;
    VariableTable variables=Steed.ExcutingFunction().variables;

    context.push(Context(Steed.pc,variables));
}

void FunctionStack::Pop()
{
    if(context.empty())
        diagnostor.Error(E_FUNCTION,"Function stack is empty!");
    
    Steed.pc=context.top().pc;
    Steed.ExcutingFunction().variables =context.top().variables;

    context.pop();
}