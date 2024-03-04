#include "Function.h"

void Function::Excute()
{
    for(Instruction* instruction_ptr:instructions)
        instruction_ptr->Excute();
}