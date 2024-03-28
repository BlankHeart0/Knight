#include "Function.h"

void Function::Excute()
{
    for(Instruction* instruction_ptr:instructions)
        instruction_ptr->Excute();
}



Function& FunctionTable::Get(string name)
{
    if(table.find(name)==table.end())
        diagnostor.Error(E_FUNCTION,"Can not find "+name);

    return table[name];
}

void FunctionTable::LoadInstruction(string name,Instruction* instruction)
{
    table[name].instructions.push_back(instruction);
}

